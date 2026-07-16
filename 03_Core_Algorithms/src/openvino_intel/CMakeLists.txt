cmake_minimum_required(VERSION 3.18)
project(binocular_openvino_intel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(onnxruntime REQUIRED)

add_library(binocular_core SHARED
    ${CMAKE_SOURCE_DIR}/src/rectify.cpp
    ${CMAKE_SOURCE_DIR}/src/triangulate.cpp
    ${CMAKE_SOURCE_DIR}/src/pupil_seg.cpp
    ${CMAKE_SOURCE_DIR}/src/pipeline.cpp
)

target_include_directories(binocular_core
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(binocular_core
    ${OpenCV_LIBS}
    onnxruntime::onnxruntime
)

# Export DLL symbols (Windows)
if(WIN32)
    set_target_properties(binocular_core PROPERTIES
        COMPILE_DEFINITIONS "BINOCULAR_EXPORTS"
    )
endif()
