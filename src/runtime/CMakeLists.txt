cmake_minimum_required(VERSION 3.17.1)

option(MX_USE_FLOAT_AS_DOUBLE  "Use 64-bits floats" OFF)
option(MX_USE_SAMPLED_SPECTRUM "Use sampled spectrum rather than RGB spectrum")

add_library(
    MaxineRuntime STATIC 
    api/Maxine/Config.h
    api/Maxine/Engine.h
    api/Maxine/Engine.cpp
    api/Maxine/Document.h
    api/Maxine/Document.cpp
    api/Maxine/IRenderer.h
    api/Maxine/SWRenderer.h
    api/Maxine/SWRenderer.cpp
    api/Maxine/HWRenderer.h
    api/Maxine/HWRenderer.cpp
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
    "${CMAKE_CURRENT_SOURCE_DIR}/api"
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