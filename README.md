# PyTinySea

TinySea python binding

<!-- vim-markdown-toc GitLab -->

* [Installation](#installation)
    * [Build (c++)](#build-c)
    * [Build (python)](#build-python)

<!-- vim-markdown-toc -->

## Installation

### Build (c++)

To build this project you must have `conan`, `cmake` and a compiler that support cpp17.

```bash
git clone git@github.com:jorisv/tiny_sea
mkdir build
cd build
conan install ../tiny_sea -s compiler.cppstd=17 -b missing
cmake ../tiny_sea
make && ctest
```

### Build (python)

TODO
