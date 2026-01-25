cmake_minimum_required(VERSION 3.30)
add_compile_options(
    -Wall
    -Werror
    -Wextra
    -Wpedantic
)

project(engine)
    add_executable(${PROJECT_NAME} engine.c)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_EXPORT=true)


project(game_plugin)
    add_library(${PROJECT_NAME} MODULE game_plugin.c)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_IMPORT=true)