#include"ximeawrappers.h"
#include "stdstream.h"

namespace xi
{



__declspec(noreturn) inline void xiThrow(int err, const std::string& msg)
{
    throw xi::Exception(err, msg);
}


// Check a return status.  Currently this just dumps a message on error but
// going forward it would likely be better to make this throw a rich exception
void xiCheck(XI_RETURN ret, const std::string msg)
{
    if (XIFAIL(ret))
        xiThrow(ret, msg);
}


Camera::Camera() : m_hDevice(NULL), m_bAcquiring(false)
{
}
Camera::Camera(XI_OPEN_BY sel, const char* prm)
    : m_hDevice(NULL), m_bAcquiring(false)
{
    open(sel, prm);
}
Camera::Camera(XI_OPEN_BY sel, const std::string& prm)
    : m_hDevice(NULL), m_bAcquiring(false)
{
    open(sel, prm.c_str());
}
Camera::Camera(DWORD id)
    : m_hDevice(NULL), m_bAcquiring(false)
{
    open(id);
}


void Camera::open(XI_OPEN_BY sel, const char* prm)
{
    close();

    // Use a temp value because Ximea changes it even on failure.  Bad Ximea.

    decltype(m_hDevice) temp = NULL;
    const auto val = xiOpenDeviceBy(sel, prm, &temp);
    if (!XIOK(val))
        xiThrow(val, "Opening device.");

    m_hDevice = temp;

#ifdef _DEBUG
    DebugLevel = XI_DL_ERROR;
#else
//    DebugLevel = XI_DL_ERROR;
#endif
}
void Camera::open(DWORD devId)
{
    close();

    // Use a temp value because Ximea changes it even on failure.  Bad Ximea.

    decltype(m_hDevice) temp = NULL;
    const auto val = xiOpenDevice(devId, &temp);
    if (!XIOK(val))
        xiThrow(val, "Opening device " + std::to_string(devId));

    m_hDevice = temp;

#ifdef _DEBUG
    DebugLevel = XI_DL_ERROR;
#else
//    DebugLevel = XI_DL_ERROR;
#endif
}

bool Camera::isOpen() const 
{
    return NULL != m_hDevice; 
}
void Camera::close()
{
    if (NULL != m_hDevice)
    {
        stopAcquisition();

        const auto val = xiCloseDevice(m_hDevice);
        if (!XIOK(val))
            STDERR("Failed to close device " << m_hDevice);

        m_hDevice = NULL;
    }
}
void Camera::startAcquisition()
{
    ASSERT(isOpen());
    ASSERT(!m_bAcquiring);
    if (!m_bAcquiring)
    {
        const auto val = xiStartAcquisition(m_hDevice);

        if (XI_ACQUISITION_ALREADY_UP == val)
            STDLOG("xi::Camera: Acquisition was already up");
        else if (!XIOK(val))
            xiThrow(val, "starting acquisition");

        m_bAcquiring = true;

        STDLOG("Ximea Camera Acquisition started");
    }
}
void Camera::stopAcquisition()
{
    if (m_bAcquiring)
    {
        ASSERT(isOpen());
        const auto val = xiStopAcquisition(m_hDevice);

        if (XI_ACQUISITION_STOPED == val && XI_ACQUISITION_STOPED_WERR == val)
            STDLOG("Acquisition was already stopped");
        else if (!XIOK(val))
            xiThrow(val, "stopping acquisition");

        if (XI_ACQUISITION_STOPED_WERR == val)
            STDERR("Acquisition stopped but with an error.");

        m_bAcquiring = false;

        STDLOG("Ximea Camera Acquisition stopped");
    }
}
XI_IMG Camera::image(DWORD dwTimeout) const
{
    XI_IMG img = {0};
    img.size = sizeof(XI_IMG);

    const auto val = xiGetImage(m_hDevice, dwTimeout, &img);
    if (!XIOK(val))
        xiThrow(val, "retrieving image");

    return img;
}

XI_RETURN Camera::getImage(DWORD dwTimeout, XI_IMG& img) const
{
    img.size    = sizeof(XI_IMG);

    const auto val = xiGetImage(m_hDevice, dwTimeout, &img);

    if (!XIOK(val))
        STDERR("Unable to retrieve image: " << ErrorString(val));

    return val;
}




std::string Camera::infoString(DWORD devId, const char* prm)
{
    char buf[300];
    const auto stat = xiGetDeviceInfoString(devId, prm, buf, sizeof(buf));
    std::string out;

    if (!XIOK(stat))
    {
        STDERR("Failed to get info string \"" << prm << "\" for << devId "
        << devId << ":  " << ErrorString(stat));
    }
    else
    {
        buf[299] = 0;       // ensure it's null terminated
        out = buf;

        // Ximea likes to return control characters and the like in these
        // strings.  Remove all non-printable characters.
        // TODO:  Make this caller's responsibility?

        const auto ctl = [] (auto ch) {return !std::isprint(ch, std::locale::classic()); };
        su::erase_if(out, ctl);
    }


    return out;
}
std::string Camera::serialNumber(DWORD devId)
{
    return infoString(devId, XI_PRM_DEVICE_SN);
}

DWORD Camera::count()
{
    DWORD val = 0;
    const auto stat = xiGetNumberDevices(&val);
    if (XIFAIL(stat))
    {
        STDERR("xi::Camera -- failed to retrieve number of devices: "
            << ErrorString(stat));
    }

    return val;
}




#if 0

ImageProcessing::ImageProcessing()
{
    processing_handle_ = NULL;
    XI_RETURN res = xiProcOpen(&processing_handle_);
    CheckResult(res, "xiProcOpen");
}

// ---------------------------------------------------------------------

ImageProcessing::~ImageProcessing()
{
    XI_RETURN res = xiProcClose(processing_handle_);
    CheckResult(res, "xiProcClose");
}

// ---------------------------------------------------------------------


// -------------------------------------------------------------------

void ImageProcessing::SetParam(const char* prm, void* val, DWORD size, XI_PRM_TYPE type)
{
    XI_RETURN res = xiProcSetParam(processing_handle_, prm, val, size, type);
    CheckResult(res, "xiProcSetParam");
}

// ---------------------------------------------------------------------

void ImageProcessing::PushImage(unsigned char* first_pixel)
{
    XI_RETURN res = xiProcPushImage(processing_handle_, first_pixel);
    CheckResult(res, "xiProcPushImage");
}

void ImageProcessing::PullImage()
{
    XI_RETURN res = xiProcPullImage(processing_handle_, 0, last_image_.GetXI_IMG());
    CheckResult(res, "xiPullImage");
}
//#include "XiSampleOpencv.hpp"




/**********************************************************************************/
/**
* Initialize the CameraOcv class.
*/
CameraOcv::CameraOcv()
{

    //cv_image=NULL;
    cv_image_ = cvCreateImage(cvSize(1, 1), IPL_DEPTH_8U, 1);
    cv_mat_image_ = cv::Mat(0, 1, CV_32FC1);
    next_image_ = NULL;
    counter_ = 0;
    index_ = 0;
}

/**********************************************************************************/
/**
* Class destructor. Free allocated memory, release images
*/
CameraOcv::~CameraOcv()
{
    printf("Closing Ocv camera\n");
    if (cv_image_)
        cvReleaseImage(&cv_image_);
    cv_mat_image_.release();
}

/**********************************************************************************/
/**
* Reads an image from the camera using XiAPI, stores the image in OpenCV format.
* @return OpenCV IpliImage* image.
*/

//Reads and image and converts it to OpenCV IplImage
IplImage*  CameraOcv::GetNextImageOcvIpl()
{
    next_image_ = GetNextImage(NULL);
    return ConvertOcvIpl(next_image_);
}

/**********************************************************************************/
/**
* Reads an image from the camera using XiAPI, stores the image in OpenCV Mat format.
* @return OpenCV Mat image.
*/
cv::Mat CameraOcv::GetNextImageOcvMat()
{
    cv_mat_image_ = cv::cvarrToMat(GetNextImageOcvIpl());
    return cv_mat_image_;
}

/**********************************************************************************/
/**
* Converts a XiAPI image (Image*) to OpenCV IplImage *.
* @param input_image[in] Input Image* to be converted.
* @return converted OpenCV IpliImage* image.
*/
IplImage *  CameraOcv::ConvertOcvIpl(Image * input_image)
{
    counter_++;
    //Testing section
    /*if(counter_%50==0){
        if(cv_image_) cvReleaseImage(&cv_image_);
        cv_image_ = NULL;
        cv_image_=cvCreateImage(cvSize( 400, 400), IPL_DEPTH_16U, 1);
        //index++;
        counter_=1;
        printf("index: %d\n",index_);
    }*/
    //End of testing section
    //printf("Before reset conversion XIAPI+ IMGDATA %d\n",*input_image->GetPixels());  
    // update cvImage after format has changed
    resetCvImage_();
    //printf("After reset before conversion XIAPI+ IMGDATA %d\n",*input_image->GetPixels());    
    //printf("Converting xiAPI image to openCV\n");
    // allocate frame buffer copy pixel data

    cv_image_->imageData = (char*)input_image->GetPixels();

    if (cv_image_)
        return cv_image_;
    else
    {
        printf("Error: converting XI_IMG to IplImage\n");
        return NULL;
    }
}

/**********************************************************************************/
/**
* Converts a XiAPI image (Image*) to OpenCV  .
* @param input_image[in] Input Image* to be converted.
* @return converted OpenCV IpliImage* image.
*/
cv::Mat CameraOcv::ConvertOcvMat(Image *  input_image)
{
    cv_mat_image_ = cv::cvarrToMat(ConvertOcvIpl(input_image));
    return cv_mat_image_;
}

/**********************************************************************************/
/**
* Resets the Opencv image if properties of XI_IMG have changed. Resets the cv_image_.
*/
void CameraOcv::resetCvImage_()
{
    bool do_reset = false;
    //printf ("Reseting image\n");
    // first check basic image resolution
    if (next_image_->GetDataFormat() != XI_MONO8)
    {
        if (((int)next_image_->GetWidth() != cv_image_->width) || ((int)next_image_->GetHeight() != cv_image_->height))
            do_reset = true;
    }
    else
    {
        if (((int)(next_image_->GetWidth() + next_image_->GetPadding_X()) != cv_image_->width) || ((int)next_image_->GetHeight() != cv_image_->height))
            do_reset = true;
    }

    // afterwards check image format
    switch (next_image_->GetDataFormat())
    {
    case XI_MONO8:
    case XI_RAW8:
    {
        if (cv_image_->depth != IPL_DEPTH_8U || cv_image_->nChannels != 1)
            do_reset = true;
    }
    break;
    case XI_MONO16:
    case XI_RAW16:
    {
        if (cv_image_->depth != IPL_DEPTH_16U || cv_image_->nChannels != 1)
            do_reset = true;
    }
    break;
    case XI_RGB24:
    case XI_RGB_PLANAR:
    {
        if (cv_image_->depth != IPL_DEPTH_8U || cv_image_->nChannels != 3)
            do_reset = true;
    }
    break;
    case XI_RGB32:
    {
        if (cv_image_->depth != IPL_DEPTH_8U || cv_image_->nChannels != 4)
            do_reset = true;
    }
    break;
    default:
        printf("CvCaptureCAM_XIMEA::resetCvImage ERROR: Unknown format.");
        return;
    }


    if (do_reset)
    {
        if (cv_image_) cvReleaseImage(&cv_image_);
        cv_image_ = NULL;

        switch (next_image_->GetDataFormat())
        {
        case XI_MONO8: cv_image_ = cvCreateImage(cvSize(next_image_->GetWidth() + next_image_->GetPadding_X(), next_image_->GetHeight()), IPL_DEPTH_8U, 1); printf("Doing reset to mono\n"); break;
        case XI_RAW8: cv_image_ = cvCreateImage(cvSize(next_image_->GetWidth(), next_image_->GetHeight()), IPL_DEPTH_8U, 1); printf("Doing reset to mono\n"); break;
        case XI_MONO16:
        case XI_RAW16: cv_image_ = cvCreateImage(cvSize(next_image_->GetWidth(), next_image_->GetHeight()), IPL_DEPTH_16U, 1); printf("Doing reset to mono\n"); break;
        case XI_RGB24:
        case XI_RGB_PLANAR: cv_image_ = cvCreateImage(cvSize(next_image_->GetWidth(), next_image_->GetHeight()), IPL_DEPTH_8U, 3);  printf("Doing reset to RGB\n");; break;
        case XI_RGB32: cv_image_ = cvCreateImage(cvSize(next_image_->GetWidth(), next_image_->GetHeight()), IPL_DEPTH_8U, 4);   printf("Doing reset to RGB\n");; break;
        default:
            printf("CvCaptureCAM_XIMEA::resetCvImage ERROR: Unknown format.");
            return;
        }
    }
    return;
}

#endif // #ifdef 0
} // end namespace xi
