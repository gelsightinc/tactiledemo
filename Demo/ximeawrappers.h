#pragma once
#ifndef XIMEAWRAPPERS_H
#define XIMEAWRAPPERS_H


#include "xiapi.h"
#include <string>
#include "stdutil.h"
#include "gsassert.h"
#include "stdstream.h"




#pragma region XIAPIEXT

// JMO:  Copied the following parameters from Ximea example "xiApiPlusOcvExample"
// Don't know why they not provided in a normal include header file with the SDK.
// If we ever get that file (which I expect to be included in future versions
// of the SDK), then this section should be jettisoned.

//-------------------------------------------------------------------------------------------------------------------
// xiApi Extension header file

// Generated for xiAPI version 0.0.5027

#ifndef __XIAPIEXT_H
#define __XIAPIEXT_H

//-------------------------------------------------------------------------------------------------------------------
// xiApiExtended parameters

#define  XI_PRM_LENS_COMM_DATA                  "lens_comm_data"          // Write/Read data sequences to/from lens 
#define  XI_PRM_DEVICE_ID                       "device_id"               // Return unique device ID 
#define  XI_PRM_IMAGE_CORRECTION_SELECTOR       "image_correction_selector"// Select image correction function XI_IMAGE_CORRECTION_SELECTOR
#define  XI_PRM_IMAGE_CORRECTION_VALUE          "image_correction_value"  // Select image correction selected function value 
#define  XI_PRM_CAM_ENUM_GOLDEN_ENABLED         "cam_enum_golden_enabled" // Enable enumeration of golden devices 
#define  XI_PRM_CAM_SIMULATORS_COUNT            "cam_simulators_count"    // Number of camera simulators to be available. 
#define  XI_PRM_CAM_SENSOR_INIT_DISABLED        "cam_sensor_init_disabled"// Camera sensor will not be initialized when 1=XI_ON is set. 
#define  XI_PRM_EXTENDED_FEATURE_SELECTOR       "ext_feature_selector"    // Selection of extended feature. XI_EXT_FEATURE_SELECTOR
#define  XI_PRM_EXTENDED_FEATURE                "ext_feature"             // Extended feature value. 
#define  XI_PRM_DEVICE_UNIT_SELECTOR            "device_unit_selector"    // Selects device unit. XI_DEVICE_UNIT_SELECTOR
#define  XI_PRM_DEVICE_UNIT_REGISTER_SELECTOR   "device_unit_register_selector"// Selects register of selected device unit(XI_PRM_DEVICE_UNIT_SELECTOR). 
#define  XI_PRM_DEVICE_UNIT_REGISTER_VALUE      "device_unit_register_value"// Sets/gets register value of selected device unit(XI_PRM_DEVICE_UNIT_SELECTOR). 


inline std::string EnumName(XI_IMG_FORMAT idf)
{
    switch(idf)
    {
    default: return "Unknown" + std::to_string((int)idf);

    case XI_MONO8:              return "XI_MONO8";               // 8 bits per pixel
    case XI_MONO16:             return "XI_MONO16";              // 16 bits per pixel
    case XI_RGB24:              return "XI_RGB24";               // RGB data format
    case XI_RGB32:              return "XI_RGB32";               // RGBA data format
    case XI_RGB_PLANAR:         return "XI_RGB_PLANAR";          // RGB planar data format
    case XI_RAW8:               return "XI_RAW8";                // 8 bits per pixel raw data from sensor
    case XI_RAW16:              return "XI_RAW16";               // 16 bits per pixel raw data from sensor
    case XI_FRM_TRANSPORT_DATA: return "XI_FRM_TRANSPORT_DATA";  // Data from transport layer (e.g. packed). Format see XI_PRM_TRANSPORT_PIXEL_FORMAT
	
    };
}

//-------------------------------------------------------------------------------------------------------------------
// xiAPI enumerators
// Image correction function
typedef enum
{
    XI_CORRECTION_TYPE_SELECTOR = 0, // Correction Type selected see XI_TYPE_CORRECTION_SELECTOR
    XI_DEFECT_ID                = 1, // Select defect id
    XI_DEFECTS_COUNT_BY_TYPE    = 2, // Count of defects selected by current XI_DEFECT_TYPE
    XI_DEFECT_TYPE              = 3, // Type of defect see XI_IMAGE_DEFECT_TYPE
    XI_DEFECT_SUB_TYPE          = 4, // Defect sub type see XI_IMAGE_DEFECT_SUB_TYPE
    XI_DEFECT_POS_X             = 5, // Defect position x
    XI_DEFECT_POS_Y             = 6, // Defect position y
    XI_DEFECT_CMD_ADD           = 7, // Write cached defect to the list
    XI_DEFECT_CMD_DELETE        = 8, // Delete defect to the list
    XI_DEFECT_CMD_APPLY_CHANGES = 9, // Apply changes
    XI_DEFECT_CMD_LIST_CLEAR    = 10, // Clear list
    XI_DEFECT_CMD_LISTS_CLEAR   = 11, // Clear lists
    XI_DEFECT_CMD_SAVE          = 12, // Save list to device
    XI_CORRECTION_TYPE_ENABLED  = 13, // Enable or disable correction type
    XI_DEFECT_ID_BY_TYPE        = 14, // Select defect id by type

} XI_IMAGE_CORRECTION_SELECTOR;

// Define image  correction type
typedef enum
{
    XI_CORR_TYPE_SENSOR_DEFECTS_FACTORY = 0, // Factory defect list
    XI_CORR_TYPE_SENSOR_COLUMN_FPN      = 1, // Select Fixed Pattern Noise Correction for Columns
    XI_CORR_TYPE_SENSOR_ADC_BLO         = 2, // ADC gain and black level offset sensor register correction
    XI_CORR_TYPE_SENSOR_ROW_FPN         = 3, // Select Fixed Pattern Noise Correction for Rows

} XI_TYPE_CORRECTION_SELECTOR;

// Define image defect types
typedef enum
{
    XI_IMAGE_DEFECT_TYPE_PIXEL  = 0, // Defect is bad pixel
    XI_IMAGE_DEFECT_TYPE_COLUMN = 1, // Defect is bad column
    XI_IMAGE_DEFECT_TYPE_ROW    = 2, // Defect is bad row

} XI_IMAGE_DEFECT_TYPE;

// Define image defect sub types
typedef enum
{
    XI_IMAGE_DEFECT_SUB_TYPE_DARK   = 0, // Defect pixel(s) is(are) too dark
    XI_IMAGE_DEFECT_SUB_TYPE_BRIGHT = 1, // Defect pixel(s) is(are) out of range
    XI_IMAGE_DEFECT_SUB_TYPE_HOT    = 2, // Defect pixel(s) is(are) too bright

} XI_IMAGE_DEFECT_SUB_TYPE;

// Extended feature selector.
typedef enum
{
    XI_EXT_FEATURE_SEL_SIMULATOR_GENERATOR_FRAME_LOST_PERIOD_MIN = 1, // Camera simulator lost frame generation minimum period (in frames).
    XI_EXT_FEATURE_SEL_SIMULATOR_GENERATOR_FRAME_LOST_PERIOD_MAX = 2, // Camera simulator lost frame generation random period (in frames).
    XI_EXT_FEATURE_SEL_SIMULATOR_IMAGE_DATA_FORMAT               = 3, // Camera simulator image data format.
    XI_EXT_FEATURE_SEL_BANDWIDTH_MEASUREMENT_TIME_SECONDS        = 4, // Number of seconds for bandwidth measurement. Default = 1.
    XI_EXT_FEATURE_SEL_IMAGE_INTENSIFIER_VOLTAGE                 = 5, // Input voltage for image intensifier. Default = 0.
    XI_EXT_FEATURE_SEL_TRIG_FRAME                                = 6, // Triggers frame(s) on internal event. Default = 0.
    XI_EXT_FEATURE_SEL_IMAGE_OVERSAMPLING                        = 7, // Enable/disable image pixels oversampling. Default = 0.

} XI_EXT_FEATURE_SELECTOR;

