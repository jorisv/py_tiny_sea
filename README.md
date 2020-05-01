# PyTinySea

TinySea python binding

<!-- vim-markdown-toc GitLab -->

* [Installation](#installation)
    * [Build (C++)](#build-c)
    * [Create Conan package](#create-conan-package)
    * [Build (python)](#build-python)
* [Dev](#dev)
    * [Conan Workspace](#conan-workspace)

<!-- vim-markdown-toc -->

## Installation

Before doing any of theses steps you must have tiny\_sea in your [Conan cache](https://github.com/jorisv/tiny_sea#create-conan-package).

### Build (C++)

To build this project you must have `conan`, `cmake` and a compiler that support cpp17.

```bash
git clone https://github.com/jorisv/py_tiny_sea
mkdir build
cd build
conan install ../py_tiny_sea -s compiler.cppstd=17 -b missing
cmake ../py_tiny_sea
make && ctest
```

### Create Conan package

```bash
git clone https://github.com/jorisv/py_tiny_sea.git
conan create py_tiny_sea/ -s compiler.cppstd=17 -b missing
```

### Build (python)

```bash
git clone https://github.com/jorisv/py_tiny_sea.git
cd py_tiny_sea
python -m pip install .
```

## Dev

### Conan Workspace

To work on both [TinySea](https://github.com/jorisv/tiny_sea) and [PyTinySea](https://github.com/jorisv/py_tiny_sea) you can create Conan workspace.

In a directory create `conanws.yml` file with the right version:

```yaml
editables:
    tiny_sea/0.1.0:
        path: tiny_sea
    py_tiny_sea/0.1.0:
        path: py_tiny_sea
layout: layout
workspace_generator: cmake
root: py_tiny_sea/0.1.0
```

Create a `layout` file:

```ini
[source_folder]
.

[includedirs]
src

[libdirs]
../build/{{ reference.name }}/lib

[build_folder]
../build/{{ reference.name }}
```

Create a root `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.1)
project(root)
enable_testing()

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_BINARY_DIR}/conanworkspace.cmake)
conan_workspace_subdirectories()
```

Then clone both repository and install workspace:

```bash
git clone https://github.com/jorisv/tiny_sea.git
git clone https://github.com/jorisv/py_tiny_sea.git
mkdir build
cd build
conan workspace install .. -s compiler.cppstd=17 -b missing
cmake ..
make && ctest
```
