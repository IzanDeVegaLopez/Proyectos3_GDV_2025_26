cmake_minimum_required(VERSION 3.30)

project(any_vec)
    add_compile_options(
        -Wall
        -Werror
        -Wextra
        -Wpedantic
    )
    add_executable(${PROJECT_NAME} main.cpp tasy_any_vector.cpp)