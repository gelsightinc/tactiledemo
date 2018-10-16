# Try to find GelSightSdk libraries
# Once done this will define
# GelSightSdk_FOUND        - system has GelSightSdk
# GelSightSdk_INCLUDE_DIRS - GelSightSdk include directories
# GelSightSdk_LIBRARIES    - GelSightSdk libraries 
# GelSightSdk_BIN          - Path to flex binaries

set(gspath "$ENV{GS_SDK}")
if (NOT EXISTS ${gspath})
    message(STATUS "GelSightSdk path does not exist= ${gspath}")
endif()

find_path (GS_INCLUDE
    NAMES gelsightsdk.h
    PATHS "${gspath}/include"
    DOC "GelSightSdk include path"
)

find_library (GS_LIB1
    NAMES gscore
    PATHS "${gspath}/lib"
)

find_library (GS_LIB2
    NAMES gsanalysis
    PATHS "${gspath}/lib"
)



include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GelSightSdk DEFAULT_MSG GS_LIB1 GS_LIB2 GS_INCLUDE)

if(GelSightSdk_FOUND)
    set(GelSightSdk_INCLUDE_DIRS ${GS_INCLUDE})
    set(GelSightSdk_LIBRARIES ${GS_LIB1} ${GS_LIB2})
    set(GelSightSdk_BIN "${gspath}/bin")
endif()

    

# We don't want these variables to show up in the CMake GUI so we mark
# them as advanced
mark_as_advanced(GS_INCLUDE GS_LIB1 GS_LIB2)

