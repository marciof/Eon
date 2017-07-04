# Architecture

- `interpreter/`: implementation of the language specification
  - `core/`: host-independent core of the implementation, with host-dependent hooks for each system component, builds an embeddable library
  - `i386/`: Intel x86 32-bit host, builds a Multiboot-compliant executable
  - `native/`: native OS host (eg. Linux, Windows), builds a standalone executable
- `specification/`: language specification
- `stdlib/`: standard library for the interpreter
