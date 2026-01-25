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
    add_library(${PROJECT_NAME} STATIC engine.c)
    

project(game_plugin)
    add_executable(${PROJECT_NAME} game_plugin.c)
    target_link_libraries(${PROJECT_NAME} PRIVATE engine)