// Device unit selector
typedef enum
{
    XI_DEVICE_UNIT_SENSOR1  = 0, // Selects first sensor on device
    XI_DEVICE_UNIT_FPGA1    = 1, // Selects first FPGA on device
    XI_DEVICE_UNIT_SAL      = 2, // Selects sensor abstraction layer
    XI_DEVICE_UNIT_DAL      = 3, // Selects driver abstraction layer
    XI_DEVICE_UNIT_SCM      = 4, // Selects sensor correction module
    XI_DEVICE_UNIT_FGENTL   = 5, // Selects register in underlying GenTL layer
    XI_DEVICE_UNIT_MCU1     = 6, // Selects first MCU on device
    XI_DEVICE_UNIT_MCU2     = 7, // Selects second MCU on device
    XI_DEVICE_UNIT_CHF      = 8, // Selects Camera High Features Model

} XI_DEVICE_UNIT_SELECTOR;

// Camera sensor mode enumerator.
typedef enum
{
    XI_SENS_MD0     =  0,   // Sensor mode number  0
    XI_SENS_MD1     =  1,   // Sensor mode number  1
    XI_SENS_MD2     =  2,   // Sensor mode number  2
    XI_SENS_MD3     =  3,   // Sensor mode number  3
    XI_SENS_MD4     =  4,   // Sensor mode number  4
    XI_SENS_MD5     =  5,   // Sensor mode number  5
    XI_SENS_MD6     =  6,   // Sensor mode number  6
    XI_SENS_MD7     =  7,   // Sensor mode number  7
    XI_SENS_MD8     =  8,   // Sensor mode number  8
    XI_SENS_MD9     =  9,   // Sensor mode number  9
    XI_SENS_MD10    = 10,   // Sensor mode number 10
    XI_SENS_MD11    = 11,   // Sensor mode number 11
    XI_SENS_MD12    = 12,   // Sensor mode number 12
    XI_SENS_MD13    = 13,   // Sensor mode number 13
    XI_SENS_MD14    = 14,   // Sensor mode number 14
    XI_SENS_MD15    = 15,   // Sensor mode number 15

} XI_SENSOR_MODE;

// Camera channel count enumerator.
typedef enum
{
    XI_CHANN_CNT2   = 2,    // 2 sensor readout channels.
    XI_CHANN_CNT4   = 4,    // 4 sensor readout channels.
    XI_CHANN_CNT8   = 8,    // 8 sensor readout channels.
    XI_CHANN_CNT16  = 16,   // 16 sensor readout channels.
    XI_CHANN_CNT32  = 32,   // 32 sensor readout channels.

} XI_SENSOR_OUTPUT_CHANNEL_COUNT;


#endif /* __XIAPIEXT_H */
#pragma endregion XIAPIEXT



inline std::string EnumName(XI_ACQ_TIMING_MODE v)
{
    switch (v)
    {
    default: ASSERT(false); return "Unknown " + std::to_string(v);
    case XI_ACQ_TIMING_MODE_FREE_RUN:           return "Free-Run";
    case XI_ACQ_TIMING_MODE_FRAME_RATE:         return "FrameRate";
    case XI_ACQ_TIMING_MODE_FRAME_RATE_LIMIT:   return "FrameRateLimit";
    }
}

