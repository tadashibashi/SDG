project(SDG_Tests)

add_executable(SDG_Tests "SDG_Tests.cpp" "CryptoTest.h" DelegateTests.h)
add_test(EngineTests SDG_Tests)
target_link_libraries(SDG_Tests PRIVATE SDG_Engine)

target_include_directories(SDG_Tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Set up content pipeline
include(${CMAKE_SOURCE_DIR}/cmake/SDG_AddContentPipeline.cmake)
AddContentPipeline(assets john316)

if (EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "-Os")
    set(CMAKE_EXE_LINKER_FLAGS "-sFULL_ES2=1 -sUSE_WEBGL2=1 -sWASM=2 -sUSE_ZLIB -sMAX_WEBGL_VERSION=2 -sLLD_REPORT_UNDEFINED")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()