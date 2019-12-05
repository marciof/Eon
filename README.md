# Introduction

A free/libre open source (FLOSS) programming language for interactive use, scripting, and building small to large programs, that aims to be simple, powerful, and practical.

It includes a well-defined specification, a platform-agnostic implementation core, and an interpreter for various operating systems and environments.

# Installation

## Dependencies

See `.travis.yml`.

### Windows

- [Visual Studio Build Tools](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=BuildTools)

## Building

1. Create a new directory to store the build artifacts.
2. *Optionally* configure which builds to create. By default it will build a native standalone executable only. Selecting the builds can be done in several different ways using CMake.
  - command-line:
    ```
    # List options:
    $ cmake -L -H
    # Build a Multiboot-compliant executable only:
    $ cmake -D BUILD_FOR_X86_32_HOST=ON -D BUILD_FOR_NATIVE_HOST=OFF path/to/sources
    ```
  - TUI:
    ```
    ccmake path/to/sources
    ```
  - GUI:
    ```
    cmake-gui path/to/sources
    ```
3. Invoke the build tool.
  ```
  $ cmake --build .
  ```

# Architecture

- `interpreter/`: implementation of the language specification
  - `core/`: builds an embeddable library with the host-independent core of the implementation and host-dependent hooks
  - `javascript/`: builds a standalone executable to compile to JavaScript
  - `native/`: builds an embeddable library and a standalone executable to run natively (eg. on Windows)
  - `x86-32/`: builds a Multiboot-compliant executable to run on an Intel x86 32-bit host
- `spec/`: language specification
- `stdlib/`: standard library for the interpreter
