cmake_minimum_required(VERSION 3.17.1)
project(Xavier)

set(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin")

foreach(ConfigType ${CMAKE_CONFIGURATION_TYPES})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${ConfigType} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${ConfigType} "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${ConfigType} "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
	set(CMAKE_PDB_OUTPUT_DIRECTORY_${ConfigType}     "${CMAKE_PDB_OUTPUT_DIRECTORY}")
endforeach()

include(cmake/conan.cmake)

conan_cmake_run(
	CONANFILE conanfile.txt
	BASIC_SETUP 
	CMAKE_TARGETS
    BUILD missing
	IMPORTS "bin, *.dll -> ${CMAKE_BINARY_DIR}/bin"
    IMPORTS "lib, *.dylib* -> ${CMAKE_BINARY_DIR}/bin"
)

add_subdirectory(engine)

option(XAV_BUILD_EDITOR "Build editor" ON)
if (XAV_BUILD_EDITOR)
	add_subdirectory(editor)
endif()

option(XAV_BUILD_BENCHMARK "Build benchmark" OFF)
if (XAV_BUILD_BENCHMARK)
	add_subdirectory(benchmark)
endif()

set_directory_properties(PROPERTIES VS_STARTUP_PROJECT XavierEditor)
