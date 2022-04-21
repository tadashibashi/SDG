# Sets up content pipeline program to build
function(AddContentPipeline AssetDir Key)
    add_custom_target("${PROJECT_NAME}_Content"
            COMMAND "${CMAKE_BINARY_DIR}/SDG_ContentPipe"
            ${CMAKE_CURRENT_SOURCE_DIR}/${AssetDir} ${CMAKE_BINARY_DIR}/${AssetDir} ${Key})
    add_dependencies(${PROJECT_NAME} "${PROJECT_NAME}_Content")
    add_dependencies("${PROJECT_NAME}_Content" SDG_ContentPipe)
endfunction()
