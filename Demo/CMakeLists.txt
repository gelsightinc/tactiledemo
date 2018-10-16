cmake_minimum_required(VERSION 3.2)
project(demo VERSION 1.0 LANGUAGES CXX C)

add_executable(demo "")


#
# List all source files and headers here
target_sources(demo
PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/Demo.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imageconvert.h"
    "${CMAKE_CURRENT_LIST_DIR}/imageconvert.cpp"
)


#
# demo depends on gelsightsdk, gslicense
#
find_package(GelSightSdk REQUIRED)
include_directories(demo ${GelSightSdk_INCLUDE_DIRS})
target_link_libraries(demo ${GelSightSdk_LIBRARIES})

# demo depends on opencv
find_package(OpenCV 3.4 REQUIRED)
include_directories(demo ${OpenCV_INCLUDE_DIRS})
target_link_libraries(demo ${OpenCV_LIBS})

# demo depends on Ximea
find_package(XIMEA REQUIRED)
include_directories(demo ${XIMEA_INCLUDE_DIRS})
target_link_libraries(demo ${XIMEA_LIBRARIES})



