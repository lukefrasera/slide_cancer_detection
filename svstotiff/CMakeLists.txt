add_library(svsconvertlib SHARED include/svsconvert.cpp)
target_link_libraries(svsconvertlib ${OPENSLIDE_LIBRARIES})

add_executable(svsconverter src/svsconverter.cpp)
include_directories(${OPENSLIDE_INCLUDE_DIRS})
target_link_libraries(svsconverter ${OPENSLIDE_LIBRARIES})