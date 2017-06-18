# Dependencies #

See `../.travis.yml` for details.

Tested on Debian 9 64-bit.

## i386 ##

```
# test
apt install grub-common grub-pc-bin xorriso mtools virtualbox-5.1
```

# To Do #

- Build library for the native architecture, and use it in the built executable, so that it can be embedded.
- Use `grub-file` to verify kernel image is bootable.
- Move dependencies to main README, and rename individual READMEs to TODOs.
- Test on Windows, Debian 32-bit (check again 64-bit dependencies on a pristine image).
- Tests, coverage, lint, static analysis, continuous integration, memory check (Valgrind).
  - Automation: Vagrant, Docker?
  - https://autotest.github.io
  - https://scan.coverity.com
  - https://travis-ci.org # validate `.travis.yml` file, fix build
  - https://github.com/andrewrk/malcheck
  - https://github.com/google/sanitizers
  - http://clang-analyzer.llvm.org
- Clean up, simplify, remove double blank lines, more flat less nested, remove useless TODO comments and documentation (document only what's need), remove stop modes and use only reset or halt.
- Colored native logging.
- Logging of long integers.
- Add support for "amd64"?
  - ASFLAGS += -f elf64
  - CCFLAGS += -m64
  - LINKFLAGS += -m elf_x86_64
- Upgrade to Multiboot 2?
- Use exceptions to reduce coupling between components? Eg. no need to call System::stop() directly, calls to Log::error() will throw an exception.
- https://github.com/copy/v86
- http://www.nongnu.org/libunwind/
- https://sourceware.org/libffi/
- libreadline
