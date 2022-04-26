cmake_minimum_required(VERSION 3.16)
project(SDG_Engine)
set(CMAKE_CXX_STANDARD 17)

# Build all targets into one directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(LINUX 1)
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(DEBUG 1)
endif()

add_compile_definitions(SDL_GPU_DISABLE_OPENGL SDL_GPU_DISABLE_GLES_2 SDL_GPU_DISABLE_GLES_1 MIN_WEBGL_VERSION=2 MAX_WEBGL_VERSION=2)

add_subdirectory(src)
add_definitions(-w)
add_subdirectory(lib/SDL)

# For sdl-gpu's find SDL2
set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2)
set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/SDL/include)

add_subdirectory(lib/sdl-gpu)
add_subdirectory(lib/tinyxml2)
add_subdirectory(lib/spdlog)

