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

//#define EXPOSURE_NEG

using std::string;
using std::cout;
using std::endl;
using std::vector;




/*
 * Run pstereo algorithm on sine wave sample data
 */
int runpstereo(gs::PhotometricStereo *pstereo)
{
	string setpath("../testdata/");
	string scanfile = setpath + "sine2/scan.yaml";

	cout << "Running photometric stereo algorithm" << endl;

	// Load a scan from the scan file
	
	auto scan = gs::LoadScanFromYAML(scanfile, gs::DefaultAnalysisManager());

	
	// Load images from scan
    // Can also run algorithm on 8-bit or 16-bit images to reduce memory consumption
	auto images = gs::util::LoadImagesF(scan->imagePaths());
	

	cout << "Loaded " << images.size() << " images" << endl;
	if (images.size() == 0)
		return 1;

	// Do surface normal reconstruction
	auto nrm = pstereo->nonlinearNormalMap(images, pstereo->roi());

	// Integrate normals into heightmap
	cout << "Integrating surface normals..." << endl;
	auto poisson = gs::CreateIntegrator(gs::Version());
	auto heightmap = poisson->integrateNormalMap(nrm, pstereo->resolution());

	// Save surface as TMD
	string out1 = setpath + "sine2/output.tmd";
	cout << "Saving " << out1 << endl;
	gs::util::WriteTMD(out1, heightmap, pstereo->resolution(), 0.0, 0.0);


	// Save normal map
	string out2 = setpath + "sine2/output_nrm.png";
	cout << "Saving " << out2 << endl;
	gs::util::WriteNormalMap(out2, nrm, 16);

	return 0;
}


/*
 * This function shows how to load a saved calibration and compute 3D for a scan
 */
int runsavedcalib()
{
	string setpath("../testdata/");

	cout << "Loading saved calibration data..." << endl;
	// Load PhotometricStereo algorithm from settings file
	
	auto modelfile = setpath + "model.yaml";
	try {

		auto pstereo = gs::LoadPhotometricStereo(modelfile);
		runpstereo(pstereo.get());

	} catch (gs::Exception& e) {
		cout << "Exception: " << e.error() << endl;
	}

	

	return 0;
}




/*
 * This function shows how to calibrate the system from one or more calibration scans
 */
int runcalibration()
{
	string setpath("../testdata/");
	string calibdir = setpath + "calib-001/scan.yaml";
	
	// Create list of calibration targets
    std::vector<std::shared_ptr<gs::CalibrationTarget>> targets;
    
    auto scanpt = gs::LoadScanFromYAML(calibdir, gs::DefaultAnalysisManager());

    auto calibradius = 1.5785 / 2.0;
    auto calibspacing = 3.175;

    // Now create BGA from scan pointer
    std::vector<gs::CircleD> nocircles;
    auto bga = std::make_shared<gs::BgaTarget>(scanpt, nocircles, calibspacing, calibradius);
				
    targets.push_back(bga);

	auto start = std::chrono::system_clock::now();
	
	cout << "Running calibration algorithm..." << endl;
    auto res = 0.00345 * 2.0;

	auto pstereo = gs::CalibratePhotometricStereo(targets, res, gs::Version());

	std::chrono::duration<double> readtime = std::chrono::system_clock::now() - start;
    
	cout << "calibration took " << readtime.count() << " seconds" << endl;

	return 0;
}


/*
 * This function is meant to simulate a scan that has been saved to disk
 */
vector<string> doscan(const string& foldername)
{
	string setpath("../testdata/");
	string calibdir = setpath + "calib";
	
	vector<string> paths;
	for (int i = 0; i < 6; ++i) {
		paths.push_back(calibdir + "/image0" + std::to_string(i+1) + ".png");
	}
	return paths;
}












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
		std::cerr << ex.what() << endl;
	}
	
	const auto nDevices = xi::Camera::count();  // Get this once

	if (nDevices == 0) {
		std::cerr << "No devices found, exiting." << std::endl;
		return 1;
	}

	const auto sn = xi::Camera::serialNumber(0);

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



	try {
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

	} catch (std::exception& e) {
		std::cerr << "Error initializing camera" << e.what() << std::endl;
		
	}


	// Start acquisition
	gs::Image image;
	try {
		camera->startAcquisition();

		auto&& img = camera->image(1000);

		// Convert to gs::Image
		image = gs::convertImage(img);

	} catch (std::exception& e) {
		std::cerr << "Error grabbing frame: " << e.what() << std::endl;
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

		gs::util::WritePng("C:/Users/kimo/Desktop/testcolor.png", image);
		gs::util::WriteTMD("C:/Users/kimo/Desktop/test.tmd", hm, pstereo->resolution(), 0.0, 0.0);
		gs::util::WriteNormalMap("C:/Users/kimo/Desktop/normals.png", nrm, 16);
		
	} catch (gs::Exception& e) {
		std::cerr << "Error running pstereo: " << e.what() <<  std::endl;
	}


	// Stop acquisition
	try {
		camera->stopAcquisition();
	} catch (std::exception& e) {
		std::cerr << "Error stopping camera" << std::endl;
	}

	// Disable camera
	camera.reset();
	
	std::cout << "done." << std::endl;
	// Make the console wait for a character to exit
	std::getchar();
	return 0;
}


