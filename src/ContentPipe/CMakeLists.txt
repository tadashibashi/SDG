project(SDG_ContentPipe)

add_executable(SDG_ContentPipe SDG_ContentPipe.cpp "ContentCache.h" "ContentCache.cpp")
target_link_libraries(SDG_ContentPipe PRIVATE crunch)
target_include_directories(SDG_ContentPipe PRIVATE 
    ${CMAKE_SOURCE_DIR}/lib/crunch/crunch
    ${CMAKE_SOURCE_DIR}/lib/json/include)

target_include_directories(SDG_ContentPipe PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(SDG_ContentPipe PROPERTIES
        CXX_STANDARD 20
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
