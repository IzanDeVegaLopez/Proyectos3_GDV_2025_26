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
    set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS TRUE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_EXPORT=true)


project(game_plugin)
    add_library(${PROJECT_NAME} MODULE game_plugin.c)
    target_link_libraries(${PROJECT_NAME} PRIVATE engine)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_IMPORT=true)
