project(SDG_Sandbox)

if (EMSCRIPTEN)
    set(EmscriptenLinkerFlags "-sASSERTIONS -sASYNCIFY \
            -sINITIAL_MEMORY=268435456 -sALLOW_MEMORY_GROWTH \
            -sUSE_WEBGL2=1 -sWASM=2 -sMAX_WEBGL_VERSION=2 \
            -sLLD_REPORT_UNDEFINED -sNO_DISABLE_EXCEPTION_CATCHING")

    # Emscripten flag feature research:
    # Exceptions https://emscripten.org/docs/porting/exceptions.html
    # Asyncify runs Emscripten in a thread separate from browser input

    set(CMAKE_CXX_FLAGS "-fexceptions" ${CMAKE_CXX_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS  "${EmscriptenLinkerFlags} ${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()




add_executable(SDG_Sandbox
        Sandbox.cpp)

target_link_libraries(SDG_Sandbox PRIVATE SDG_Engine)

# Set up content pipeline
include(${CMAKE_SOURCE_DIR}/cmake/SDG_AddContentPipeline.cmake)
AddContentPipeline(assets john316)

