project(SDG_Tests)
add_subdirectory(lib/Catch2)

add_compile_definitions(SDG_NO_ENTRYPOINT)


add_executable(SDG_Tests
        src/DelegateTests.cpp
        src/PathTests.cpp
        src/RefTests.cpp
        src/ServiceContainerTests.cpp
        src/WindowTests.cpp src/SDG_Tests.cpp)

target_include_directories(SDG_Tests PRIVATE ${CMAKE_SOURCE_DIR}/src
        lib/Catch2/src)
target_link_libraries(SDG_Tests PRIVATE SDG_Engine Catch2)
