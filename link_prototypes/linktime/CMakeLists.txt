cmake_minimum_required(VERSION 3.30)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(
        -Wall
        -Wextra 
        -Werror 
        -Wpedantic 
    )
else()
    add_compile_options(/W4)
endif()

project(engine)
    add_library(${PROJECT_NAME} STATIC engine.c)
    

project(game_plugin)
    add_executable(${PROJECT_NAME} game_plugin.c)
    target_link_libraries(${PROJECT_NAME} PRIVATE engine)