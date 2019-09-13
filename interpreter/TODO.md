# Ideas

- Quick and easy interactivity like GNU Octave (ie. Matlab).
- Able to run over SSH efficiently like X11?
- Unix tools philosophy for the interpreter? Command line options for each stage for textual output (easier to debug and integrate with other external tools without code linking?): stream tokens from input one per line, then parser, etc

# Resources

Memory management:

- malloc minimal implementation: https://github.com/microsoft/mimalloc

Arbitrary precision arithmetic:

- GMP, https://gmplib.org/
- LibBF, https://bellard.org/libbf/
- JavaScript BigInt, https://github.com/tc39/proposal-bigint

Immutable data structures:

- https://github.com/immerjs/immer

Compilation:

- LibJIT, https://www.gnu.org/software/libjit/

Lisp interpreters:

- Kilo LISP, http://t3x.org/klisp/index.html
- femtolisp, https://github.com/JeffBezanson/femtolisp
- Chicken Scheme, http://call-cc.org/
  - http://wiki.call-cc.org/man/4/Embedding
  - https://wiki.call-cc.org/man/4/Cross%20development

JavaScript interpreters:

- QuickJS, embeddable JavaScript: https://bellard.org/quickjs/
- Duktape, embeddable JavaScript: https://duktape.org/

# Cleanups

- Check licensing of libraries and tools/dependencies.
- Compile on both GCC and Clang for portability? Add optional "-Weverything" for Clang?
- Use ccache for speed? https://ccache.dev/
- Specify all build dependencies.
  - Sign-up to interest mailing lists.
  - How to test macOS?
  - Haven't built on Windows yet. Cross compile too? https://blog.svgames.pl/article/cross-compiling-c-programs-for-ms-windows-using-mingw
- Reproducible builds?
  - https://reproducible-builds.org/docs/
  - https://signal.org/blog/reproducible-android/
- Avoid using variable-length arrays.
- Why is the output directory of the cmake build in the root alongside sources and not in the build directory?
- Error handling:
  - Check uses of K_LOG_LEVEL_ERROR and whether it should be made an Err for proper logging elsewhere.
  - Make Err be the last param always for consistency.
  - Check places where it assumed K_LOG_LEVEL_ERROR was stopping the system.
  - Verify all uses of Err (where it's missing, where it's not needed, etc).
- How to have documentation comments within Assembly source code?
- C tidy/linter?
- JS uses the same native code, since it's just a backend for code generation, just like a real-time interpreter is another backend. So don't merge it into native to allow an embedded systems to just pick core+native, but merge JS-independent parts into core.
  - Start moving core stuff (eg. AST) from javascript/ to core/
  - Move non-essentials out of core/

# Implementation

