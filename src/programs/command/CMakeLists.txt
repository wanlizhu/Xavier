cmake_minimum_required(VERSION 3.17.1)

add_executable(
    XavierCommand
    main.cpp
)

set_target_properties(
    XavierCommand PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME xavier
)

target_compile_definitions(
    XavierCommand
    PUBLIC UNICODE
    PUBLIC $<$<BOOL:${WIN32}>:WIN32_LEAN_AND_MEAN>
    PUBLIC $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>
)

target_link_libraries(
    XavierCommand PUBLIC
    XavierRuntime
)

install(
    TARGETS XavierCommand
    DESTINATION bin
)
