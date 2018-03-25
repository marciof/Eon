# Architecture

- `interpreter/`: implementation of the language specification
  - `core/`: builds an embeddable library with the host-independent core of the implementation and host-dependent hooks
  - `i386/`: builds a Multiboot-compliant executable to run on a Intel x86 32-bit host
  - `javascript/`: builds a standalone executable to compile to JavaScript
  - `native/`: builds a standalone executable to run natively (eg. Linux, Windows)
- `specification/`: language specification
- `stdlib/`: standard library for the interpreter