namespace xi
{

inline bool XIOK(int err)   { return XI_OK == err; }
inline bool XIFAIL(int err) { return XI_OK != err; }

__declspec(noreturn) inline void xiThrow(int err, const std::string& msg = "");
void xiCheck(XI_RETURN ret, const std::string msg="");


// xiSetParam and xiGetParam
// -------------------------
// Use function overloading to create our own versions of xiGetParamXXXX and
// xiSetParamXXXS functions.  Now we don't have to call a differently named
// function for every single type.  It will simplify using these in templates.

// xiSetParamXXX wrappers
inline XI_RETURN xiSetParam(HANDLE h, PCSTR p, bool v)           { return xiSetParamInt(h, p, (int)v);  }
inline XI_RETURN xiSetParam(HANDLE h, PCSTR p, int v)            { return xiSetParamInt(h, p, v);       }
inline XI_RETURN xiSetParam(HANDLE h, PCSTR p, float v)          { return xiSetParamFloat(h, p, v);     }
inline XI_RETURN xiSetParam(HANDLE h, PCSTR p, void* v, DWORD s) { return xiSetParamString(h, p, v, s); }   
inline XI_RETURN xiSetParam(HANDLE h, PCSTR p, const std::string& v) 
{
    return xiSetParam(h, p, const_cast<char*>(v.c_str()), v.size());
}   

// xiGetParamXXX
inline XI_RETURN xiGetParam(HANDLE h, PCSTR p, int& v)            { return xiGetParamInt(h, p, &v);     }
inline XI_RETURN xiGetParam(HANDLE h, PCSTR p, float& v)          { return xiGetParamFloat(h, p, &v);   }
inline XI_RETURN xiGetParam(HANDLE h, PCSTR p, std::string& v)
{
    char buf[300] = {0};
    const auto val = xiGetParamString(h, p, buf, 299);
    if (XIOK(val))
        v = buf;

    return val;
}
inline XI_RETURN xiGetParam(HANDLE h, PCSTR p, bool& v)           
{
    int out = 0;
    const auto ret = xiGetParam(h, p, out);   
    if (XIOK(ret))
        v = 0 != out;

    return ret;
}
/*

struct XiIntTag {};
struct XiEnumTag {};
struct XiFloatTag {};
struct XiStringTag {};

template<class T, XI_PRM_TYPE XITYPE>
class XiParamBase
{
    std::string m_prm;
    HANDLE      m_hDev;

protected:
    XI_RETURN get(T& v, const std::string& prm) const { return xiGetParam(m_hDev, prm, &v, sizeof(T), XITYPE); }
public:

    typedef XITYPE xiType;
    const std::string& prm() const { return m_prm; }
    XiParamBase(HANDLE hDev, const char* p) : m_hDev(hDev), m_prm(p ? p : "") { };
    XI_RETURN value(T& v)   const { return get(v, m_prm); }
    operator T
    XI_RETURN min(T& v)     const { return get(v, m_prm + XI_PRM_INFO_MIN)); } 
    XI_RETURN max(T& v)     const { return get(v, m_prm + XI_PRM_INFO_MAX)); }
    XI_RETURN inc(T& v)     const;
};
template<class T, XI_PRM_TYPE XITYPE, class Enable=enable_if_numeric<T>::type>
class XiParamBase
{
    std::string m_prm;
    HANDLE      m_hDev;

protected:
    XI_RETURN get(T& v, const std::string& prm) const { return ::xiGetParam(m_hDev, prm, &v, sizeof(T), XITYPE); }
public:
    XiParam(HANDLE hDev, const char* prm) : m_hDev(hDev), m_prm(prm ? prm : "") { };
    XI_RETURN value(T& v)   const { return get(v, m_prm); }
    operator T
    XI_RETURN min(T& v)     const { return get(v, m_prm + XI_PRM_INFO_MIN)); } 
    XI_RETURN max(T& v)     const { return get(v, m_prm + XI_PRM_INFO_MAX)); }
    XI_RETURN inc(T& v)     const;
};
*/

inline std::string ErrorString(XI_RETURN xr)
{
    switch(xr)
    {
    default:                                  return "Unknown Error" + std::to_string(xr);
    case XI_OK:                               return "Function call succeeded";
    case XI_INVALID_HANDLE:                   return "Invalid handle";
    case XI_READREG:                          return "Register read error";
    case XI_WRITEREG:                         return "Register write error";
    case XI_FREE_RESOURCES:                   return "Freeing resources error";
    case XI_FREE_CHANNEL:                     return "Freeing channel error";
    case XI_FREE_BANDWIDTH:                   return "Freeing bandwith error";
    case XI_READBLK:                          return "Read block error";
    case XI_WRITEBLK:                         return "Write block error";
    case XI_NO_IMAGE:                         return "No image";
    case XI_TIMEOUT:                          return "Timeout";
    case XI_INVALID_ARG:                      return "Invalid arguments supplied";
    case XI_NOT_SUPPORTED:                    return "Not supported";
    case XI_ISOCH_ATTACH_BUFFERS:             return "Attach buffers error";
    case XI_GET_OVERLAPPED_RESULT:            return "Overlapped result";
    case XI_MEMORY_ALLOCATION:                return "Memory allocation error";
    case XI_DLLCONTEXTISNULL:                 return "DLL context is NULL";
    case XI_DLLCONTEXTISNONZERO:              return "DLL context is non zero";
    case XI_DLLCONTEXTEXIST:                  return "DLL context exists";
    case XI_TOOMANYDEVICES:                   return "Too many devices connected";
    case XI_ERRORCAMCONTEXT:                  return "Camera context error";
    case XI_UNKNOWN_HARDWARE:                 return "Unknown hardware";
    case XI_INVALID_TM_FILE:                  return "Invalid TM file";
    case XI_INVALID_TM_TAG:                   return "Invalid TM tag";
    case XI_INCOMPLETE_TM:                    return "Incomplete TM";
    case XI_BUS_RESET_FAILED:                 return "Bus reset error";
    case XI_NOT_IMPLEMENTED:                  return "Not implemented";
    case XI_SHADING_TOOBRIGHT:                return "Shading is too bright";
    case XI_SHADING_TOODARK:                  return "Shading is too dark";
    case XI_TOO_LOW_GAIN:                     return "Gain is too low";
    case XI_INVALID_BPL:                      return "Invalid bad pixel list";
    case XI_BPL_REALLOC:                      return "Bad pixel list realloc error";
    case XI_INVALID_PIXEL_LIST:               return "Invalid pixel list";
    case XI_INVALID_FFS:                      return "Invalid Flash File System";
    case XI_INVALID_PROFILE:                  return "Invalid profile";
    case XI_INVALID_CALIBRATION:              return "Invalid calibration";
    case XI_INVALID_BUFFER:                   return "Invalid buffer";
    case XI_INVALID_DATA:                     return "Invalid data";
    case XI_TGBUSY:                           return "Timing generator is busy";
    case XI_IO_WRONG:                         return "Wrong operation open/write/read/close";
    case XI_ACQUISITION_ALREADY_UP:           return "Acquisition already started";
    case XI_OLD_DRIVER_VERSION:               return "Old version of device driver installed to the system.";
    case XI_GET_LAST_ERROR:                   return "To get error code please call GetLastError function.";
    case XI_CANT_PROCESS:                     return "Data cannot be processed";
    case XI_ACQUISITION_STOPED:               return "Acquisition is stopped. It needs to be started to perform operation.";
    case XI_ACQUISITION_STOPED_WERR:          return "Acquisition has been stopped with an error.";
    case XI_INVALID_INPUT_ICC_PROFILE:        return "Input ICC profile missing or corrupted";
    case XI_INVALID_OUTPUT_ICC_PROFILE:       return "Output ICC profile missing or corrupted";
    case XI_DEVICE_NOT_READY:                 return "Device not ready to operate";
    case XI_SHADING_TOOCONTRAST:              return "Shading is too contrast";
    case XI_ALREADY_INITIALIZED:              return "Module already initialized";
    case XI_NOT_ENOUGH_PRIVILEGES:            return "Application does not have enough privileges (one or more app)";
    case XI_NOT_COMPATIBLE_DRIVER:            return "Installed driver is not compatible with current software";
    case XI_TM_INVALID_RESOURCE:              return "TM file was not loaded successfully from resources";
    case XI_DEVICE_HAS_BEEN_RESETED:          return "Device has been reset, abnormal initial state";
    case XI_NO_DEVICES_FOUND:                 return "No Devices Found";
    case XI_RESOURCE_OR_FUNCTION_LOCKED:      return "Resource (device) or function locked by mutex";
    case XI_BUFFER_SIZE_TOO_SMALL:            return "Buffer provided by user is too small";
    case XI_COULDNT_INIT_PROCESSOR:           return "Couldnt initialize processor.";
    case XI_NOT_INITIALIZED:                  return "The object/module/procedure/process being referred to has not been started.";
    case XI_RESOURCE_NOT_FOUND:               return "Resource not found(could be processor, file, item...).";
    case XI_UNKNOWN_PARAM:                    return "Unknown parameter";
    case XI_WRONG_PARAM_VALUE:                return "Wrong parameter value";
    case XI_WRONG_PARAM_TYPE:                 return "Wrong parameter type";
    case XI_WRONG_PARAM_SIZE:                 return "Wrong parameter size";
    case XI_BUFFER_TOO_SMALL:                 return "Input buffer is too small";
    case XI_NOT_SUPPORTED_PARAM:              return "Parameter is not supported";
    case XI_NOT_SUPPORTED_PARAM_INFO:         return "Parameter info not supported";
    case XI_NOT_SUPPORTED_DATA_FORMAT:        return "Data format is not supported";
    case XI_READ_ONLY_PARAM:                  return "Read only parameter";
    case XI_BANDWIDTH_NOT_SUPPORTED:          return "This camera does not support currently available bandwidth";
    case XI_INVALID_FFS_FILE_NAME:            return "FFS file selector is invalid or NULL";
    case XI_FFS_FILE_NOT_FOUND:               return "FFS file not found";
    case XI_PARAM_NOT_SETTABLE:               return "Parameter value cannot be set (might be out of range or invalid).";
    case XI_SAFE_POLICY_NOT_SUPPORTED:        return "Safe buffer policy is not supported. E.g. when transport target is set to GPU (GPUDirect).";
    case XI_GPUDIRECT_NOT_AVAILABLE:          return "GPUDirect is not available. E.g. platform isn't supported or CUDA toolkit isn't installed.";
    case XI_PROC_OTHER_ERROR:                 return "Processing error - other";
    case XI_PROC_PROCESSING_ERROR:            return "Error while image processing.";
    case XI_PROC_INPUT_FORMAT_UNSUPPORTED:    return "Input format is not supported for processing.";
    case XI_PROC_OUTPUT_FORMAT_UNSUPPORTED:   return "Output format is not supported for processing.";
    case XI_OUT_OF_RANGE:                     return "Parameter value is out of range";
    };
}


class Exception : public std::exception
{
public:
    Exception(XI_RETURN code) : m_err(code), m_desc(ErrorString(code))
    {
    }
    Exception(XI_RETURN code, const std::string& desc) 
        : m_err(code)
        , m_desc(desc.empty() ? ErrorString(code) : desc + ":" + ErrorString(code))
    {
    }
    XI_RETURN       error() { return m_err; }
    virtual         const char* what() const override { return m_desc.c_str(); }

private:
    std::string     m_desc;
    XI_RETURN       m_err;
};


class Camera
{
            HANDLE      m_hDevice;
            bool        m_bAcquiring;

    Camera();

public:
    Camera(XI_OPEN_BY sel, const char* prm);
    Camera(XI_OPEN_BY sel, const std::string& prm);
    Camera(DWORD id);
    virtual ~Camera() { close(); }

    void        open(XI_OPEN_BY sel, const char* prm);
    void        open(DWORD devId);

    bool        isOpen() const;
    void        close();
    void        startAcquisition();
    void        stopAcquisition();
    bool        isAcquiring() const { return m_bAcquiring; }
    XI_IMG      image(DWORD dwTimeout) const;           // throws on any failure to retrieve image
    XI_RETURN   getImage(DWORD timeout, XI_IMG& img) const;// throws on any failure *except* XI_TIMEOUT;
    bool        isColor() const { return SensorIsColor; }

