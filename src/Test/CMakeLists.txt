project(SDG_Tests)

add_executable(SDG_Tests "SDG_Tests.cpp" "CryptoTest.h")

target_link_libraries(SDG_Tests PRIVATE SDG_Engine)

target_include_directories(SDG_Tests PRIVATE ${CMAKE_SOURCE_DIR}/src)


# Copy encrypted assets
add_custom_target(ProcessContent
        COMMAND "${CMAKE_BINARY_DIR}/SDG_ContentPipe" ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets john316)
add_dependencies(SDG_Tests ProcessContent)
add_dependencies(ProcessContent SDG_ContentPipe)