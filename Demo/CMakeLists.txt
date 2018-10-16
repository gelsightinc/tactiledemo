cmake_minimum_required(VERSION 3.2)
project(demo VERSION 1.0 LANGUAGES CXX C)

add_executable(demo "")


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

#
# List all source files and headers here
target_sources(demo
PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/Demo.cpp"
)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
#set(CMAKE_SHARE_LINKER_FLAGS "${CMAKE_SHARE_LINKER_FLAGS} -fopenmp")

#
# demo depends on gelsightsdk, gslicense
#
find_package(GelSightSdk REQUIRED)
include_directories(demo ${GelSightSdk_INCLUDE_DIRS})
target_link_libraries(demo ${GelSightSdk_LIBRARIES})

# demo also depends on opencv and Ximea SDK
find_package(OpenCV 3.4 REQUIRED)
include_directories(demo ${OpenCV_INCLUDE_DIRS})
target_link_libraries(demo ${OpenCV_LIBS})

find_package(XIMEA REQUIRED)
include_directories(demo ${XIMEA_INCLUDE_DIRS})
target_link_libraries(demo ${XIMEA_LIBRARIES})



#
# C++ Filesystem 
target_link_libraries(demo stdc++fs)



#set_property(TARGET demo PROPERTY CXX_STANDARD 14)


