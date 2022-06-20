# Sets up content pipeline program to build
# @param AssetDir the relative path to the asset directory from the current CMakeLists's folder
# @param Key encryption key
function(AddContentPipeline AssetDir Key)

    if (EMSCRIPTEN)
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_CURRENT_BINARY_DIR}/${AssetDir}@${AssetDir}")
    endif()
    set(ContentPipe_BinaryDir ${CMAKE_SOURCE_DIR}/bin)

    if (WIN32)
        set(Project_BinaryDir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    else()
        get_target_property(Project_BinaryDir ${PROJECT_NAME} BINARY_DIR)
    endif()

    set(ContentPipe_AssetDir ${Project_BinaryDir}/${AssetDir})

    add_custom_target("${PROJECT_NAME}_Content"
            COMMAND "${ContentPipe_BinaryDir}/SDG_ContentPipe"
            ${CMAKE_CURRENT_SOURCE_DIR}/${AssetDir} ${ContentPipe_AssetDir} ${Key} ${CMAKE_CURRENT_SOURCE_DIR}/${AssetDir}/assets.json)
    add_dependencies(${PROJECT_NAME} "${PROJECT_NAME}_Content")

    if (NOT EMSCRIPTEN)
        add_dependencies("${PROJECT_NAME}_Content" SDG_ContentPipe)
    endif()

endfunction()
