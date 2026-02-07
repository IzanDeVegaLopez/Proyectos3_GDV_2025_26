# How to build with CMake

<!-- TOC start (generated with https://github.com/derlin/bitdowntoc) -->

- [How to build with CMake](#how-to-build-with-cmake)
  - [Building from CLI](#building-from-cli)
  - [Configure and build](#configure-and-build)
    - [Verifying CMake installation](#verifying-cmake-installation)
    - [Your first CMake build](#your-first-cmake-build)
      - [Configure](#configure)
      - [Build](#build)
      - [Configuration Variables](#configuration-variables)
  - [CMake Presets](#cmake-presets)
  - [Running and Debugging](#running-and-debugging)
    - [Debugging](#debugging)

<!-- TOC end -->

To get started with CMake I recommend you explore the files in this directory tree and read the explanation comments I put alongside the commands and syntax.

This directory tree contains a multi-project CMake repository. It contains a main project and two subprojects libraries independent of each other. The main project depends on both subprojects and links to them statically and dynamically.

The reccomended tour is [`CMakeLists.txt`](./CMakeLists.txt) -> [`compile_commands.cmake`](./compile_commands.cmake) -> [`deps/my_math/CMakeLists.txt`](./deps/my_math/CMakeLists.txt) -> [`deps/my_print/CMakeLists.txt`](./deps/my_print/CMakeLists.txt). You may take a look at the c source code at any moment too as you need.

A neat way to excercise your learning about CMake is to try build, configure, modify or run the projects yourself!

## Building from CLI

CMake is a build system generator. That is why there are two steps on building your project with CMake.

### Configure and build

1. First we **configure** the project.
1. Then we **build** it.

Configuration is that of generating the build system files. For example, if you are on Linux and you have `make` installed, CMake will generate a `Makefile` for you. If you are on Windows and you have Visual Studio installed, CMake will generate a `.sln` file for you.

I, for example, run on windows but have installed Ninja as my build system. So it generates a `build.ninja` files for me.

Building is what generates the actual products you care about; i.e. executables and libraries. This step is what invokes the compiler and linker, the way you configured it in the previous step, to recursively build your project and all its dependencies. Linking libraries, resolving include paths, etc.

### Verifying CMake installation

To verify that you have CMake installed, you can run the following command in your terminal:

```bash
cmake --version
```

### Your first CMake build

Make a simple `CMakeLists.txt` file; like that in the commentted snippet of [`compile_options.cmake`](./compile_options.cmake) that builds a single "Hello, World!" source file with maybe some helper header.

Something like this:

```cmake
cmake_minimum_required(VERSION 3.30)

project(hello_world)
    add_executable(hello_world)
    target_sources(
        hello_world
        PRIVATE
            src/main.c
        
        PUBLIC
            FILE_SET hello_world_headers
            TYPE HEADERS
            BASE_DIRS src
            FILES
                src/hello_world.h
    )
```

Then, from the command line, we will do the [configure](#configure-and-build) step and then the [build](#configure-and-build) step.

#### Configure

```bash
cmake -B build
```

This is the most basic syntax to configure your CMake project. The argument after `-B` is the build directory. This is where the build files for the project are generated. This is one we **do not commit**. We could have called it `temp`, `out` for the purpose.

Written this way, CMake will use defaults for the arguments we have not specified. Such as the proper generator for your platform. And it will assume that the `CMakeLists.txt` file is in the current directory.

You can specify a different source directory with the `-S` flag; that is where it will look for the `CMakeLists.txt` file. And you can specify a different generator with the `-G` flag. For example, I invoke it to use Ninja on Windows like this:

```bash
cmake -G Ninja -B build 
```

Additionally, when you are making changes to the build system or CMake configuration files, you can use the `--fresh` flag to force CMake to regenerate the build files from scratch. This is useful when you want to ensure that all changes are properly reflected in the build system.

```bash
cmake -G Ninja -B build --fresh
```

#### Build

After you have run the commands of the [configure](#configure) step, you can build the project with the following command:

```bash
cmake --build build
```

Here we indicate after `--build` the build directory that we specified in the previous step. CMake will look for the build files in that directory and invoke the appropriate build system to build the project.

One thing we could do is to specify the target we want to build with the `--target` flag. Because we could have multiple targets across the *build tree*; like just (re)building a submodule. For example, if we have a target called `hello_world`, we can build it like this:

```bash
cmake --build build --target hello_world
```

If we want to make sure we are building all the source files and CMake has not cached any old results from previous builds, we can use the `--clean-first` flag to clean the build directory before building. This can be useful when we have moved build directories, sources, or just want to make sure we are building everything from scratch.

```bash
cmake --build build --clean-first
```

Now you know how to build your project with CMake from the command line!

In the next sections we explain how to configure settings and variables of your CMake project in a clean and portable way. Things like the compiler, the build type, the build directory, the target architecture and more are covered next.

#### Configuration Variables

To inform CMake about certain configuration values that we want for our project, such as the **C++ version**, **compiler**, **directories for the runtime output** (the executables), the library outputs, the intermediate build files, and more, we can use the `-D` flag.

The `-D` flag sets CMake variables from the command line at the [configure](#configure) step. For example, if we want to set the C++ standard to C++20, we can do it like this:

```bash
cmake -G Ninja -B build -D CMAKE_CXX_STANDARD=20
```

We can also change that information from the `CMakeLists.txt` file itself. While it is configuring, CMake can be told commands like:

```cmake
set(CMAKE_CXX_STANDARD 20)
```

But it is preferred not to pollute the `CMakeLists.txt` file with configuration information. It is better to keep it clean and portable. So we can set those variables from outside the `CMakeLists.txt` file.

Here is how various cache variables; the varaibles we are setting with `-D` are called cache variables; would be passed from the command line:

```bash
cmake -G Ninja -B build \
    -D CMAKE_CXX_STANDARD=20 \
    -D CMAKE_BUILD_TYPE=Debug \
    -D CMAKE_RUNTIME_OUTPUT_DIRECTORY=bin \
    -D CMAKE_LIBRARY_OUTPUT_DIRECTORY=lib \
    -D CMAKE_ARCHIVE_OUTPUT_DIRECTORY=lib
```

This quickly gets out of hand. And it is not portable. For that there are CMake Presets. They come in two flavors: [`CMakePresets.json`](./CMakePresets.json) and [`CMakeUserPresets.json`](./CMakeUserPresets.json).

## CMake Presets

CMake Presets are JSON files that contain the configuration variables for your project. You can have multiple presets for different configurations; like one for debug, one for release, one for testing, etc. And you can select the preset you want to use when configuring or building your project.

**Please take a look to [`CMakePresets.json`](./CMakePresets.json) and [`CMakeUserPresets.json`](./CMakeUserPresets.json)**. In them there are comments explaining all the relevant variables that they set up for the configure and build steps.

Just note that **`CMakePresets.json` is intended to be committed** to the repository and shared across all the developers working on the project. While **`CMakeUserPresets.json` is intended to be included in the `.gitignore`** and contain presets that are specific to your local machine and workflow. Both can work together and combine their configuration and presets.

For example, as I know we use different compilers for the project, no single specific compiler will be "set" in the common `CMakePresets.json`. But each member of the team should create their own `CMakeUserPresets.json` with presets that specify the compiler they have installed and want to use for the project.

They will make their presets "inherit"; see more in the [`CMakeUserPresets.json`](./CMakeUserPresets.json) sample included; from the common presets in `CMakePresets.json` and just adding the compiler specification to their own presets.

Now here, we will explain how the presets mechanism replace the previous command line syntax for configuring and building with CMake.

To [configure](#configure) with a preset, you can use the `--preset` flag followed by the name of the preset you want to use. For example, if you have a preset called `debug`, you can configure your project like this:

```bash
cmake --preset debug
```

To [build](#build) with a preset, you can also use the `--preset` flag followed by the name of the preset you want to use. For example, if you have a preset called `debug`, you can build your project like this:

```bash
cmake --build --preset debug
```

My personal **recommendation is that the "final" presets we use to build our project include in their name our target-triple**. In the example presets I have included `clang-debug-x64` and `clang-release-x64`. This way we can easily identify the target platform and configuration of the preset we are using; like the compiler it is using.

Finally, now **workflow presets** exist. When you have defined a configure and build preset. You can instruct CMake to do back to back the usual two commands we have to do to build our project:

```bash
cmake --preset debug
cmake --build --preset debug
```

Now with a workflow preset, we can do both steps with a single command:

```bash
cmake --workflow --preset debug
```

## Running and Debugging

After you have built your project, you can run the executables generated in the runtime output directory. For example, if you have an executable called `hello_world`, you can run it like this:

```bash
./bin/hello_world
```

In Windows it will have appended `.exe` to the executable name, so you can run it like this:

```bash
.\bin\hello_world.exe
```

### Debugging

For debugging your project, you can use a debugger that supports CMake projects. For example, if you are using Visual Studio, you can both:

- open the generated `.sln` file and set breakpoints and debug your project from there.
- or open the project folder; "as a folder"; and Visual Studio will automatically detect the CMake project and allow you to set breakpoints and debug your project from there. And show your in the dropdowns the different configurations, presets and targets you have in your project.

**I recommend you to use Visual Studio Code with the CMake Tools extension**. It provides a great experience for debugging CMake projects. You can set breakpoints, inspect variables, and step through your code with ease.

If you are using Visual Studio Code; like I do; you can run you project executable with the shortcut `Ctrl + Shift + F5`.

You can debug your project executable with the shortcut `Shift + F5`.

Additionaly, the the CMake Tools extension, shows you in the status bar the different presets and targets you have in your project. You can select the preset and target you want to build and run from there. As well as further options in the "CMake Tab" in the sidebar.
