cmake_minimum_required(VERSION 3.17.1)

option(XAV_USE_FLOAT_AS_DOUBLE  "Use 64-bits floats" OFF)
option(XAV_USE_SAMPLED_SPECTRUM "Use sampled spectrum rather than RGB spectrum")

add_library(
    XavierRuntime STATIC
    XavierConfig.h
    XavierAPI.h
    core/MaxineAPI.cpp
    core/Document.h
    core/Document.cpp
    core/Window.h
    core/Window.cpp
)

set_target_properties(
    XavierRuntime PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME libXavierRT
)

target_compile_definitions(
    XavierRuntime
    PUBLIC UNICODE
    PUBLIC $<$<BOOL:${WIN32}>:WIN32_LEAN_AND_MEAN>
    PUBLIC $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>
)

target_include_directories(
    XavierRuntime PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

find_package(Vulkan REQUIRED)
target_link_libraries(
    XavierRuntime PUBLIC
    Vulkan::Vulkan
)

install(
    TARGETS XavierRuntime
    DESTINATION lib
)
