# Introduction

A free/libre open source (FLOSS) programming language for interactive use, scripting, and building small to large programs, that aims to be simple, powerful, and practical.

It includes a well-defined specification, a platform-agnostic implementation core, and an interpreter for various operating systems and environments.

# Structure

- `interpreter/`: Implementation of the language specification.
  - `core/`: Builds an embeddable library with the host-independent core of the implementation and host-dependent hooks.
  - `javascript/`: Builds a standalone executable to compile to JavaScript.
  - `native/`: Builds an embeddable library and a standalone executable to run natively (eg. on Windows).
  - `x86-32/`: Builds a Multiboot-compliant executable to run on an Intel x86 32-bit host.
- `library/`: Standard library for the interpreter.
- `specification/`: Language specification.

# Installation

## Dependencies

Per build target:

- `lint-documentation`
  - [Python 3](https://www.python.org/downloads/)
  - [commonmark](https://pypi.org/project/commonmark/)

### Linux

All build targets:

- `make` (POSIX compliant)

Per build target:

- `library`
  - Compiler: [GCC](https://gcc.gnu.org)
  - Librarian: `ar` (POSIX compliant)

### macOS

All build targets:

- `make` (POSIX compliant)

Per build target:

- `library`
  - Compiler: [Clang](https://clang.llvm.org)
  - Librarian: `ar` (POSIX compliant)

### Windows

All build targets:

- `nmake` (via [Visual Studio Build Tools](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=BuildTools))

Per build target:

- `library`
  - Compiler: `cl` (via [Visual Studio Build Tools](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=BuildTools))
  - Librarian: `lib` (via [Visual Studio Build Tools](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=BuildTools))

## Building

1. Create a new empty directory to store the build artifacts, and change to it.
2. Generate a build system [using CMake](https://cmake.org/runningcmake/) (see file `CMakeLists.txt` for the minimum supported version). The following steps assume running it from the command line:
   - By default it will build the core library only, but it can also be configured to select other builds. To view options:
     ```
     $ cmake -LH path/to/sources
     ```
   - Otherwise, to use the default options:
     ```
     $ cmake path/to/sources
     ```
3. Invoke the build tool:
   ```
   $ cmake --build .
   ```
