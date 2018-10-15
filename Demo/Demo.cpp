// Demo.cpp : Defines the entry point for the console application.
//

#include "gelsightsdk.h"
#include "gsanalysisroutine.h"
#include "calibration.h"
#include "geometry.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <memory>

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

/*
 * This function shows how to calibrate the system from lists of image paths
 */
void runCalibrationFromImagePaths()
{
	// List of BGA Targets
	std::vector<std::shared_ptr<gs::CalibrationTarget>> targets;
	for (int i = 0; i < 4; ++i) {

		// Get image paths for a new scan
		auto paths = doscan("calib" + std::to_string(i+1));

		// Create scan object for thes image paths
		auto scan = gs::CreateScan(paths);

		// Set BGA parameters - pitch (spacing) and radius
		scan->setCalibDimensions(0.4, 0.15625);

		// Set resolution
		scan->setResolution(0.007812500000000002, gs::Unit::MM);

		// Save the scan file as YAML format
		auto scanp = string("../testdata/calib") + "/scan" + std::to_string(i+1) + ".yaml";
		scan->save(scanp, gs::Format::YAML);

		// Now create BGAs from scans
		// Create list of calibration targets
		auto target = std::make_shared<gs::BgaTarget>(string("../testdata/calib"));

		targets.push_back(target);
	}


	cout << "Run calibration algorithm..." << endl;
    auto pstereo = gs::CalibratePhotometricStereo(targets, 0.007812500000000002, gs::Version());


	// Save calibration file as model.yaml
	pstereo->save("../testdata/testmodel.yaml", gs::Format::YAML);


}



//
// Demo of offset analysis
//
void runoffset1()
{
	string setpath("../testdata/Offset/");
	string tmdpath = setpath + "offset1.tmd";

	try {

		// Try loading analysis manager
		auto am = gs::DefaultAnalysisManager();

		auto hm = gs::util::ReadTMD(tmdpath);

		auto scan = gs::CreateScan(hm);
		
		auto r = am->newRoutine("Offset");

		// Add a line for analysis
		auto ln = std::make_shared<gs::LineShape>(0, 32, 63, 32);

		scan->addShape(ln);
		r->setInt("primaryshapeid", ln->id());

		// Profile extraction parameters
		r->setBool("level",        true);
		r->setDouble("levelstart", 0.00);
		r->setDouble("levelend",   0.02);
		r->setInt("numprofiles",   1);

		// Offset parameters
		r->setDouble("region1start", 0.01);
		r->setDouble("region1end",   0.02);
		r->setString("region1mode",  "average");
		r->setDouble("region2start", 0.04);
		r->setDouble("region2end",   0.05);
		r->setString("region2mode",  "average");

		// Create scan context for calling analysis
		gs::ScanContext ct(*scan);

		string msg;
		gs::Error err;
		auto valid = r->validate(ct, err, msg);

		r->analyze(ct);
		auto dst = r->getDouble("offset");

		std::cout << "offset: " << dst << std::endl;
	} catch (gs::Exception&) {}
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
	

	try {
        //runsavedcalib();
        runcalibration();

	} catch (gs::Exception& e) {
		std::cerr << e.what() << std::endl;
		
	}
	
	// Make the console wait for a character to exit
	std::getchar();
	return 0;
}


