find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} src/)
add_executable(
  segment src/full_svs_segmentation.cpp
  src/segmentation.cpp
  src/sgsmooth.cpp
)
target_link_libraries( segment ${OPENSLIDE_LIBRARIES} ${OpenCV_LIBS})
