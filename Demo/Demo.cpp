// Demo.cpp : Defines the entry point for the console application.
//

#include "gelsightsdk.h"
#include "imageconvert.h"

#include <string>
#include <iostream>

using std::string;

//#define EXPOSURE_NEG

// If USECAMERA is false, load an image from a file
const bool USECAMERA = true;

//
// 
//
int main(int argc, char *argv[])
{
	
	//
	// IMPORTANT: Must call gsSdkInitialize() before using the SDK
	//
	try {
        std::cout << "Initializing GelSightSdk" << std::endl;
		gsSdkInitialize();
	} catch(std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	
	DWORD nDevices;
	const auto stat = xiGetNumberDevices(&nDevices);

	if (USECAMERA && (stat != XI_OK || nDevices == 0)) {
		std::cerr << "No devices found, exiting." << std::endl;
		return 1;
	}


	HANDLE camera;
	
	// Load Photometric stereo object for image -> normalmap
	string setpath("../../testdata/");
#ifdef _WIN32
	setpath = std::string("../testdata/");
#endif

    std::cout << "Loading PhotometricStereo object" << std::endl;
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
        std::cout << "Opening Camera" << std::endl;
		auto val = xiOpenDevice(0, &camera);
		if (val != XI_OK) {
			std::cerr << "Cannot open camera 0" << std::endl;
			return 1;
		}

		// Camera settings
		val = xiSetParamInt(camera, XI_PRM_BUFFER_POLICY, XI_BP_UNSAFE);
		val = xiSetParamInt(camera, XI_PRM_GPO_SELECTOR, XI_GPO_PORT1);
		val = xiSetParamInt(camera, XI_PRM_ACQ_TIMING_MODE, XI_ACQ_TIMING_MODE_FRAME_RATE_LIMIT);
		val = xiSetParamInt(camera, XI_PRM_GPI_MODE, XI_GPI_OFF);

		// Strobe for triggering lights
#ifdef EXPOSURE_NEG
		val = xiSetParamInt(camera, XI_PRM_GPO_MODE, XI_GPO_EXPOSURE_ACTIVE_NEG);
#else
		val = xiSetParamInt(camera, XI_PRM_GPO_MODE, XI_GPO_EXPOSURE_ACTIVE);
#endif

		auto micros = static_cast<int>(1000 * shutterms);
		val = xiSetParamInt(camera, XI_PRM_EXPOSURE, micros);
		val = xiSetParamInt(camera, XI_PRM_IMAGE_DATA_FORMAT, XI_RGB24);

		// White balance, frame rate, gamma
		val = xiSetParamFloat(camera, XI_PRM_WB_KR, 1.7f);
		val = xiSetParamFloat(camera, XI_PRM_WB_KG, 1.5f);
		val = xiSetParamFloat(camera, XI_PRM_WB_KB, 1.0f);
		val = xiSetParamFloat(camera, XI_PRM_FRAMERATE, 60.0f);
		val = xiSetParamFloat(camera, XI_PRM_GAMMAY, 1.0f);
		val = xiSetParamFloat(camera, XI_PRM_GAMMAC, 1.0f);


		val = xiStartAcquisition(camera);
		if (val != XI_OK) {
			std::cerr << "Unable to start camera" << std::endl;
			return 1;
		}

		XI_IMG img;
		memset(&img, 0, sizeof(img));
		img.size = sizeof(XI_IMG);

        std::cout << "Grabbing single image" << std::endl;
		val = xiGetImage(camera, 1000, &img);
		if (val != XI_OK) {
			std::cerr << "Umable to retrieve image" << std::endl;
			return 1;
		}

		// Convert to gs::Image
		image = gs::convertImage(img);


	} else {
		// Load image from memory
        std::cout << "Reading image from memory" << std::endl;
		image = gs::util::ReadBgr8(setpath + "penny-001/image01.png");
	}

	// Do 3D reconstruction using saved calibration
	gs::HeightMap hm;

	// For tactile sensor, important to only compute 3D within specified 
	// crop region
	gs::RectI croproi(567, 229, 902, 828);


	try {
		// Poisson integration for normalmap -> heightmap
		auto poisson = gs::CreateIntegrator(gs::Version());

		// Fast reconstruction
		auto nrm = pstereo->linearNormalMap(image, croproi);

		// Limit normal map to croi
        std::cout << "3D reconstruction" << std::endl;
		gs::NormalMap nrmc(nrm, croproi);
		hm = poisson->integrateNormalMap(nrmc, pstereo->resolution());

        auto fpath = setpath + "output.tmd";
        auto impath = setpath + "frame.png";
        std::cout << "Saving 3D measurement in TMD format to " << fpath << std::endl;
        gs::util::WriteTMD(fpath, hm);
	std::cout << "Saving image in PNG format to " << impath << std::endl;
	gs::util::WritePng(impath, image);

	} catch (gs::Exception& e) {
		std::cerr << "Error running pstereo: " << e.what() <<  std::endl;
	}

	// Convert Heightmap to CV_32F
    std::cout << "Converting to cv::Mat CV_32F" << std::endl;
	auto mat = convertImage(hm);



	if (USECAMERA) {
		// Stop acquisition
		auto val = xiStopAcquisition(camera);
	}
	
	std::cout << "done." << std::endl;
	// Make the console wait for a character to exit
#ifdef _WIN32
	std::getchar();
#endif
	return 0;
}