- **Make a shell/REPL so that I can start using it ASAP, for early use and testing.** Phases:
  - Just echo back each line from stdin in a robust way.
  - Integrate with readline.
  - Syntax highlighting. (Language Server Protocol? https://langserver.org/)
  - Translate AST to a backend that writes JavaScript (browser and node?) and/or Lisp for a quicker first release? Can use an embedded interpreter to run it on spot.

# Testing

- Check style tool
- Memory leaks, Valgrind
- Static code analysis
  - cyclomatic-complexity
  - https://en.m.wikipedia.org/wiki/SonarQube
  - https://www.owasp.org/index.php/Static_Code_Analysis
  - shellcheck for shell scripts (add to dependencies as well)
  - https://yetanotherchris.dev/clean-code/gestalt-principles/
- Code coverage
- Continuous integration
  - Verify CMake version when installing? (See .travil.yml)
  - https://about.gitlab.com/
  - https://ci.appveyor.com/login
  - https://bitbucket.org/product/features/pipelines
  - https://github.com/travis-ci/travis-ci/issues/5770
  - https://docs.travis-ci.com/user/multi-os/
- Fuzzy testing, http://lcamtuf.coredump.cx/afl/
- Hashing DoS

---

- Don't use wrappers to access struct members directly.
- How to add full stack trace information to `Err` instances?
- Add Travis CI build matrix for the different builds (native, javascript, i386) and OSes.
- Regularly test building on Debian 32-bit 64-bit, Windows, macOS.
- Add simple v86 HTML demo?
- Replace flexible struct member (`val[]`) with a `void*` for portability and also to allow the struct interface to grow without breaking implementations.
- Redesign architecture, to make it easier to embed, no singletons, and easier to unit test:
  - Avoid all these repeated calls for `*_get()`?
  - Remove stop modes and use only reset or halt
  - main(multiboot_magic_num, multiboot_info)
- Tests (unit, functional), coverage, lint, static analysis, continuous integration, memory check (Valgrind).
  - Automation: Vagrant, Docker?
  - https://autotest.github.io
  - https://scan.coverity.com
  - https://travis-ci.org # validate `.travis.yml` file, fix build
  - https://github.com/andrewrk/malcheck
  - https://github.com/google/sanitizers
  - http://clang-analyzer.llvm.org
- Make it more resilient, warn more instead of aborting, and errors during logging too.
- Add location to log calls? function, file, line? Or to warnings and errors only?
- Add color to native logging.
- Logging of long integers.
- Add support for "amd64"?
  - ASFLAGS += -f elf64
  - CCFLAGS += -m64
  - LINKFLAGS += -m elf_x86_64
- Upgrade to Multiboot 2?
- https://github.com/copy/v86
- Option or tool to validate Coding Style guidelines.
- Verify space/time complexity in the spec matches the implementation.
- Prototyping:
  - "I Built a Lisp Compiler", https://news.ycombinator.com/item?id=19508616 (timmorgan.org)
  - "Lisp Shell", https://news.ycombinator.com/item?id=16878498, https://github.com/tonyg/racket-something
  - "Crafting Interpreters", Bob Nystrom: http://craftinginterpreters.com
  - "LispOS - Specification of a Lisp operating system.", Robert Strandh: http://metamodular.com/lispos.pdf
  - lexical analysis: Lexer, Tokenizer, Scanner / syntax analysis: Parser, Syntax Tree, Parse Tree
  - Start adding unit tests.
  - Add `getopt` with help screen, options, and version.
  - Add flag option to print token stream.
  - Add flag option for `-e` expressions.
  - Add verbose option, print func/file/line on errors only in debug mode.
  - Add few functional high-level black-box language tests, eg. input "(+ 1 2)", translate to JavaScript, run, output "3". (Or even with the token stream option alone as well). With Valgrind.
  - Add requirements one by one, even if with limitations (eg. no fully unlimited precision arithmetic at first): immutable collections, Unicode text, prototypical inheritance, first class scope, unlimited precision arithmetic, homoiconic, unevaluated arguments.
  - When done with JavaScript backend, start translating to PicoLisp (or even ECL, Common Lisp, Clojure) since it can be embedded (verify first), and reuse the tests written previously.
  - Skip translation and interpret directly. Look to PicoLisp for inspiration. Maybe still leave translation in as an option, especially if to JavaScript since that also makes the browser another possible host and can be useful (lower barrier to entry and also ability to use a single language full-stack).
    - http://www.nongnu.org/libunwind/
    - https://sourceware.org/libffi/
    - libreadline
    - GNU MP / MPFR
  - Finally integrate with the "core" hooks so that it works with any host layer available.

# Inspiration

## Unix shell

- POSIX compatibility
- Editing mode (readline compatibility): vi, Emacs; line/readline editing/moving keyboard shortcuts: line feed ctrl-j, backspace ctrl-h, tab
- Special variables: $PATH, $HOME, $USER
- Find where: command -v, which, whereis, whence
- Job control, `fg`, `bg`, `jobs`, `nice`, `&`, including keyboard shortcuts: ctrl-z
- Prompt: customizable, special escape sequence support
- Color support
- getopt compatibility
- Tilde notation, including home directory (eg. ~bob, ~bob/some-file, ~/my-file
- Wildcard expansion/globbing
- Brace expansion (maybe?), including ranges
- Unix IO: arbitrarily long byte sequences, everything is a file
- Standard IO: input, output, error
- Pipelines
- IO redirection
- Online help system
- Command history (shared? separate?)
- Completion: commands, variables, user names, host names, file names, directories
