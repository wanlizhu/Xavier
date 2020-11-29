cmake_minimum_required(VERSION 3.17.1)
project(Xavier)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(GLOBAL PROPERTY USE_FOLDERS ON)

include(conan.cmake)

conan_cmake_run(
	CONANFILE conanfile.txt
	BASIC_SETUP 
	CMAKE_TARGETS
    BUILD missing
	IMPORTS "bin, *.dll -> ${CMAKE_BINARY_DIR}/bin"
    IMPORTS "lib, *.dylib* -> ${CMAKE_BINARY_DIR}/bin"
)

add_subdirectory(engine)

option(XAV_BUILD_EDITOR "Build editor" OFF)
if (XAV_BUILD_EDITOR)
	add_subdirectory(editor)
endif()

option(XAV_BUILD_BENCHMARK "Build benchmark" OFF)
if (XAV_BUILD_BENCHMARK)
	add_subdirectory(benchmark)
endif()
