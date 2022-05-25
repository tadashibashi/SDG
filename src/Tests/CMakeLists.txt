project(SDG_Tests)
add_subdirectory(lib/Catch2)

add_compile_definitions(SDG_NO_ENTRYPOINT)
if (EMSCRIPTEN)
    set(EmscriptenLinkerFlags "-sASSERTIONS -sASYNCIFY \
            -sINITIAL_MEMORY=268435456 -sALLOW_MEMORY_GROWTH \
            -sUSE_WEBGL2=1 -sWASM=2 -sMAX_WEBGL_VERSION=2 \
            -sNO_DISABLE_EXCEPTION_CATCHING -fexceptions")

    # Emscripten flag feature research:
    # Exceptions https://emscripten.org/docs/porting/exceptions.html
    # Asyncify runs Emscripten in a thread separate from browser input

    set(CMAKE_CXX_FLAGS "-Os -fexceptions -sUSE_SDL=2 -sUSE_SDL_TTF=2 ${CMAKE_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS  "${EmscriptenLinkerFlags} ${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

add_executable(SDG_Tests
        src/DelegateTests.cpp
        src/PathTests.cpp
        src/RefTests.cpp
        src/ServiceProviderTests.cpp
        src/WindowTests.cpp src/SDG_Tests.cpp
        src/ExceptionTests.cpp
        src/SDG_Tests.h
        src/KeyboardTests.cpp
        src/MathTests.cpp src/RandTests.cpp src/AppTimeTests.cpp src/Vector2Tests.cpp src/Vector3Tests.cpp src/RectangleTests.cpp src/ColorTests.cpp src/FontTests.cpp src/TweenTests.cpp src/PoolTests.cpp src/FixedPoolTests.cpp src/FileSysTests.cpp src/StringTests.cpp src/TweenerTests.cpp src/ShapeFunctionTests.cpp src/BufferTests.cpp "src/Camera2DTests.cpp")

target_include_directories(SDG_Tests PRIVATE ${CMAKE_SOURCE_DIR}/src
        lib/Catch2/src)
target_link_libraries(SDG_Tests PRIVATE SDG_Engine Catch2)
