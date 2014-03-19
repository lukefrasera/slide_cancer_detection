
add_executable(segment src/full_svs_segmentation.cpp)

include_directories(${OPENSLIDE_INCLUDE_DIRS})
target_link_libraries( segment ${OPENSLIDE_LIBRARIES})

