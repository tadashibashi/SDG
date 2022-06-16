project(SDG_Sandbox)

if (EMSCRIPTEN) # -sASYNCIFY
    set(EmscriptenLinkerFlags "-sASSERTIONS  \
            -sINITIAL_MEMORY=268435456 -sALLOW_MEMORY_GROWTH \
            -sUSE_WEBGL2=1 -sWASM=2 -sMAX_WEBGL_VERSION=2 \
            -sLLD_REPORT_UNDEFINED -sNO_DISABLE_EXCEPTION_CATCHING \
            -sUSE_SDL=2 -sUSE_SDL_TTF=2 -O0")

    # Emscripten flag feature research:
    # Exceptions https://emscripten.org/docs/porting/exceptions.html
    # Asyncify runs Emscripten in a thread separate from browser input

    set(CMAKE_CXX_FLAGS "-fexceptions -O0 ${CMAKE_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS  "${EmscriptenLinkerFlags} ${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)

    add_custom_target(SDG_Sandbox_Emrun
        COMMAND "${CMAKE_SOURCE_DIR}/lib/emsdk/upstream/emscripten/emrun" "${CMAKE_CURRENT_BINARY_DIR}/SDG_Sandbox.html")
    add_dependencies(SDG_Sandbox_Emrun SDG_Sandbox)
endif()




add_executable(SDG_Sandbox
        Sandbox.cpp)

target_link_libraries(SDG_Sandbox PRIVATE SDG_Engine)

# Set up content pipeline
include(${CMAKE_SOURCE_DIR}/cmake/SDG_AddContentPipeline.cmake)
AddContentPipeline(assets john316)

