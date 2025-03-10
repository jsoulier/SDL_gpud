cmake_minimum_required(VERSION 3.24)
project(sdl_gpud)

set(BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINARY_DIR})

add_subdirectory(lib/SDL)
add_executable(sdl_gpud WIN32
    example/impl.c
    example/main.c
    example/main.cpp
)
target_include_directories(sdl_gpud PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(sdl_gpud SDL3::SDL3)