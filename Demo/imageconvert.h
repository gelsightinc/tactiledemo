#pragma once
#ifndef IMAGECONVERT_H
#define IMAGECONVERT_H

#include "xiApi.h"
#include "opencv2/opencv.hpp"
#include "gscorefwd.h"

namespace gs {

Image convertImage(const XI_IMG& img);

cv::Mat convertImage(const HeightMap& img);

} // namespace gs

#endif
