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
    set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS TRUE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_EXPORT=true)


project(game_plugin)
    add_library(${PROJECT_NAME} MODULE game_plugin.c)
    target_link_libraries(${PROJECT_NAME} PRIVATE engine)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_IMPORT=true)