    // Get a camera parameter


    template<typename T>
    bool getParamImpl(PCSTR prm, T& v, std::false_type) const
    {
        ASSERT(isOpen());
        const auto val = xiGetParam(m_hDevice, prm, v);
        xiCheck(val, std::string("getting param ") + (prm ? prm : ""));



        if (!XIOK(val))
            STDERR("ERROR: Ximea GET \"" << prm << "\" FAILS");

        return XIOK(val);
    }
    template<typename T>
    bool getParamImpl(PCSTR prm, T& v, std::true_type) const
    {
        // Enum version calls the integer-based version and then converts

        auto vi = int();
        const auto ok = getParamImpl(prm, vi, std::false_type());
        if (ok)
            v = static_cast<T>(vi);

        return ok;
    }
    template<typename T>
    bool getParam(PCSTR prm, T& v) const
    {
        return getParamImpl(prm, v, std::is_enum<T>());
    }
    template<typename T>
    bool getParam(const std::string& prm, T& v) const
    {
        return getParamImpl(prm.c_str(), v, std::is_enum<T>());
    }
   

    // Set a camera parameter

    template<typename T>
    bool setParam(PCSTR prm, const T& v) const
    {
        ASSERT(isOpen());
        const auto val = xiSetParam(m_hDevice, prm, v);
        xiCheck(val, std::string("setting ") + (prm ? prm : ""));
        return XIOK(val);
    }


    // return a camera parameter
    // This currently returns a default value on failure but I think it should
    // probably throw.  If they want the safe version that does not throw, they
    // can call getParam (above).  But for now, this Ximea SDK is a bit flaky
    // so I am returning a default

    template<typename T>
    T param(const char* prm) const
    {
        auto out = T();
        getParam(prm, out);
        return out;
    }


    /*
    static int getInfoInt(DWORD dwDevId, const char* prm, int v)
    {
    }
    */
    static  std::string infoString(DWORD devId, const char* prm);
    static  std::string serialNumber(DWORD devId);
    static  DWORD       count();

    // FUNCTION DECLARATION MACROS
    // ---------------------------
    // Ximea numerical parameters appear follow a pattern.  You have:
    //      - the basic readable value (get)    e.g. getGain()
    //      - some props are writable (set)     e.g. setGain()
    //      - some are bounded (min/max)        e.g. getGainMin()/getGainMax() 
    //      - some can be iterated (inc)        e.g. getGainSelectorInc()
    //
    // It would be folly to write the same functions over and over again for
    // the innumerable camera properties we deal with so instead we will use 
    // some macros to do the job for us.
    //
    // As these functions are  declared inline, we'll only end up linking in the
    // ones that we actually call.

    // BASE_PROP
    // ---------
    // All properties have a get function that comes in two versions.  One
    // version returns the retrieved value and throws on failure.  The other 
    // returns a boolean indicating success/failure and takes the retrieved
    // value as an in/out param.  The second version does not throw. 
    //
    // e.g. auto x = cam->getGain();        // throws if unsuccessful
    //      if (!cam->getGain(x))...
    //
    // PT = Parameter Type  (e.g. integer, float, bool, some enum type)
    // PN = Parameter Name  (used by our client code to get and set)
    // PK = Parameter Key   (used by function to tell Ximea SDK which param we mean)

    #define BASE_PROP(PT, PN, PK)                                   \
        PT      get##PN() const  { return param<PT>(PK); }          \
        bool    get##PN(PT& v) const { return getParam(PK, v); }
    


    // READONLY_PROP
    // -------------
    // Read only properties allow you to get the value via the property name
    // e.g. 
    //
    //      auto x = cam->Gain 
    //
    // instead of 
    //
    //      auto x = cam->getGain();

    #define READONLY_PROP(PT, PN, PK) __declspec(property(get=get##PN)) PT PN; 


    // READWRITE_PROP
    // --------------
    // ReadWrite properties allow you to both GET and SET the value via the name
    // e.g. 
    //
    //      cam->Gain = 0.7;
    //
    // instead of
    //
    //      cam->setGain(0.7);

