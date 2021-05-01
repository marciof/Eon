# Ideas

- Quick and easy interactivity like GNU Octave (ie. Matlab).
- Able to run over SSH efficiently like X11?
- Print type after each value in the REPL like Elm? eg. `5 : number`
- Unix tools philosophy for the interpreter? Command line options for each stage for textual output (easier to debug and integrate with other external tools without code linking?): stream tokens from input one per line, then parser, etc

# Resources

Memory management:

- malloc minimal implementation: https://github.com/microsoft/mimalloc

Arbitrary precision arithmetic:

- GMP, https://gmplib.org/
- LibBF, https://bellard.org/libbf/
- JavaScript BigInt, https://github.com/tc39/proposal-bigint

Immutable data structures:

- https://github.com/immerjs/immer (JavaScript)
- https://github.com/rtfeldman/seamless-immutable (JavaScript)
- https://github.com/slburson/fset (Common Lisp)

Compilation:

- LibJIT, https://www.gnu.org/software/libjit/

Lisp interpreters:

- Make-A-Lisp, https://github.com/kanaka/mal/blob/master/process/guide.md
- Kilo LISP, http://t3x.org/klisp/index.html
- femtolisp, https://github.com/JeffBezanson/femtolisp
- MicroScheme, https://ryansuchocki.github.io/microscheme/
- Gambit Scheme, http://gambitscheme.org/wiki/index.php/Main_Page
- Chicken Scheme, http://call-cc.org/
  - http://wiki.call-cc.org/man/4/Embedding
  - https://wiki.call-cc.org/man/4/Cross%20development

# Implementation

- **Make a shell/REPL so that I can start using it ASAP, for early use and testing.** Phases:
  - Just echo back each line from stdin in a robust way.
  - Integrate with readline.
  - Syntax highlighting. (Language Server Protocol? https://langserver.org/)
  - Translate AST to a backend that writes JavaScript (browser and node?) and/or Lisp for a quicker first release? Can use an embedded interpreter to run it on spot (pico Lisp).
    - Duktape, embeddable JavaScript: https://duktape.org/
    - QuickJS, embeddable JavaScript: https://bellard.org/quickjs/

# Testing

- profiling
  - Evaluation of CPU profiling tools: gperftools, Valgrind and gprof, https://news.ycombinator.com/item?id=21480984
  - flamegraphs, http://www.brendangregg.com/flamegraphs.html
- unit tests
- integration tests (Vagrant? Docker?)
- Code coverage
- Check style tool
- Memory leaks
  - Valgrind
  - https://github.com/andrewrk/malcheck
- Fuzzy testing
  - http://lcamtuf.coredump.cx/afl/
  - https://gitlab.com/akihe/radamsa
- scale testing (DoS on hashing, etc)

---

- https://github.com/GrapheneOS/hardened_malloc/blob/master/README.md
- malloc once for Str and other types
- https://danluu.com/input-lag/
- https://www.bearssl.org
- Travis CI make each interpreter sub-project a separate build
# native
# javascript
- valgrind
# vm.sh
- grub-common # contains grub-mkrescue to build a bootable ISO
- grub-pc-bin # PC/BIOS architecture version of GRUB (eg. non-UEFI)
- mtools # symlinked from mformat, needed by grub-mkrescue
- xorriso # create ISO files, needed by grub-mkrescue
# VirtualBox

- tooling, https://nullprogram.com/blog/2020/01/21/
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
  - Add few functional high-level opaque-box language tests, eg. input "(+ 1 2)", translate to JavaScript, run, output "3". (Or even with the token stream option alone as well). With Valgrind.
  - Add requirements one by one, even if with limitations (eg. no fully unlimited precision arithmetic at first): immutable collections, Unicode text, prototypical inheritance, first class scope, unlimited precision arithmetic, homoiconic, unevaluated arguments.
  - When done with JavaScript backend, start translating to PicoLisp (or even ECL, Common Lisp, Clojure) since it can be embedded (verify first), and reuse the tests written previously.
  - Skip translation and interpret directly. Look to PicoLisp for inspiration. Maybe still leave translation in as an option, especially if to JavaScript since that also makes the browser another possible host and can be useful (lower barrier to entry and also ability to use a single language full-stack).
    - http://www.nongnu.org/libunwind/
    - https://sourceware.org/libffi/
    - libreadline
    - GNU MP / MPFR
  - Finally integrate with the "core" hooks so that it works with any host layer available.

# Inspiration

# IDE

- Automatic completion (no keys needed to trigger)
- Spell-check
- Detects wrong commands proactively and prevents execution (underline like spell check).

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
- Pipelines, including named pipes
- IO redirection, including using any command as a file eg. `wc -o <(head file)`
- Online help system
- Command history (shared? separate?)
- Completion: commands, variables, user names, host names, file names, directories

---

500 Byte Images: The Haiku Vector Icon Format
http://blog.leahhanson.us/post/recursecenter2016/haiku_icons.html
