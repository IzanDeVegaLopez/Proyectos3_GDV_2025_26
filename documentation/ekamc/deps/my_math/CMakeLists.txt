# Note: This CMakeLists.txt file is very similar to
# the one in the root of the project. I will only new commands found here.

cmake_minimum_required(VERSION 3.30)

project(my_math)

    # Command: add_library(<target_name> [STATIC|SHARED|MODULE] [EXCLUDE_FROM_ALL])
    ## When this CMake project is built, it will generate a library named <target_name>.
    ## The type of library can be specified as STATIC, SHARED, or MODULE.
    ## If no type is specified, the library will be STATIC by default.
    
    # Note:
    #- A STATIC library is a library that is linked into the executable at compile time.
    #- A SHARED library is a library that is linked into the executable at runtime, and can be shared among multiple executables.
    #- A MODULE library is a library that is not linked into the executable, but can be loaded at runtime using dynamic loading mechanisms,
    #- such as dlopen() in Unix or LoadLibrary() in Windows. THIS IS THE TYPE OF LIBRARY OUR GAMES DLL WILL BE.
    add_library(${PROJECT_NAME} STATIC)
    target_sources(${PROJECT_NAME}
        PRIVATE
            src/my_math.c

        PUBLIC
            FILE_SET ${PROJECT_NAME}_headers
            TYPE HEADERS
            BASE_DIRS src
            FILES
                src/my_math.h
    )