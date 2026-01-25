cmake_minimum_required(VERSION 3.30)
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(
        -Wall 
        -Werror
        -Wextra 
        -Wpedantic
    )
endif()

project(engine)
    add_executable(${PROJECT_NAME} engine.c)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLUGIN_IMPORT=true)
    target_link_libraries(${PROJECT_NAME} PRIVATE game_plugin)


project(game_plugin)
    add_library(${PROJECT_NAME} SHARED game_plugin.c)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLUGIN_EXPORT=true)