add_library(svsconvertlib SHARED include/svsconvert.cpp)
target_link_libraries(svsconvertlib ${OPENSLIDE_LIBRARIES})

add_executable(svsconverter src/svstotiff.cpp)
include_directories(${OPENSLIDE_INCLUDE_DIRS} include/)
target_link_libraries(svsconverter ${OPENSLIDE_LIBRARIES} ${CMAKE_BINARY_DIR}/svstotiff/libsvsconvertlib.so)