- Build library for the native architecture, and use it in the built executable, so that it can be embedded.
- Use `grub-file` to verify kernel image is bootable.
- Test on Windows, Debian 32-bit (check again 64-bit dependencies on a pristine image).
- Tests (unit, functional), coverage, lint, static analysis, continuous integration, memory check (Valgrind).
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
- Prototypes (reqs: immutable collections, Unicode, prototype inheritance, first class scope, unlimited precision arithmetic -- symbolic computation provided by computer algebra system, homoiconic, unevaluated arguments)
  1. Create limited runtime support library only (eg. basic arithmetic, immutable collections, prototype inheritance). Easier and faster to experiment and test.
    - http://mathjs.org/docs/datatypes/bignumbers.html
  2. Write translator in C/C++, translate to PicoLisp (Common Lisp, Clojure with maybe even ClojureScript, or JavaScript likely to stay and be useful unlike the others, save maybe for PicoLisp since it could be embedded). Might even embed ECL or PicoLisp to make this transparent. Decouple each stage. Use the runtime library created in the previous version.
    - http://www.nongnu.org/libunwind/
    - https://sourceware.org/libffi/
    - libreadline
    - GNU MP / MPFR
  3. Skip translation, interpret directly. Look to PicoLisp for inspiration. Maybe still leave translation in as an option, especially if to JavaScript since that also makes the browser another possible host and can be useful (lower barrier to entry and also ability to use a single language full-stack).
  4. Integrate with the "core" hooks.
