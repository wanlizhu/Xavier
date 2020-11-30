cmake_minimum_required(VERSION 3.17.1)

option(XAV_USE_FLOAT_AS_DOUBLE  "Use 64-bits floats" OFF)
option(XAV_USE_SAMPLED_SPECTRUM "Use sampled spectrum rather than RGB spectrum" OFF)

add_library(
    XavierEngine STATIC
    include/Xavier/Config.h
    include/Xavier/IEngine.h
    include/Xavier/IDocument.h
    include/Xavier/IRenderer.h
    src/Engine.h
    src/Engine.cpp
    src/Document.h
    src/Document.cpp
    src/Window.h
    src/Window.cpp
    src/Renderer.h
    src/Renderer.cpp
)

get_target_property(SourceFiles XavierEngine SOURCES)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SourceFiles})

set_target_properties(
    XavierEngine 
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME libXavierEngine
)

target_compile_definitions(
    XavierEngine
    PUBLIC UNICODE
    PUBLIC $<$<BOOL:${WIN32}>:WIN32_LEAN_AND_MEAN>
    PUBLIC $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>
)

target_include_directories(
    XavierEngine 
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

find_package(Vulkan REQUIRED)
target_link_libraries(
    XavierEngine 
    PUBLIC
    Vulkan::Vulkan
    CONAN_PKG::glfw
    CONAN_PKG::Eigen3
)

install(
    TARGETS XavierEngine
    DESTINATION lib
)
