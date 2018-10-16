#pragma once
#ifndef IMAGECONVERT_H
#define IMAGECONVERT_H

#include "xiApi.h"

namespace gs {

class Image;

Image convertImage(const XI_IMG& img);

}

#endif
