cmake_minimum_required(VERSION 2.8)

PROJECT(cancer_Detection)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)

find_package(OpenSlide)
if(NOT OPENSLIDE_FOUND)
	message(FATAL_ERROR "OpenSlide Not Installed or Not Found")
endif()

# INCLUDE SUBDIRECTORIES
ADD_SUBDIRECTORY(segmentation)
ADD_SUBDIRECTORY(packingProblem)
ADD_SUBDIRECTORY(svstotiff)