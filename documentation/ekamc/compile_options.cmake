# Note: This commented out code is what a basic configuration of
#- the de-facto configuration of a CMake project would look like
#- If you came from 'CMakeLists.txt' this commented out snippet is 
#- what usually would be there, but we moved it to this separate file 'compile_options.cmake'
#- to 1. show how to include a separate CMake file in the main 'CMakeLists.txt'
#- and 2. to improve readability of the main 'CMakeLists.txt' file,
#- since below we perform some additional logic to check for compiler and linker flags and build type
#- to enable different compile and link options, such as sanitizers, in debug builds.

# Node:
#- Notice that in the code we use (ADD) 'add_compile_options()' 
#- while in the snippet we use (TARGET) 'target_compile_options()'.
#- IT IS ALWAYS VASTLY RECOMMENDED TO PREFER "TARGET" COMMANDS OVER "ADD" COMMANDS,
#- because "TARGET" commands allow you to specify the target to which the options will be applied,
#- while "ADD" commands apply to all targets in the directory and subdirectories. They are "global"!

# Note: That being said. Here we purposefully use 'add_compile_options()'
#- to apply the same strict compiler options to all targets in the project,
#- including our sub-projects and dependencies, such as 'my_math' and 'my_print'.

# Code:
# project(my_project)
#     if (MSVC)
#         target_compile_options(
#             main PRIVATE
#             /W4
#             /WX
#         )
#     else()
#         target_compile_options(
#              main PRIVATE
#             -Wall
#             -Werror
#             -Wextra
#             -Wpedantic
#         )
#     add_executable(main main.c)


# Command: if(<condition>)
## CMake has conditional statements
## It is very important that we evaluate them after a call to 'project()',
## because they ofen rely on variables that are set by the 'project()' command,
## such as 'CMAKE_BUILD_TYPE', 'CMAKE_CXX_COMPILER_ID', etc.
## MSVC is one of these variables, and it is set to true if the compiler is MSVC.
if (MSVC)
    add_compile_options(
        /W4
        /WX
    )
else()
    add_compile_options(
        -Wall
        -Werror
        -Wextra
        -Wpedantic
    )
    
    # Note: The above compiler options are their equivalent sets for MSVC and GCC/Clang.
    # These are: enabling all warnings, -Wall -Wextra -Wpedantic == /W4. These encompass a range of warnings.
    # And: treating warnings as errors, -Werror == /WX. This makes the build fail if there are any warnings.


    # Note: Here our intent is to enable CLANG'S SANITIZERS IN DEBUG BUILDS
    #- We do two checks. First we check if the build is a debug build.
    #- Then we check if the compiler and linker support the flags for the sanitizers.
    #- We do the second check because sanitizers are not supported by all compilers and linkers,
    #- and we want to avoid build errors in case they are not supported.
    #- The goal is to call 'add_compile_options(-fsanitize=address,undefined)' and 'add_link_options(-fsanitize=address,undefined)'.
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        include(CheckCompilerFlag)
        include(CheckLinkerFlag)

        check_linker_flag(C "-fsanitize=address" HAS_ASAN_LINK)
        check_compiler_flag(C "-fsanitize=undefined" HAS_UBSAN_FLAG)
        check_linker_flag(C "-fsanitize=undefined" HAS_UBSAN_LINK)

        # check_linker_flag(C "-static-libsan" HAS_STATIC_LIBSAN)
        if (HAS_ASAN_LINK AND HAS_UBSAN_FLAG AND HAS_UBSAN_LINK)
            add_compile_options(
                -fsanitize=address,undefined
            )
            add_link_options(
                # -v
                # -static-libsan
                -fsanitize=address,undefined
            )
            # add_compile_definitions(
            #     _NO_CRT_STDIO_INLINE
            # )
            # link_libraries(msvcrt ucrt msvcprt vcruntime legacy_stdio_definitions)
            # "CMAKE_MSVC_RUNTIME_LIBRARY": "MultiThreadedDebug"
        endif()
    endif()
endif()
