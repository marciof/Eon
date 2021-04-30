# Introduction

Karyon is a free/libre open source (FLOSS) programming language for interactive use, scripting, and building small to large programs, that aims to be simple, powerful, and practical.

It includes a well-defined specification, a platform-agnostic implementation core, and an interpreter for various operating systems and environments.

# Structure

Soure code layout:

- `interpreter/`: Implementation of the language specification.
  - `core/`: Builds an embeddable library with the host-independent core of the implementation and host-dependent hooks.
  - `native/`: Builds an embeddable library and a standalone executable to run natively (eg. Linux, Windows, MacOS).
  - `x86-32/`: Builds a Multiboot-compliant executable to run on an Intel x86 32-bit host.
- `library/`: Standard library for the interpreter.
- `specification/`: Language specification.

# Building

Supported operating systems:

- Linux
- macOS
- Windows

Supported build tools:

- `make` (POSIX compliant)
- `nmake` ([Visual Studio Build Tools](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=BuildTools))

After installing or building the required [dependencies](#dependencies) for a given build type, then run a supported build tool on the `all` target.

For example, to build and run the **native** executable on Linux:

```
interpreter/core/$ make all
interpreter/native/$ make all
interpreter/native/$ ./karyon
```

For example, to build and run (under a VM) the **x86-32** executable on Linux:

```
interpreter/core/$ make all
interpreter/x86-32/$ make all
interpreter/x86-32/$ ./vm.sh karyon-x86-32
```

## Dependencies

Dependencies by build type:

- `interpreter/`:
  - `core/`:
    - [compiler](#compiler)
    - [librarian](#librarian)
  - `native/`:
    - core build
    - [compiler](#compiler)
    - [linker](#linker)
  - `x86-32/`:
    - core build
    - (TODO list x86-32 build and run-time dependencies)

Dependencies by build target, shared across build types:

- `lint-documentation`
  - [Python 3](https://www.python.org/downloads/)
  - `requirements.lint-commonmark-links.txt` (for [pip](https://pip.pypa.io))
  - internet access for validating links

- `lint-sources-python`
  - [Python 3](https://www.python.org/downloads/)
  - `requirements.lint-sources-python.txt` (for [pip](https://pip.pypa.io))

### Compiler

Supported compilers:

- `c99` (POSIX compliant)
- [GCC](https://gcc.gnu.org)
- [Clang](https://clang.llvm.org)
- `cl` ([Visual Studio Build Tools](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=BuildTools))

### Librarian

Supported librarians:

- `ar` (POSIX compliant)
- `lib` ([Visual Studio Build Tools](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=BuildTools))

### Linker

(TODO list supported linkers)

# Development

To continuously and automatically build on source code changes and get immediate feedback, use the `dev` build target. It uses [watchexec](https://github.com/watchexec/watchexec) to monitor changes, with the `all` build target.

For example, to do development on and build the **native** executable on Linux using GCC, start with watching the core build:

```
interpreter/core/$ make dev CCNAME=gcc
```

And then separately watching the native build:

```
interpreter/native/$ make dev CCNAME=gcc
```
