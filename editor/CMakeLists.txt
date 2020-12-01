cmake_minimum_required(VERSION 3.17.1)

add_executable(
    XavierEditor
    src/main.cpp
)

get_target_property(SourceFiles XavierEditor SOURCES)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SourceFiles})

if (WIN32)
    set(SubDirName "$(Configuration)/")
else()
    set(SubDirName "")
endif()

set_target_properties(
    XavierEditor 
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME XavierEditor
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SubDirName}"
    LINK_FLAGS "/ignore:4099"
)


target_compile_definitions(
    XavierEditor
    PRIVATE UNICODE
    PRIVATE $<$<BOOL:${WIN32}>:WIN32_LEAN_AND_MEAN>
    PRIVATE $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>
)

target_include_directories(
    XavierEditor 
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(
    XavierEditor 
    PRIVATE
    XavierEngine
)

install(
    TARGETS XavierEditor
    DESTINATION bin
)

add_custom_command(
    TARGET XavierEditor
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SubDirName}assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SubDirName}config
    COMMENT "Copy resources to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SubDirName}"
)