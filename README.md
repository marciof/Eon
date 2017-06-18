# Architecture #

- `interpreter/`: implementation of the language specification
  - `core/`: host-independent core of the implementation, with host-dependent hooks as C++ pure virtual functions for each system component (eg. `Log`)
  - `i386/`: Intel x86 32-bit host, builds a Multiboot-compliant executable
  - `native/`: native OS host (eg. Linux, Windows), builds a standalone executable and an embeddable library
- `specification`: language specification
- `stdlib/`: standard library for the interpreter
