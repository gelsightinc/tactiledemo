#include "imageconvert.h"
#include "gelsightsdk.h"


namespace gs {

Image convertImage(const XI_IMG& img)
{
	Image image;
	gs::SizeI sz(img.width, img.height);

    switch (img.frm)
    {
    case XI_MONO8:
        image = gs::ImageT<uint8_t>(reinterpret_cast<uint8_t*>(img.bp), sz);
        break;
    
    case XI_RGB_PLANAR:
        ASSERT(false);              // JMO:  TODO:  Process?
    
    case XI_RGB24:  // Ximea "RGB" data is really BGR according to their docs
        image = gs::ImageT<gs::Bgr8>(reinterpret_cast<gs::Bgr8*>(img.bp), sz);
        break;
    
    case XI_RGB32:
        ASSERT(false);              // JMO:  No idea what to do.
        break;
    
    case XI_MONO16:
        image = gs::ImageT<uint16_t>(reinterpret_cast<uint16_t*>(img.bp), sz);
        break;
    
    default:
        throw std::runtime_error("Unsupported data format " + std::to_string(img.frm) + "in hitCount");
        break;
    }

     return image;
}

cv::Mat convertImage(const ImageF& img)
{
	const auto yd = img.height();
	const auto xd = img.width();
	cv::Mat mat(yd, xd, CV_32F);

	memcpy((float*)(mat.data), img.ptr(0), xd*yd*sizeof(float));
	return mat;
}

}