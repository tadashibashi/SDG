# Sets up content pipeline program to build
# @param AssetDir the relative path to the asset directory from the current CMakeLists's folder
# @param Key encryption key
function(AddContentPipeline AssetDir Key)
if (EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_BINARY_DIR}/${AssetDir}@${AssetDir}")
    message("Emscripten asset directory is set to: ${CMAKE_BINARY_DIR}/${AssetDir}@${AssetDir}")
else()
    add_custom_target("${PROJECT_NAME}_Content"
            COMMAND "${CMAKE_BINARY_DIR}/SDG_ContentPipe"
            ${CMAKE_CURRENT_SOURCE_DIR}/${AssetDir} ${CMAKE_BINARY_DIR}/${AssetDir} ${Key})
    add_dependencies(${PROJECT_NAME} "${PROJECT_NAME}_Content")
    add_dependencies("${PROJECT_NAME}_Content" SDG_ContentPipe)
endif()
endfunction()
