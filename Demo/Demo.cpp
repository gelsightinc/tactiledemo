// Demo.cpp : Defines the entry point for the console application.
//

#include "gelsightsdk.h"
#include "gsanalysisroutine.h"
#include "calibration.h"
#include "geometry.h"
#include "ximeawrappers.h"
#include "imageconvert.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <memory>

using std::string;

//#define EXPOSURE_NEG

// If USECAMERA is false, load an image from a file
const bool USECAMERA = false;


//
// 
//
int main(int argc, char *argv[])
{
	
	//
	// IMPORTANT: Must call gsSdkInitialize() before using the SDK
	//
	try {
		gsSdkInitialize();
	} catch(std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	
	const auto nDevices = xi::Camera::count();  // Get this once

	if (USECAMERA && nDevices == 0) {
		std::cerr << "No devices found, exiting." << std::endl;
		return 1;
	}


	std::shared_ptr<xi::Camera> camera;
	
	// Load Photometric stereo object for image -> normalmap
	string setpath("../testdata/");
	const auto modelfile = setpath + "model.yaml";
	auto pstereo = gs::LoadPhotometricStereo(modelfile);
	if (!pstereo) {
		std::cerr << "Cannot load calibration" << std::endl;
	}
 
	// Try to load camera shutter from calibration file
	double shutterms = 1.0;
	auto camProps   = pstereo->getPropMap(PK_CAMERA);
	if (camProps.find("shutter") != camProps.end()) {
		shutterms = std::stod(camProps["shutter"]);
	}

	gs::Image image;

	if (USECAMERA) {
		try {
			const auto sn = xi::Camera::serialNumber(0);
			auto cam = std::make_shared<xi::Camera>(XI_OPEN_BY_SN, sn);

			// Camera settings
			cam->BufferPolicy = XI_BP_UNSAFE;

			cam->GpoSelector   = XI_GPO_PORT1;
			cam->AcqTimingMode = XI_ACQ_TIMING_MODE_FRAME_RATE_LIMIT;
			cam->GpiMode       = XI_GPI_OFF;

	#ifdef EXPOSURE_NEG
			cam->GpoMode      = XI_GPO_EXPOSURE_ACTIVE_NEG;
	#else
			cam->GpoMode      = XI_GPO_EXPOSURE_ACTIVE;
	#endif
			cam->ExposureTime = static_cast<float>(1000 * shutterms);
			cam->ImageDataFormat = XI_RGB24;
			cam->WbRed     = 1.7f;
			cam->WbGreen   = 1.5f;
			cam->WbBlue    = 1.0f;
			cam->FrameRate = 60;

			cam->GammaLuminosity = 1.0;


			camera = cam;

			// Start acquisition
			camera->startAcquisition();

			auto&& img = camera->image(1000);

			// Convert to gs::Image
			image = gs::convertImage(img);

		} catch (std::exception& e) {
			std::cerr << "Error grabbing frame: " << e.what() << std::endl;
		}

	} else {
		// Load image from memory
		image = gs::util::ReadBgr8(setpath + "penny-001/image01.png");
	}

	// Do 3D reconstruction using saved calibration
	gs::HeightMap hm;

	// For tactile sensor, important to only compute 3D within specified 
	// crop region
	gs::RectI croproi(567, 229, 902, 828);
	gs::Images images;
	images.push_back(image);

	try {
		// Poisson integration for normalmap -> heightmap
		auto poisson = gs::CreateIntegrator(gs::Version());

		// Fast reconstruction
		auto nrm = pstereo->linearNormalMap(images, croproi);

		// Limit normal map to croi
		gs::NormalMap nrmc(nrm, croproi);
		hm = poisson->integrateNormalMap(nrmc, pstereo->resolution());

		
	} catch (gs::Exception& e) {
		std::cerr << "Error running pstereo: " << e.what() <<  std::endl;
	}

	// Convert Heightmap to CV_32F
	auto mat = convertImage(hm);

	// Save opencv mat
	std::ofstream myfile;
	myfile.open("C:/Users/kimo/Desktop/output.csv");
	myfile << cv::format(mat, cv::Formatter::FMT_CSV) << std::endl;
	myfile.close();


	if (USECAMERA) {
		// Stop acquisition
		try {
			camera->stopAcquisition();
		} catch (std::exception& e) {
			std::cerr << "Error stopping camera" << std::endl;
		}
	}
	// Disable camera
	camera.reset();
	
	std::cout << "done." << std::endl;
	// Make the console wait for a character to exit
	std::getchar();
	return 0;
}


