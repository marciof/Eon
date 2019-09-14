# Installation

## Dependencies

### Linux

See `.travis.yml`.

### macOS

See `.travis.yml`.

### Windows

- CMake, v2.8 or higher
- [Visual Studio Build Tools](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=BuildTools)

## Building

1. Create an empty build directory somewhere outside the source code tree (to prevent mixing sources with builds).
2. *Optionally* configure which builds to create. By default it will build a native standalone executable only. Selecting the builds can be done in several different ways using CMake:
  - command-line:
    ```
    # List options:
    $ cmake -L -H
    # Build a Multiboot-compliant executable only:
    $ cmake -D BUILD_FOR_I386_HOST=ON -D BUILD_FOR_NATIVE_HOST=OFF path/to/sources
    ```
  - TUI:
    ```
    ccmake path/to/sources
    ```
  - GUI:
    ```
    cmake-gui path/to/sources
    ```
3. Start the build, using the appropriate tool for the chosen generator (eg. for Unix Makefiles do `make`).

# Architecture

- `interpreter/`: implementation of the language specification
  - `core/`: builds an embeddable library with the host-independent core of the implementation and host-dependent hooks
  - `i386/`: builds a Multiboot-compliant executable to run on an Intel x86 32-bit host
  - `javascript/`: builds a standalone executable to compile to JavaScript
  - `native/`: builds an embeddable library and a standalone executable to run natively (eg. on Windows)
- `spec/`: language specification
- `stdlib/`: standard library for the interpreter
