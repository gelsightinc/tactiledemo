#
#  XIMEA_FOUND         - True if XIMEA API found
#  XIMEA_INCLUDE_DIR   - Path to the XIMEA API headers
#  XIMEA_LIBRARIES     - XIMEA libraries folder
#
# Modified from OpenCV OpenCVFindXimea.cmake
#

find_path (XIMEA_INCLUDE
    NAMES xiApi.h
    PATHS "/usr/include/m3api"
    DOC "xiApi include path"
)

find_library (XIMEA_LIB
    NAMES m3api
    PATHS "/usr/lib"
    DOC "xiApi library path"
)


include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(XIMEA DEFAULT_MSG XIMEA_LIB XIMEA_INCLUDE)

if(XIMEA_FOUND)
    set(XIMEA_INCLUDE_DIRS ${XIMEA_INCLUDE})
    set(XIMEA_LIBRARIES ${XIMEA_LIB} )
endif()


# We don't want these variables to show up in the CMake GUI so we mark
# them as advanced
mark_as_advanced(XIMEA_INCLUDE XIMEA_LIB )

