project(SDG_Tests)

if (EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "-Os" ${CMAKE_CXX_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS "-sASSERTIONS -sASYNCIFY -sINITIAL_MEMORY=268435456 -sALLOW_MEMORY_GROWTH -sUSE_WEBGL2=1 -sWASM=2 -sUSE_ZLIB -sMAX_WEBGL_VERSION=2 -sLLD_REPORT_UNDEFINED" ${CMAKE_EXE_LINKER_FLAGS})
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

add_executable(SDG_Tests "SDG_Tests.cpp" DelegateTests.h)
target_link_libraries(SDG_Tests PRIVATE SDG_Engine)

target_include_directories(SDG_Tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Set up content pipeline
include(${CMAKE_SOURCE_DIR}/cmake/SDG_AddContentPipeline.cmake)
AddContentPipeline(assets john316)
