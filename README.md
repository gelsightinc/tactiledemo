# GelSight Tactile Sensor Demo

This project demonstrates how to grab images from the GelSight tactile sensor,
push them through the GelSightSDK to convert to 3D and then convert the 3D data
into OpenCV CV_32F format. 



## Prerequisites

This demo assumes you have several third-party packages installed. Here are the packages and basic installation instructions.

 - Ximea API: Download the Ximea XPI from [XIMEA Linux Software](https://www.ximea.com/support/wiki/apis/XIMEA_Linux_Software_Package) and install according to the instructions. It will install the Ximea libraries to /usr/lib and the headers to /usr/include/m3api
 - OpenCV: Download and use CMake to build OpenCV. I modify the CMake settings to build opencv_world for convenince. After make install, the libraries will be installed to /usr/local/lib
 - GelSightSdk: Get the latest version of GelSightSdk for Linux from support@gelsight.com and define the GS_SDK environment variable to specify the location of the GelSightSdk folder on your machine

In addition, it is necessary to run the following command to use the camera. This issue is reported when you run xiCOP in /opt/XIMEA/bin:
```
Detected issues:

* [MC050MG-SY-UB/CIMAU1633011] Kernel setting usbcore.usbfs_memory_mb is too low.
  1). Execute the following command: sudo tee /sys/module/usbcore/parameters/usbfs_memory_mb >/dev/null <<<0
```

## Testing the camera

You can test the camera by running xiCamTool. The basic settings are:
 - Basic -> Auto exposure: unchecked
 - Basic -> Exposure: 2 ms (between 1 and 3 ms depending on the camera/lens)
 - Trigger, Device I/O ->  Device IO Setup... -> GPO1: Exposure active 
 - Performance -> Control FPS: Frame Rate Limit
 - Performance -> Frame rate: 80 FPS

The `Exposure active` settings for GPO (General Purpose Output) triggers the LEDs using the camera strobe. When the exposure is active, the strobe is HIGH, turning the lights on. It is normal for the lights to flicker with the camera. 

You should be able to click the triangle in the upper left corner of xiCamTool and see a live image at 80 FPS with the lights on. 

## GelSight license

The GelSightSdk requires a license to run. Please email suport@gelsight.com if
you do not have a license. The software expects to find the license file
`gelsight_64.bin` in `$GS_SDK/lib`

It is also useful to append $GS_SDK/lib to LD_LIBRARY_PATH.

## Building the demo

First use CMake to create the build environment. Then type make. 
