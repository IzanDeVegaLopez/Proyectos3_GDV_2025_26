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
    
    add_executable(${PROJECT_NAME} engine.c)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLUGIN_IMPORT=true)
    target_link_libraries(${PROJECT_NAME} PRIVATE game_plugin)


project(game_plugin)
    add_library(${PROJECT_NAME} SHARED game_plugin.c)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLUGIN_EXPORT=true)
