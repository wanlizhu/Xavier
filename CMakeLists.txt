cmake_minimum_required(VERSION 3.17.1)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(GLOBAL PROPERTY USE_FOLDERS ON)

project(Xavier)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(src/runtime)
add_subdirectory(src/tests/unittest)
add_subdirectory(src/programs/command)
add_subdirectory(src/programs/gui)
