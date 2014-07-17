find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} src/)
add_executable(
  segment src/full_svs_segmentation.cpp
  src/segmentation.cpp
  src/sgsmooth.cpp
)
add_executable(
  histogram_seg src/histogramSegmentation.cpp
  src/segmentation.cpp
  src/sgsmooth.cpp
)

target_link_libraries( segment ${OPENSLIDE_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries( histogram_seg ${OPENSLIDE_LIBRARIES} ${OpenCV_LIBS})
