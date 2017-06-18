# Dependencies #

See `../.travis.yml` for details.

Tested on Debian 9 64-bit.

## x86 ##

```
# test
apt install grub-common grub-pc-bin xorriso mtools virtualbox-5.1
```

# To Do #

- Try embedding PicoLisp to check how easy/hard it is. (ECL? Io? Chibi-Scheme?)
  - Verify requirements: CFFI C/Java, immutable maps/sets/lists, unwind, Unicode, scope, prototype
  - Remove or cleanup Boynton Scheme?
    - Simple functional tests with Valgrind.
    - Fix no output when cwd isn't the source code path.
    - Move library to a separate directory.
    - Compile as C++.
    - Use readline.
    - Reformat indentation.
    - Consistent naming.
  - Resources:
    - https://news.ycombinator.com/item?id=1591172
    - https://github.com/kanaka/mal
    - http://matt.might.net/articles/programming-with-continuations--exceptions-backtracking-search-threads-generators-coroutines/
    - http://norvig.com/lispy.html
    - https://github.com/copy/v86
    - http://www.nongnu.org/libunwind/
    - https://sourceware.org/libffi/
- Create library folder that each implementation uses, so that it can be embedded.
- Rename "x86" to "intel-x86".
- Use `grub-file` to verify kernel image is bootable.
- Tests, coverage, lint, static analysis, continuous integration, memory check.
  - Automation: Vagrant, Docker?
  - https://autotest.github.io
  - https://scan.coverity.com
  - https://travis-ci.org # validate `.travis.yml` file
  - https://github.com/andrewrk/malcheck
  - https://github.com/google/sanitizers
  - http://clang-analyzer.llvm.org
- Clean up, simplify, remove double blank lines, more flat less nested, remove useless TODO comments and documentation (document only what's need, eg. log's format string grammar), use single-line comments, remove `this->`.
- Colored native logging.
- Logging of long integers.
- Make warnings fatal.
- Drop x86 support and switch to x64?
  - ASFLAGS += -f elf64
  - CCFLAGS += -m64
  - LINKFLAGS += -m elf_x86_64
- Upgrade to Multiboot 2.
- Modern C, `#pragma once`
- Use exceptions to reduce coupling between components? Eg. no need to call System::stop() directly, calls to Log::error() will throw an exception.
