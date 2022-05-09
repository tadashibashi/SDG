project(SDG_Tests)

if (EMSCRIPTEN)
    set(EmscriptenLinkerFlags "-sASSERTIONS -sASYNCIFY \
            -sINITIAL_MEMORY=268435456 -sALLOW_MEMORY_GROWTH \
            -sUSE_WEBGL2=1 -sWASM=2 -sMAX_WEBGL_VERSION=2 \
            -sLLD_REPORT_UNDEFINED -sNO_DISABLE_EXCEPTION_CATCHING -fexceptions")

    # Emscripten flag feature research:
    # Exceptions https://emscripten.org/docs/porting/exceptions.html
    # Asyncify runs Emscripten in a thread separate from browser input

    set(CMAKE_CXX_FLAGS "-Os -fexceptions" ${CMAKE_CXX_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS  "${EmscriptenLinkerFlags} ${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()


add_subdirectory(lib/Catch2)

add_executable(SDG_Tests "SDG_Tests.cpp" DelegateTests.cpp PathTests.cpp)
target_link_libraries(SDG_Tests PRIVATE SDG_Engine Catch2)

target_include_directories(SDG_Tests PRIVATE ${CMAKE_SOURCE_DIR}/src
        lib/Catch2/src)

# Set up content pipeline
include(${CMAKE_SOURCE_DIR}/cmake/SDG_AddContentPipeline.cmake)
AddContentPipeline(assets john316)
