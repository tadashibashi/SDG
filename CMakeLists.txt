cmake_minimum_required(VERSION 3.16)
project(SDG_Engine)

set(CMAKE_CXX_STANDARD 17)


# Build all targets into one directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#include_directories(
#        lib/SDL/include
#        lib/sdl-gpu/include)

add_subdirectory(src)
add_subdirectory(lib/SDL)
add_subdirectory(lib/sdl-gpu)
add_subdirectory(lib/tinyxml2)
add_subdirectory(lib/spdlog)
