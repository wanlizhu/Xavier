cmake_minimum_required(VERSION 3.17.1)

add_executable(
    MaxineCommand
    main.cpp
)

set_target_properties(
    MaxineCommand PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME maxine
)

target_compile_definitions(
    MaxineCommand
    PUBLIC UNICODE
    PUBLIC $<$<BOOL:${WIN32}>:WIN32_LEAN_AND_MEAN>
    PUBLIC $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>
)

target_link_libraries(
    MaxineCommand PUBLIC
    MaxineRuntime
)

install(
    TARGETS MaxineCommand
    DESTINATION bin
)