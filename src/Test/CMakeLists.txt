project(SDG_Tests)

add_executable(SDG_Tests "SDG_Tests.cpp" "CryptoTest.h")

target_link_libraries(SDG_Tests PRIVATE SDG_Engine)

target_include_directories(SDG_Tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
