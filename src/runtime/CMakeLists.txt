cmake_minimum_required(VERSION 3.17.1)

option(MX_USE_FLOAT_AS_DOUBLE  "Use 64-bits floats" OFF)
option(MX_USE_SAMPLED_SPECTRUM "Use sampled spectrum rather than RGB spectrum")

add_library(
    MaxineRuntime STATIC 
    api/Config.h
    api/Engine.h
    api/Engine.cpp
    api/Document.h
    api/Document.cpp
    api/IRenderer.h
    api/SWRenderer.h
    api/SWRenderer.cpp
    api/HWRenderer.h
    api/HWRenderer.cpp
)

set_target_properties(
    MaxineRuntime PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME libMaxineRT
)

target_compile_definitions(
    MaxineRuntime
    PUBLIC UNICODE
    PUBLIC $<$<BOOL:${WIN32}>:WIN32_LEAN_AND_MEAN>
    PUBLIC $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>
)

target_include_directories(
    MaxineRuntime PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

find_package(Vulkan REQUIRED)
target_link_libraries(
    MaxineRuntime PUBLIC
    Vulkan::Vulkan
)

install(
    TARGETS MaxineRuntime
    DESTINATION lib
)