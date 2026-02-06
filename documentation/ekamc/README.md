# How to build with CMake

To get started with CMake I recommend you explore the files in this directory tree and read the explanation comments I put alongside the commands and syntax.

This directory tree contains a multi-project CMake repository. It contains a main project and two subprojects libraries independent of each other. The main project depends on both subprojects and links to them statically and dynamically.

The reccomended tour is [CMakeLists.txt](./CMakeLists.txt) -> [compile_commands.cmake](./compile_commands.cmake) -> [deps/my_math/CMakeLists.txt](./deps/my_math/CMakeLists.txt) -> [deps/my_print/CMakeLists.txt](./deps/my_print/CMakeLists.txt). You may take a look at the c source code at any moment too as you need.

A neat way to excercise your learning about CMake is to try build, configure, modify or run the projects yourself!

## TODO

These topics are yet undocumented in their respective source files.

Guys, I will cover and push them later. Don't worry.

- [ ] Configure and build from command line
- [ ] [CMakePresets.json](./CMakePresets.json) and [CMakeUserPresets.json](./CMakeUserPresets.json)
