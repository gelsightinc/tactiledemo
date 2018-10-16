cmake_minimum_required(VERSION 3.2)
project(gsdemo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

#
# cmake module path for custom modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

add_subdirectory(Demo)