    #define READWRITE_PROP(PT, PN, PK)                              \
            bool        set##PN(PT v) { return setParam(PK, v); }   \
            __declspec(property(get=get##PN, put=set##PN))       PT PN; 


    // BOUNDED_PROP
    // ------------
    // Bounded properties have a Min and Max (which are read only) These bounds 
    // also have the ability to be read via the property name (e.g. GainMin, 
    // GainMax) instead of calling getXXXMin/getXXXMax().

    #define BOUNDED_PROP(PT, PN, PK)                                                            \
            PT         get##PN##Max() const         { return param<PT>(PK XI_PRM_INFO_MAX); }   \
            PT         get##PN##Min() const         { return param<PT>(PK XI_PRM_INFO_MIN); }   \
            __declspec(property(get=get##PN##Max))   PT PN##Max;                                \
            __declspec(property(get=get##PN##Min))   PT PN##Min;                                       


    // ITERABLE_PROP
    // -------------
    // Iterable properties have an increment (as far as I know, only enums and integers)

    #define ITERABLE_PROP(PN, PK)   \
        int get##PN##Inc() const   { return param<int>(PK XI_PRM_INFO_INCREMENT); } \
         __declspec(property(get=get##PN##Inc))      int PN##Inc;   

    // INTEGERS
    // Integer properties are bounded and iterable

    #define INTEGER_PROP(PN, PK)                        \
            BASE_PROP(int, PN, PK)                      \
            BOUNDED_PROP(int, PN, PK)                   \
            ITERABLE_PROP(PN, PK)

    #define INTG_RO(PN, PK)     INTEGER_PROP(PN, PK);       READONLY_PROP(int, PN, PK);
    #define INTG_RW(PN, PK)     INTEGER_PROP(PN, PK);       READWRITE_PROP(int, PN, PK);
   
    // ENUM properties are also bounded and iterable but have an associate enum type

     #define ENUM_PROP(PN, PK, PT)                      \
            BASE_PROP(PT, PN, PK)                       \
            BOUNDED_PROP(PT, PN, PK)                    \
            ITERABLE_PROP(PN, PK)                       

    #define ENUM_RO(PN, PK, PT) ENUM_PROP(PN, PK, PT);          READONLY_PROP(PT, PN, PK);
    #define ENUM_RW(PN, PK, PT) ENUM_PROP(PN, PK, PT);          READWRITE_PROP(PT, PN, PK);

    // Float properties are just bounded.  It does not appear to be valid to try
    // to iterate through them, as far as I can tell in my testing

    #define FLOAT_PROP(PN, PK)  BASE_PROP(float, PN, PK);       BOUNDED_PROP(float, PN, PK)                   
    #define FLOA_RO(PN, PK)     FLOAT_PROP(PN, PK);             READONLY_PROP(float, PN, PK)
    #define FLOA_RW(PN, PK)     FLOAT_PROP(PN, PK);             READWRITE_PROP(float, PN, PK);

    // Bools and strings are simplest of all.  No bounds, no increments.

    #define BOOL_RO(PN, PK)     BASE_PROP(bool, PN, PK);        READONLY_PROP(bool, PN, PK);
    #define BOOL_RW(PN, PK)     BASE_PROP(bool, PN, PK);        READWRITE_PROP(bool, PN, PK)

    #define STRI_RO(PN, PK)     BASE_PROP(std::string, PN, PK); READONLY_PROP(std::string, PN, PK)
    #define STRI_RW(PN, PK)     BASE_PROP(std::string, PN, PK); READWRITE_PROP(std::string, PN, PK)


    //--------------------------------------------------------------------------
    // ---- Parameter Group: Basic
    //--------------------------------------------------------------------------

    INTG_RW(ExposureTime,               XI_PRM_EXPOSURE);               
    INTG_RW(ExposureBurstCount,         XI_PRM_EXPOSURE_BURST_COUNT);
    ENUM_RW(GainSelector,               XI_PRM_GAIN_SELECTOR,                   XI_GAIN_SELECTOR_TYPE);
    FLOA_RW(Gain,                       XI_PRM_GAIN);
    ENUM_RW(Downsampling,               XI_PRM_DOWNSAMPLING,                    XI_DOWNSAMPLING_VALUE);
    ENUM_RW(BinningSelector,            XI_PRM_BINNING_SELECTOR,                XI_BIN_SELECTOR);
    INTG_RW(BinningVertical,            XI_PRM_BINNING_VERTICAL);
    INTG_RW(BinningHorizontal,          XI_PRM_BINNING_HORIZONTAL);
    ENUM_RO(BinningHorizontalPattern,   XI_PRM_BINNING_HORIZONTAL_PATTERN,      XI_BIN_PATTERN);  
    ENUM_RW(BinningVerticalPattern,     XI_PRM_BINNING_VERTICAL_PATTERN,        XI_BIN_PATTERN);
    ENUM_RW(DecimationSelector,         XI_PRM_DECIMATION_SELECTOR,             XI_DEC_SELECTOR);
    INTG_RW(DecimationVertical,         XI_PRM_DECIMATION_VERTICAL);
    INTG_RW(DecimationHorizontal,       XI_PRM_DECIMATION_HORIZONTAL);
    ENUM_RW(DecimationHorizontalPattern,XI_PRM_DECIMATION_HORIZONTAL_PATTERN,   XI_DEC_PATTERN);
    ENUM_RW(DecimationVerticalPattern,  XI_PRM_DECIMATION_VERTICAL_PATTERN,     XI_DEC_PATTERN);
    ENUM_RW(TestPatternGenSelector,     XI_PRM_TEST_PATTERN_GENERATOR_SELECTOR, XI_TEST_PATTERN_GENERATOR);
    ENUM_RW(TestPattern,                XI_PRM_TEST_PATTERN,                    XI_TEST_PATTERN);
    ENUM_RW(ImageDataFormat,            XI_PRM_IMAGE_DATA_FORMAT,               XI_IMG_FORMAT);
    ENUM_RW(ShutterType,                XI_PRM_SHUTTER_TYPE,                    XI_SHUTTER_TYPE);
    ENUM_RW(SensorTaps,                 XI_PRM_SENSOR_TAPS,                     XI_SENSOR_TAP_CNT);
    INTG_RW(AeagRoiOffsetX,             XI_PRM_AEAG_ROI_OFFSET_X);
    INTG_RW(AeagRoiOffsetY,             XI_PRM_AEAG_ROI_OFFSET_Y);
    INTG_RW(AeagRoiWidth,               XI_PRM_AEAG_ROI_WIDTH);
    INTG_RW(AeagRoiHeight,              XI_PRM_AEAG_ROI_HEIGHT);
    BOOL_RW(BadPixelCorrelation,        XI_PRM_BPC);                            // Correction of bad pixels
    BOOL_RW(WbAuto,                     XI_PRM_AUTO_WB);                        // Automatic white balance
    INTG_RW(WbManualNow,                XI_PRM_MANUAL_WB);                      // Calculates White Balance(xiGetImage function must be called)
    FLOA_RW(WbRed,                      XI_PRM_WB_KR);                          // White balance red coefficient 
    FLOA_RW(WbGreen,                    XI_PRM_WB_KG);                          // White balance green coefficient
    FLOA_RW(WbBlue,                     XI_PRM_WB_KB);                          // White balance blue coefficient 
    INTG_RW(Width,                      XI_PRM_WIDTH);                          // Width of the Image provided by the device (in pixels)
    INTG_RW(Height,                     XI_PRM_HEIGHT);                         // Height of the Image provided by the device (in pixels)
    INTG_RW(OffsetX,                    XI_PRM_OFFSET_X);                       // Horizontal offset from the origin to the area of interest (in pixels). (XI_PRM_OFFSET_X)
    INTG_RW(OffsetY,                    XI_PRM_OFFSET_Y);                       // Vertical offset from the origin to the area of interest (in pixels). (XI_PRM_OFFSET_Y)
    INTG_RW(RegionSelector,             XI_PRM_REGION_SELECTOR);                // Selects Region in Multiple ROI which parameters are set by width, height, ... ,region mode 
    INTG_RW(RegionMode,                 XI_PRM_REGION_MODE);                    // Activates/deactivates Region selected by Region Selector (XI_PRM_REGION_MODE )
    BOOL_RW(HorizontalFlip,             XI_PRM_HORIZONTAL_FLIP);                // Horizontal flip enable (XI_PRM_HORIZONTAL_FLIP)
    BOOL_RW(VerticalFlip,               XI_PRM_VERTICAL_FLIP);                  // Vertical flip enable (XI_PRM_VERTICAL_FLIP)
    BOOL_RW(Ffc,                        XI_PRM_FFC);                            // Image flat field correction (XI_PRM_FFC)
    STRI_RW(FfcFlatFieldFileName,       XI_PRM_FFC_FLAT_FIELD_FILE_NAME);       // Set name of file to be applied for FFC processor.
    STRI_RW(FfcDarkFieldFileName,       XI_PRM_FFC_DARK_FIELD_FILE_NAME);       // Set name of file to be applied for FFC processor.


    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: AE Setup
    //-------------------------------------------------------------------------------------------------------------------

    FLOA_RW(AeagExposurePriority,       XI_PRM_EXP_PRIORITY);                   // Exposure priority (0.8 - exposure 80%, gain 20%).
    FLOA_RW(AutoGainTopLimit,           XI_PRM_AG_MAX_LIMIT);                   // Maximum limit of gain in AEAG procedure
    INTG_RW(AutoExposureTopLimit,       XI_PRM_AE_MAX_LIMIT);                   // Maximum time (us);used for exposure in AEAG procedure 
    INTG_RW(AeagTargetLevel,            XI_PRM_AEAG_LEVEL);                     // Average intensity of output signal AEAG should achieve(in %);


    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Performance
    //-------------------------------------------------------------------------------------------------------------------

    INTG_RW(BwLimit,                    XI_PRM_LIMIT_BANDWIDTH);                                            // Set/get bandwidth(datarate)(in Megabits);
    ENUM_RW(BwLimitMode,                XI_PRM_LIMIT_BANDWIDTH_MODE,        XI_SWITCH);                     // Bandwidth limit enabled 
    ENUM_RW(SensorBitDepth,             XI_PRM_SENSOR_DATA_BIT_DEPTH,       XI_BIT_DEPTH);                  // Sensor output data bit depth. 
    ENUM_RW(OutputBitDepth,             XI_PRM_OUTPUT_DATA_BIT_DEPTH,       XI_BIT_DEPTH);                  // Device output data bit depth. 
    BOOL_RW(OutputDataPacking,          XI_PRM_OUTPUT_DATA_PACKING);                                        // Device output data packing (or grouping);enabled. Packing could be enabled if output_data_bit_depth > 8 and packing capability is available. 
    ENUM_RW(OutputDataPackingType,      XI_PRM_OUTPUT_DATA_PACKING_TYPE,    XI_OUTPUT_DATA_PACKING_TYPE);   // Data packing type. Some cameras supports only specific packing type. 


    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Temperature
    //-------------------------------------------------------------------------------------------------------------------

    BOOL_RO(Cooled,                     XI_PRM_IS_COOLED);                          // Returns 1 for cameras that support cooling.
    BOOL_RW(Cooling,                    XI_PRM_COOLING);                            // Start camera cooling. 
    FLOA_RW(TargetTemp,                 XI_PRM_TARGET_TEMP);                        // Set sensor target temperature for cooling. 
    ENUM_RW(TempSelector,               XI_PRM_TEMP_SELECTOR,   XI_TEMP_SELECTOR);  // Selector of mechanical point where thermometer is located
    FLOA_RW(Temp,                       XI_PRM_TEMP);                               // Camera temperature (selected by XI_PRM_TEMP_SELECTOR)
    FLOA_RW(TempSensor,                 XI_PRM_CHIP_TEMP);                          // Camera sensor temperature (XI_PRM_CHIP_TEMP)
    FLOA_RW(TempHousing,                XI_PRM_HOUS_TEMP);                          // Camera housing tepmerature
    FLOA_RW(TempHousingBackSide,        XI_PRM_HOUS_BACK_SIDE_TEMP);                // Camera housing back side tepmerature
    FLOA_RW(TempSensorBoard,            XI_PRM_SENSOR_BOARD_TEMP);                  // Camera sensor board temperature


    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Color Correction
    //-------------------------------------------------------------------------------------------------------------------

    ENUM_RW(CmsMode,                    XI_PRM_CMS, XI_CMS_MODE);               // Mode of color management system. (XI_PRM_CMS)
    BOOL_RW(CmsApply,                   XI_PRM_APPLY_CMS);                      // Enable applying of CMS profiles to xiGetImage (see XI_PRM_INPUT_CMS_PROFILE, XI_PRM_OUTPUT_CMS_PROFILE)
    STRI_RW(CmsInputProfile,            XI_PRM_INPUT_CMS_PROFILE);              // Filename for input cms profile (e.g. input.icc)
    STRI_RW(CmsOutputProfile,           XI_PRM_OUTPUT_CMS_PROFILE);             // Filename for output cms profile (e.g. input.icc)
    BOOL_RO(SensorIsColor,              XI_PRM_IMAGE_IS_COLOR);                 // Returns true for color cameras.
    ENUM_RW(ColorFilterArray,           XI_PRM_COLOR_FILTER_ARRAY, XI_COLOR_FILTER_ARRAY); // Returns color filter array type of RAW data.
    FLOA_RW(GammaLuminosity,            XI_PRM_GAMMAY);                         // Luminosity gamma
    FLOA_RW(GammaChromaticity,          XI_PRM_GAMMAC);                         // Chromaticity gamma
    FLOA_RW(Sharpness,                  XI_PRM_SHARPNESS);                      // Sharpness Strength 
    FLOA_RW(CcMatrix00,                 XI_PRM_CC_MATRIX_00);                   // Color Correction Matrix element [0][0])
    FLOA_RW(CcMatrix01,                 XI_PRM_CC_MATRIX_01);                   // Color Correction Matrix element [0][1])
    FLOA_RW(CcMatrix02,                 XI_PRM_CC_MATRIX_02);                   // Color Correction Matrix element [0][2])
    FLOA_RW(CcMatrix03,                 XI_PRM_CC_MATRIX_03);                   // Color Correction Matrix element [0][3])
    FLOA_RW(CcMatrix10,                 XI_PRM_CC_MATRIX_10);                   // Color Correction Matrix element [1][0])
    FLOA_RW(CcMatrix11,                 XI_PRM_CC_MATRIX_11);                   // Color Correction Matrix element [1][1])
    FLOA_RW(CcMatrix12,                 XI_PRM_CC_MATRIX_12);                   // Color Correction Matrix element [1][2])
    FLOA_RW(CcMatrix13,                 XI_PRM_CC_MATRIX_13);                   // Color Correction Matrix element [1][3])
    FLOA_RW(CcMatrix20,                 XI_PRM_CC_MATRIX_20);                   // Color Correction Matrix element [2][0])
    FLOA_RW(CcMatrix21,                 XI_PRM_CC_MATRIX_21);                   // Color Correction Matrix element [2][1])
    FLOA_RW(CcMatrix22,                 XI_PRM_CC_MATRIX_22);                   // Color Correction Matrix element [2][2])
    FLOA_RW(CcMatrix23,                 XI_PRM_CC_MATRIX_23);                   // Color Correction Matrix element [2][3])
    FLOA_RW(CcMatrix30,                 XI_PRM_CC_MATRIX_30);                   // Color Correction Matrix element [3][0])
    FLOA_RW(CcMatrix31,                 XI_PRM_CC_MATRIX_31);                   // Color Correction Matrix element [3][1])
    FLOA_RW(CcMatrix32,                 XI_PRM_CC_MATRIX_32);                   // Color Correction Matrix element [3][2])
    FLOA_RW(CcMatrix33,                 XI_PRM_CC_MATRIX_33);                   // Color Correction Matrix element [3][3])
    FLOA_RW(CcMatrixDefault,            XI_PRM_DEFAULT_CC_MATRIX);              // Set default Color Correction Matrix


    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Device IO
    //-------------------------------------------------------------------------------------------------------------------

    ENUM_RW(TriggerSource,              XI_PRM_TRG_SOURCE,          XI_TRG_SOURCE);     // Defines source of trigger.
    INTG_RW(TriggerSoftware,            XI_PRM_TRG_SOFTWARE);                           // Generates an internal trigger. XI_PRM_TRG_SOURCE must be set to TRG_SOFTWARE.
    ENUM_RW(TriggerSelector,            XI_PRM_TRG_SELECTOR,        XI_TRG_SELECTOR);   // Selects the type of trigger. ()
    INTG_RW(AcqFrameBurstCount,         XI_PRM_ACQ_FRAME_BURST_COUNT);                  // Number of frames acquired by burst. This burst is used only if trigger is set to FrameBurstStart


    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: GPIO Setup
    //-------------------------------------------------------------------------------------------------------------------

    ENUM_RW(GpiSelector,                XI_PRM_GPI_SELECTOR,    XI_GPI_SELECTOR);   // Selects GPI
    ENUM_RW(GpiMode,                    XI_PRM_GPI_MODE,        XI_GPI_MODE);       // Defines GPI functionality
    INTG_RW(GpiLevel,                   XI_PRM_GPI_LEVEL);                          // GPI level
    ENUM_RW(GpoSelector,                XI_PRM_GPO_SELECTOR,    XI_GPO_SELECTOR);   // Selects GPO 
    ENUM_RW(GpoMode,                    XI_PRM_GPO_MODE,        XI_GPO_MODE);       // Defines GPO functionality
    ENUM_RW(LedSelector,                XI_PRM_LED_SELECTOR,    XI_LED_SELECTOR);   // Selects LED
    ENUM_RW(LedMode,                    XI_PRM_LED_MODE,        XI_LED_MODE);       // Defines LED functionality

    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Debounce Setup
    //-------------------------------------------------------------------------------------------------------------------

    BOOL_RW(GpiDebounce,                XI_PRM_DEBOUNCE_EN);                    // Enable/Disable debounce to selected GPI
    INTG_RW(GpiDebounceEdge1,           XI_PRM_DEBOUNCE_T0);                    // Debounce time (x * 10us)
    INTG_RW(GpiDebounceEdge2,           XI_PRM_DEBOUNCE_T1);                    // Debounce time (x * 10us)
    INTG_RW(GpiDebouncePolarity,        XI_PRM_DEBOUNCE_POL);                   // Debounce polarity (pol = 1 t0 - falling edge, t1 - rising edge)


#if 0   // JMO:  Currently we don't use any of this
    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Lens Control
    //-------------------------------------------------------------------------------------------------------------------

    
    BOOL_RW(LensMode,                   XI_PRM_LENS_MODE);                      // Status of lens control interface. This shall be set to XI_ON before any Lens operations.
    FLOA_RW(LensApertureValue,          XI_PRM_LENS_APERTURE_VALUE);            // Current lens aperture value in stops. Examples: 2.8, 4, 5.6, 8, 11
    INTG_RW(LensFocusMoveValue,         XI_PRM_LENS_FOCUS_MOVEMENT_VALUE);      // Lens current focus movement value to be used by XI_PRM_LENS_FOCUS_MOVE in motor steps. ()
    INTG_RW(LensFocusMove,              XI_PRM_LENS_FOCUS_MOVE);                // Moves lens focus motor by steps set in XI_PRM_LENS_FOCUS_MOVEMENT_VALUE.
    FLOA_RW(LensFocusDistance,          XI_PRM_LENS_FOCUS_DISTANCE);            // Lens focus distance in cm.
    FLOA_RW(LensFocalLength,            XI_PRM_LENS_FOCAL_LENGTH);              // Lens focal distance in mm.
    FLOA_RW(LensFeature,                XI_PRM_LENS_FEATURE);                   // Allows access to lens feature value currently selected by XI_PRM_LENS_FEATURE_SELECTOR.
    ENUM_RW(LensFeatureSelector,        XI_PRM_LENS_FEATURE_SELECTOR, XI_LENS_FEATURE); // Selects the current feature which is accessible by XI_PRM_LENS_FEATURE.
    STRI_RO(CommData,                   XI_PRM_LENS_COMM_DATA);                 // Write/Read data sequences to/from lens
#endif
    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Device info parameters
    //-------------------------------------------------------------------------------------------------------------------

    STRI_RO(Name,                       XI_PRM_DEVICE_NAME);                // Return device name
    STRI_RO(Type,                       XI_PRM_DEVICE_TYPE);                // Return device type
    INTG_RO(ModelId,                    XI_PRM_DEVICE_MODEL_ID);            // Return device model id
    INTG_RO(SensorId,                   XI_PRM_SENSOR_MODEL_ID);            // Return device sensor model id
    STRI_RO(Sn,                         XI_PRM_DEVICE_SN);                  // Return device serial number
    //STRI_RO(SnEnhanced,                 XI_PRM_DEVICE_SNE);                 // Return device enhanced serial number (for cameras having both serials legacy and enhanced) 
    STRI_RO(SnSensor,                   XI_PRM_DEVICE_SENS_SN);             // Return sensor serial number
    STRI_RO(Id,                         XI_PRM_DEVICE_ID);                  // Return unique device ID
    STRI_RO(Path,                       XI_PRM_DEVICE_INSTANCE_PATH);       // Return device system instance path
    STRI_RO(LocPath,                    XI_PRM_DEVICE_LOCATION_PATH);       // Represents the location of the device in the device tree.
    STRI_RO(UserId,                     XI_PRM_DEVICE_USER_ID);             // Return custom ID of camera.
    STRI_RO(Manifest,                   XI_PRM_DEVICE_MANIFEST);            // Return device capability description XML. 
    INTG_RW(ImageUserData,              XI_PRM_IMAGE_USER_DATA);            // User image data at image header to track parameters synchronization.



    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Device acquisition settings
    //-------------------------------------------------------------------------------------------------------------------
    INTG_RW(ImageDataFormatRgb32Alpha,  XI_PRM_IMAGE_DATA_FORMAT_RGB32_ALPHA);                          // The alpha channel of RGB32 output image format.
    INTG_RO(ImagePayloadSize,           XI_PRM_IMAGE_PAYLOAD_SIZE);                                     // Buffer size in bytes sufficient for output image returned by xiGetImage
    ENUM_RW(TransportPixelFormat,       XI_PRM_TRANSPORT_PIXEL_FORMAT,  XI_GenTL_Image_Format_e);       // Current format of pixels on transport layer. ()
    ENUM_RW(TransportDataTarget,        XI_PRM_TRANSPORT_DATA_TARGET,   XI_TRANSPORT_DATA_TARGET_MODE); // Target selector for data - CPU RAM or GPU RAM
    FLOA_RW(SensorClockFreqHz,          XI_PRM_SENSOR_CLOCK_FREQ_HZ);                                   // Sensor clock frequency in Hz.
    INTG_RW(SensorClockFreqIndex,       XI_PRM_SENSOR_CLOCK_FREQ_INDEX);                                // Sensor clock frequency index. Sensor with selected frequencies have possibility to set the frequency only by this index.
    ENUM_RW(SensorOutputChannelCount,   XI_PRM_SENSOR_OUTPUT_CHANNEL_COUNT, XI_SENSOR_OUTPUT_CHANNEL_COUNT); // Number of output channels from sensor used for data transfer.
    FLOA_RW(FrameRate,                  XI_PRM_FRAMERATE);                                              // Define framerate in Hz
    ENUM_RW(CounterSelector,            XI_PRM_COUNTER_SELECTOR,        XI_COUNTER_SELECTOR);           // Select counter
    INTG_RO(CounterValue,               XI_PRM_COUNTER_VALUE);                                          // Counter status
    ENUM_RW(AcqTimingMode,              XI_PRM_ACQ_TIMING_MODE,         XI_ACQ_TIMING_MODE)             // Type of sensor frames timing.
    INTG_RO(BwAvailable,                XI_PRM_AVAILABLE_BANDWIDTH);                                    // Measure and return available interface bandwidth(int Megabits)
    ENUM_RW(BufferPolicy,               XI_PRM_BUFFER_POLICY,           XI_BP);                         // Data move policy
    BOOL_RW(LookUpTable,                XI_PRM_LUT_EN);                                                 // Activates LUT.
    INTG_RW(LookUpTableIndex,           XI_PRM_LUT_INDEX);                                              // Control the index (offset) of the coefficient to access in the LUT.
    INTG_RW(LookUpTableValue,           XI_PRM_LUT_VALUE);                                              // Value at entry LUTIndex of the LUT
    ENUM_RW(TriggerDelay,               XI_PRM_TRG_DELAY,               XI_GPI_SELECTOR);               // Specifies the delay in microseconds (us) to apply after the trigger reception before activating it.
    ENUM_RW(TimeStampResetMode,         XI_PRM_TS_RST_MODE,             XI_TS_RST_MODE);                // Defines how time stamp reset engine will be armed.
    ENUM_RW(TimeStampResetSource,       XI_PRM_TS_RST_SOURCE,           XI_TS_RST_SOURCE);              // Defines which source will be used for timestamp reset. Writing this parameter will trigger settings of engine (arming) (XI_PRM_TS_RST_SOURCE)


    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Extended Device parameters
    //-------------------------------------------------------------------------------------------------------------------

    BOOL_RO(Exists,                         XI_PRM_IS_DEVICE_EXIST);            // Returns 1 if camera connected and works properly. 
    INTG_RW(AcqBufferSizeBytes,             XI_PRM_ACQ_BUFFER_SIZE);            // Acquisition buffer size in buffer_size_unit. Default bytes.
    INTG_RW(AcqBufferSizeBytesUnit,         XI_PRM_ACQ_BUFFER_SIZE_UNIT);       // Acquisition buffer size unit in bytes. Default 1. E.g. Value 1024 means that buffer_size is in KiBytes
    INTG_RW(AcqTransportBufferSizeBytes,    XI_PRM_ACQ_TRANSPORT_BUFFER_SIZE);  // Acquisition transport buffer size in bytes
    INTG_RW(AcqTransportPacketSizeBytes,    XI_PRM_ACQ_TRANSPORT_PACKET_SIZE);  // Acquisition transport packet size in bytes
    INTG_RW(AcqQueueImagesCount,            XI_PRM_BUFFERS_QUEUE_SIZE);         // Queue of field/frame buffers
    INTG_RW(AcqTransportBufferCommit,       XI_PRM_ACQ_TRANSPORT_BUFFER_COMMIT);// Number of buffers to commit to low level
    BOOL_RW(SelectRecentImage,              XI_PRM_RECENT_FRAME);               // GetImage returns most recent frame
    INTG_RW(Reset,                          XI_PRM_DEVICE_RESET);               // Resets the camera to default state.



    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Sensor Defects Correction
    //-------------------------------------------------------------------------------------------------------------------

    ENUM_RW(ColumnFpnCorrection,        XI_PRM_COLUMN_FPN_CORRECTION,       XI_SWITCH);                     // Correction of column FPN
    ENUM_RW(RowFpnCorrection,           XI_PRM_ROW_FPN_CORRECTION,          XI_SWITCH);                     // Correction of row FPN
    INTG_RW(ImageCorrectionValue,       XI_PRM_IMAGE_CORRECTION_VALUE);                                     // Select image correction selected function value
    ENUM_RW(ImageCorrectionSelector,    XI_PRM_IMAGE_CORRECTION_SELECTOR,   XI_IMAGE_CORRECTION_SELECTOR);  // Select image correction function


    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Sensor features
    //-------------------------------------------------------------------------------------------------------------------
    ENUM_RW(SensorMode,         XI_PRM_SENSOR_MODE,     XI_SENSOR_MODE);    // Current sensor mode. Allows to select sensor mode by one integer. Setting of this parameter affects: image dimensions and downsampling.
    BOOL_RW(Hdr,                XI_PRM_HDR);                                // Enable High Dynamic Range feature.
    INTG_RW(HdrKneepointCount,  XI_PRM_HDR_KNEEPOINT_COUNT);                // The number of kneepoints in the PWLR.
    INTG_RW(HdrTimeSlope1,      XI_PRM_HDR_T1);                             // position of 1st kneepoint(in % of XI_PRM_EXPOSURE)
    INTG_RW(HdrTimeSlope2,      XI_PRM_HDR_T2);                             // position of 2nd kneepoint(in % of XI_PRM_EXPOSURE)
    INTG_RW(HdrKnee1Percent,    XI_PRM_KNEEPOINT1);                         // value of 1st kneepoint (% of sensor saturation)
    INTG_RW(HdrKnee2Percent,    XI_PRM_KNEEPOINT2);                         // value of 2nd kneepoint (% of sensor saturation)
    INTG_RW(ImageBlackLevel,    XI_PRM_IMAGE_BLACK_LEVEL);                  // Last image black level counts. Can be used for Offline processing to recall it.


    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Version info
    //-------------------------------------------------------------------------------------------------------------------

    STRI_RO(ApiVersion,         XI_PRM_API_VERSION);        // Returns version of API
    STRI_RO(DriverVersion,      XI_PRM_DRV_VERSION);        // Returns version of current device driver.
    STRI_RO(Mcu1Version,        XI_PRM_MCU1_VERSION);       // Returns version of MCU1 firmware.
    STRI_RO(Mcu2Version,        XI_PRM_MCU2_VERSION);       // Returns version of MCU2 firmware.
    STRI_RO(Fpga1Version,       XI_PRM_FPGA1_VERSION);      // Returns version of FPGA1 firmware.
    INTG_RO(HwRevision,         XI_PRM_HW_REVISION);        // Returns hardware revision number. 

    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: API features
    //-------------------------------------------------------------------------------------------------------------------

    ENUM_RW(DebugLevel,                 XI_PRM_DEBUG_LEVEL,     XI_DEBUG_LEVEL);// Set debug level 
    BOOL_RW(AutoBwCalculation,          XI_PRM_AUTO_BANDWIDTH_CALCULATION);     // Automatic bandwidth calculation, ()
    BOOL_RW(NewProcessChainEnable,      XI_PRM_NEW_PROCESS_CHAIN_ENABLE);       // Enables (2015/FAPI) processing chain for MQ MU cameras
    BOOL_RW(CamEnumGoldenEnabled,       XI_PRM_CAM_ENUM_GOLDEN_ENABLED);        // Enable enumeration of golden devices
    INTG_RW(CameraSimulatorsCount,      XI_PRM_CAM_SIMULATORS_COUNT);           // Number of camera simulators to be available.
    BOOL_RW(CameraSensorInitDisabled,   XI_PRM_CAM_SENSOR_INIT_DISABLED);       // Camera sensor will not be initialized when 1=XI_ON is set.


    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Camera FFS
    //-------------------------------------------------------------------------------------------------------------------

    STRI_RO(ReadFileFfs,        XI_PRM_READ_FILE_FFS);      // Read file from camera flash filesystem.
    STRI_RW(WriteFileFfs,       XI_PRM_WRITE_FILE_FFS);     // Write file to camera flash filesystem.
    STRI_RW(FfsFileName,        XI_PRM_FFS_FILE_NAME);      // Set name of file to be written/read from camera FFS.
    INTG_RO(FfsFileId,          XI_PRM_FFS_FILE_ID);        // File number.
    INTG_RO(FfsFileSize,        XI_PRM_FFS_FILE_SIZE);      // Size of file.
    INTG_RO(FreeFfsSize,        XI_PRM_FREE_FFS_SIZE);      // Size of free camera FFS.
    INTG_RO(UsedFfsSize,        XI_PRM_USED_FFS_SIZE);      // Size of used camera FFS.
    INTG_RW(FfsAccessKey,       XI_PRM_FFS_ACCESS_KEY);     // Setting of key enables file operations on some cameras.

    
    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: APIContextControl
    //-------------------------------------------------------------------------------------------------------------------

    STRI_RO(ApiContextList, XI_PRM_API_CONTEXT_LIST);   // List of current parameters settings context - parameters with values. Used for offline processing.
 

    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Sensor Control
    //-------------------------------------------------------------------------------------------------------------------

    ENUM_RW(SensorFeatureSelector,  XI_PRM_SENSOR_FEATURE_SELECTOR, XI_SENSOR_FEATURE_SELECTOR);  // Selects the current feature which is accessible by XI_PRM_SENSOR_FEATURE_VALUE.
    INTG_RW(SensorFeatureValue,     XI_PRM_SENSOR_FEATURE_VALUE);                                 // Allows access to sensor feature value currently selected by XI_PRM_SENSOR_FEATURE_SELECTOR.


    //-------------------------------------------------------------------------------------------------------------------
    // ---- Parameter Group: Extended Features
    //-------------------------------------------------------------------------------------------------------------------

    ENUM_RW(ExtendedFeatureSelector,XI_PRM_EXTENDED_FEATURE_SELECTOR,   XI_EXT_FEATURE_SELECTOR);   // Selection of extended feature.
    INTG_RW(ExtendedFeature,        XI_PRM_EXTENDED_FEATURE);                                       // Extended feature value.
    ENUM_RW(UnitSelector,           XI_PRM_DEVICE_UNIT_SELECTOR,        XI_DEVICE_UNIT_SELECTOR);   // Selects device unit.
    INTG_RW(UnitRegisterSelector,   XI_PRM_DEVICE_UNIT_REGISTER_SELECTOR);                          // Selects register of selected device unit(XI_PRM_DEVICE_UNIT_SELECTOR).
    INTG_RW(UnitRegister,           XI_PRM_DEVICE_UNIT_REGISTER_VALUE);                             // Sets/gets register value of selected device unit(XI_PRM_DEVICE_UNIT_SELECTOR).

//  JMO:  These properties were reported by the software as "not supported" as of 18-NOV-2016. 
//  I assume they will be supported in the future

//    ENUM_RW(AcqStatusSelector,      XI_PRM_ACQUISITION_STATUS_SELECTOR, XI_ACQUISITION_STATUS_SELECTOR); // Selects the internal acquisition signal to read using XI_PRM_ACQUISITION_STATUS.
    ENUM_RW(AcqStatus,              XI_PRM_ACQUISITION_STATUS,          XI_SWITCH);                 // Acquisition status(True/False)


public:

    // Utility class to temporarily pause acquisition when necessary.  Some
    // parameters can only be changed when acquisition is not running.
    // Not sure if this will have use.
    class Pause
    {
        xi::Camera& m_cam;
        const bool m_bPause;

    public:
        Pause(xi::Camera& cam) : m_cam(cam), m_bPause(cam.isAcquiring())
        {
            if (m_bPause)
                cam.stopAcquisition();
        }

        ~Pause()
        {
            try
            {
                if (m_bPause)
                    m_cam.startAcquisition();
            }
            catch (std::exception&)
            {
                ASSERT(false);
            }
        }
    };
};




}   // end namespace xi
#endif
