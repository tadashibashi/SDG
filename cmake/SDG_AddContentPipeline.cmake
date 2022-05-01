# Sets up content pipeline program to build
# @param AssetDir the relative path to the asset directory from the current CMakeLists's folder
# @param Key encryption key
function(AddContentPipeline AssetDir Key)

if (EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_CURRENT_BINARY_DIR}/${AssetDir}@${AssetDir}")
    message("Emscripten asset directory is set to: ${CMAKE_CURRENT_BINARY_DIR}/${AssetDir}@${AssetDir}")
else()
    if (WIN32)
        set(ContentPipe_BinaryDir ${CMAKE_BINARY_DIR})
        set(ContentPipe_AssetDir ${CMAKE_BINARY_DIR}/${AssetDir})
    else()
        get_target_property(ContentPipe_BinaryDir SDG_ContentPipe BINARY_DIR)
        set(ContentPipe_AssetDir ${CMAKE_CURRENT_BINARY_DIR}/${AssetDir})
    endif()
    add_custom_target("${PROJECT_NAME}_Content"
            COMMAND "${ContentPipe_BinaryDir}/SDG_ContentPipe"
            ${CMAKE_CURRENT_SOURCE_DIR}/${AssetDir} ${ContentPipe_AssetDir} ${Key})
    add_dependencies(${PROJECT_NAME} "${PROJECT_NAME}_Content")
    add_dependencies("${PROJECT_NAME}_Content" SDG_ContentPipe)
endif()
endfunction()
