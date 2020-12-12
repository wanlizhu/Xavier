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
    src/VulkanRenderer.h
    src/VulkanRenderer.cpp
    src/tools/MathCore.h
    src/tools/MathCore.cpp
    src/tools/CommandArguments.h
    src/tools/CommandArguments.cpp
    src/vulkan-core/VulkanTools.h
    src/vulkan-core/VulkanBuffer.h
    src/vulkan-core/VulkanBuffer.cpp
    src/vulkan-core/VulkanImage.h
    src/vulkan-core/VulkanImage.cpp
    src/vulkan-core/VulkanEffect.h
    src/vulkan-core/VulkanEffect.cpp
    src/vulkan-core/VulkanRenderPass.h
    src/vulkan-core/VulkanRenderPass.cpp
    src/vulkan-core/VulkanDescriptorSet.h
    src/vulkan-core/VulkanDescriptorSet.cpp
    src/vulkan-core/VulkanCommandBuffer.h
    src/vulkan-core/VulkanCommandBuffer.cpp
    src/vulkan-core/VulkanSwapChain.h
    src/vulkan-core/VulkanSwapChain.cpp
)

get_target_property(SourceFiles XavierEngine SOURCES)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SourceFiles})

set_target_properties(
    XavierEngine 
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME XavierEngine
)

target_compile_definitions(
    XavierEngine
    PUBLIC 
    UNICODE
    $<$<BOOL:${WIN32}>:NOMINMAX>
    $<$<BOOL:${WIN32}>:WIN32_LEAN_AND_MEAN>
    $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>
)

target_compile_options(
    XavierEngine
    PUBLIC
    $<$<BOOL:${WIN32}>:/wd4305>    # double constant assigned to float
    $<$<BOOL:${WIN32}>:/wd4244>    # int -> float conversion
    $<$<BOOL:${WIN32}>:/wd4843>    # double -> float conversion
    $<$<BOOL:${WIN32}>:/wd4267>    # size_t -> int
    $<$<BOOL:${WIN32}>:/wd4838>    # another double -> int
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
