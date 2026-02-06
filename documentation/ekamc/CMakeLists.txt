# Command: cmake_minimum_required(VERSION <min_version>)
## Indicates minimum CMake version that your system ought to have installed to build this project.
## THIS IS MANDATORY IN ALL CORRECT 'CMakeLists.txt' FILES.
## Version 3.30 is quite modern but standard. Newer versions of CMake imply new and features and changes to old ones.
cmake_minimum_required(VERSION 3.30)


# Command: project(<project_name> [<language_name>...])
## Defines a new project in this CMakeLists.txt file named <project_name>.
## The main purpose of a project is to produce one or more targets from source files.
## Targets may aim to generate an executable, a library (static or dynamic), or a header-only library.
## Here we have arbitrarily called this project 'main'.
project(main)
    
    # Note: the first thing I consider we should do in each project is to:
    #- SET THE COMPILER OPTIONS, flags and language standard requirements
    #- and ADD ALL SUB-PROJECTS DEPENDENCIES that this project needs.

    # Command: include(<file_name>)
    ## Includes and executes the content of the file <file_name> in this CMakeLists.txt file.
    ## I made the 'compile_options.cmake' file to contain all the compiler options
    ## and flags that I want to use in this project and its dependencies.
    ## We could have put the content of 'compile_options.cmake' directly in this CMakeLists.txt file,
    ## but since it contained some additional logic to check for compiler and linker flags,
    ## I thought it would be better to separate it in its own file.
    
    # Command: add_subdirectory(<dir_name>)
    ## Adds a subdirectory to the build. This means that CMake will look for
    ## a CMakeLists.txt file in the <dir_name> directory and execute it as part of the build process.
    ## This is useful for organizing the project into multiple directories
    ## and for including dependencies, such as libraries, sub-projects/modules (of the engine), etc.
    include(compile_options.cmake)
    add_subdirectory(deps/my_math)
    add_subdirectory(deps/my_print)


    # Command: add_executable(<target_name>)
    ## When this CMake project is built, it will generate an executable named <target_name>.
    # Command: target_sources(<target_name> [<INTERFACE|PUBLIC|PRIVATE>] <source1> <source2> ...)
    ## The source files that will be compiled to generate this executable are specified in the target_sources() command.
    ## First we list the source files.
    ## Then we list their headers and directories.
    add_executable(${PROJECT_NAME})
    target_sources(
        ${PROJECT_NAME}
        PRIVATE
            src/main.c
            src/useful.c

        PUBLIC
            FILE_SET ${PROJECT_NAME}_headers
            TYPE HEADERS
            BASE_DIRS src
            FILES
                src/useful.h
    )
    
    # Note: Many CMake commands take a 'scope keyword' as an argument, which can be one of INTERFACE, PUBLIC, or PRIVATE.
    #- The commands that take these are commands that refer to targets, such as target_sources(), target_compile_definitions(), target_link_libraries(), etc.
    #- INTERFACE means that the property being set will only be used by targets that link to this target, but not by this target itself.
    #- PUBLIC means that the property being set will be used by this target and also by targets that link to this target.
    #- PRIVATE means that the property being set will only be used by this target, but not by targets that link to this target.
    
    #- Most of the time, we need not to expose the source files of a target to other targets, so we can use PRIVATE for the source files.
    #- However, if we want to expose some header files of a target to other targets, we can use PUBLIC for those header files.
    #- And then specify them in a FILE_SET, as shown in the example above.


    # Command: target_compile_definitions(<target_name> [<INTERFACE|PUBLIC|PRIVATE>] <definition1> <definition2> ...)
    ## This command is used to define preprocessor macros for the target <target_name>.
    ## Here we use it to employ the mechanism of symbol export and import in the 'my_print' library.
    ## Because 'my_print' is a dynamic library we want to link against.
    ## This is to toggle the '__declspec(dllexport)' and '__declspec(dllimport)' in the 'my_print' library code.
    # Note: this command can be used to define any preprocessor macro.
    #- Affecting, this way, to the compilation of the files if we have defined some macro conditional logic in the code.
    target_compile_definitions(${PROJECT_NAME} PRIVATE MY_PRINT_IMPORT=true)


    # Command: target_link_libraries(<target_name> [<INTERFACE|PUBLIC|PRIVATE>] <library1> <library2> ...)
    ## This command is used to specify the libraries that the target <target_name> will link against.
    ## Here we link the 'my_math' and 'my_print' libraries to our main executable target.
    ## When doing this, we also gain access to the include directories and compile definitions of those libraries.
    ## Here PRIVATE indicares that the 'my_math' and 'my_print' libraries will only be linked to this target, but not to targets that link to this target.
    ## CMake will recognise automatically which type of library 'my_math' and 'my_print' are, search (in system paths or sub-projects), and link them correctly.
    target_link_libraries(${PROJECT_NAME} PRIVATE my_math)
    target_link_libraries(${PROJECT_NAME} PRIVATE my_print)
