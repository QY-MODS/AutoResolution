
function(automaticGameFolderOutput wildlander_output steam_owrt_output steam_mods_output)

    if(DEFINED ENV{WILDLANDER_OWRT_FOLDER} AND IS_DIRECTORY "$ENV{WILDLANDER_OWRT_FOLDER}" AND wildlander_output)
        copyOutputs("$ENV{WILDLANDER_OWRT_FOLDER}/${PRODUCT_NAME}${PROJECT_SUFFIX}")
    endif()
    if(DEFINED ENV{SKYRIM_OWRT_FOLDER} AND IS_DIRECTORY "$ENV{SKYRIM_OWRT_FOLDER}" AND steam_owrt_output)
        copyOutputs("$ENV{SKYRIM_OWRT_FOLDER}/${PRODUCT_NAME}${PROJECT_SUFFIX}")
    endif()
    if(DEFINED ENV{SKYRIM_MODS_FOLDER} AND IS_DIRECTORY "$ENV{SKYRIM_MODS_FOLDER}" AND steam_mods_output)
        copyOutputs("$ENV{SKYRIM_MODS_FOLDER}/${PRODUCT_NAME}${PROJECT_SUFFIX}")
    endif()
    if(DEFINED ENV{SKYRIM_MODS_FOLDER2} AND IS_DIRECTORY "$ENV{SKYRIM_MODS_FOLDER2}" AND steam_mods_output)
        copyOutputs("$ENV{SKYRIM_MODS_FOLDER2}/${PRODUCT_NAME}${PROJECT_SUFFIX}")
    endif()

endfunction()
