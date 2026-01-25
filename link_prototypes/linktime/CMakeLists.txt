cmake_minimum_required(VERSION 3.30)

project(engine)
    if(MSVC)
        message(STATUS "Adding safety warnings to: MSVC")
        add_compile_options(
            /W4
            /WX
        )
    else()
        message(STATUS "Adding safety warnings to: GCC or Clang")
        add_compile_options(
            -Wall
            -Wextra 
            -Werror 
            -Wpedantic 
        )
    endif()
    
    add_library(${PROJECT_NAME} STATIC engine.c)
    

project(game_plugin)
    add_executable(${PROJECT_NAME} game_plugin.c)
    target_link_libraries(${PROJECT_NAME} PRIVATE engine)
