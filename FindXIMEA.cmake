#
#  XIMEA_FOUND         - True if XIMEA API found
#  XIMEA_INCLUDE_DIR   - Path to the XIMEA API headers
#  XIMEA_LIBRARIES     - XIMEA libraries folder
#
# Modified from OpenCV OpenCVFindXimea.cmake
#

set(XIMEA_PATH /opt/XIMEA)
if (NOT EXISTS ${XIMEA_PATH})
    message(STATUS "Ximea API not installed at ${XIMEA_PATH}")
endif()


find_path (XIMEA_INCLUDE
    NAMES xiApi.h
    PATHS "${XIMEA_PATH}/include"
    DOC "xiApi include path"
)

find_library (XIMEA_LIB
    NAMES xiapi_dng_store
    PATHS "${XIMEA_PATH}/lib"
)


include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(XIMEA DEFAULT_MSG XIMEA_LIB XIMEA_INCLUDE)

if(XIMEA_FOUND)
    set(XIMEA_INCLUDE_DIRS ${XIMEA_INCLUDE})
    set(XIMEA_LIBRARIES ${XIMEA_LIB} )
    set(XIMEA_BIN "${XIMEA_PATH}/bin")
endif()


# We don't want these variables to show up in the CMake GUI so we mark
# them as advanced
mark_as_advanced(XIMEA_INCLUDE XIMEA_LIB )

