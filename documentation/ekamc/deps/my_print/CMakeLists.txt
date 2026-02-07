# Note: See the main `CMakeLists.txt` and `my_math/CMakeLists.txt` files for explanations of the CMake commands used in this file.

cmake_minimum_required(VERSION 3.30)

project(my_print)

    # Note: This is a dynamic library, so we need to specify the type as SHARED in the add_library() command.
    add_library(${PROJECT_NAME} SHARED)
    target_sources(${PROJECT_NAME}
        PRIVATE
            src/my_print.c

        PUBLIC
            FILE_SET ${PROJECT_NAME}_headers
            TYPE HEADERS
            BASE_DIRS src
            FILES
                src/my_print.h
    )

    # Note: This is a call as well to the target_compile_definitions() command,
    #- to define the preprocessor macro `MY_PRINT_EXPORT` for this library.
    #- The converse of what we did in the main `CMakeLists.txt` file.
    #- Because from this target's perspective, it is exporting its symbols.
    target_compile_definitions(${PROJECT_NAME} PRIVATE MY_PRINT_EXPORT=true)