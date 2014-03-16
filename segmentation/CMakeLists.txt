add_executable(segment src/full_svs_segmentation.cpp)
find_package(OpenSlide)
if(OPENSLIDE_FOUND)
	include_directories(${OPENSLIDE_INCLUDE_DIRS})
	target_link_libraries( segment ${OPENSLIDE_LIBRARIES})
else()
	message(FATAL_ERROR "OpenSlide Not Installed or Not Found")
endif()

