project(SDG_ContentPipe)
add_executable(SDG_ContentPipe SDG_ContentPipe.cpp)

target_include_directories(SDG_ContentPipe PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(SDG_ContentPipe PROPERTIES
        CXX_STANDARD 20)

