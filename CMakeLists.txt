cmake_minimum_required(VERSION 3.16)
project(SDG_Engine)
set(CMAKE_CXX_STANDARD 17)

# Platform-specific detection

# WINDOWS
if (WIN32)
    if (${CMAKE_SIZEOF_VOID_P} EQUAL 4)
        message(FATAL "Windows 32-bit is not supported!")
    endif()
    set(WINDOWS 1)
    # Set all targets to build into one directory. Paths are otherwise broken.
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

# LINUX
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux" AND UNIX AND NOT APPLE AND NOT ANDROID)
    set(LINUX 1)
endif()

# WEBGL
if (EMSCRIPTEN)
    set(WEBGL 1)
    #set(CMAKE_C_COMPILER ${CMAKE_SOURCE_DIR}/lib/emsdk/upstream/emscripten/emcc)
    #set(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/lib/emsdk/upstream/emscripten/em++)
endif()

# Build Type
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    set(DEBUG 1)
else()
    set(DEBUG 0)
endif()


add_subdirectory(src)
add_subdirectory(lib)
