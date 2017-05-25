# To Do #

- Indicate time and space complexity for each operation.
- Make the first element in the scope for a function call the called function. Useful for the debugger.
- Specify prototypical inheritance (eg. intro, `get` `put` and `remove` handling, etc). http://steve-yegge.blogspot.com/2008/10/universal-design-pattern.html
- Rename `debug` to `rescue` for something similar to Common Lisp conditions (signaling a condition, handling it, and restarting).
  - The specification doesn't dictate how it's handled, but the core library uses continuations to implement a full condition system?
  - Add a `continuation` built-in to create (escape?) continuations?
  - Make `rescue` calls very specific, eg. `(rescue 'illegal-argument function: get parameter: 'map argument: 123)`
  - http://www.gigamonkeys.com/book/beyond-exception-handling-conditions-and-restarts.html
  - http://matt.might.net/articles/implementing-exceptions/
- Evaluate typing difficulty of each identifier quantitatively. Use easier synonyms for hard to type words.
- Look for best/worst features of other languages: JavaScript, Clojure, Kotlin, Python, Haskell, Erlang, PureScript, Elm, Io, Rust, Ruby, Smalltalk, Java, Scheme, Go, ML, Lua, Haxe, Tcl, Shen, Matlab, R, REBOL.
  - "Perl Pocket Reference"

Research:
- http://www.infoq.com/presentations/Value-Identity-State-Rich-Hickey
- Uniform zero handling? `0/n = 0*n = n*0 = 0%n = 0`
- How to have references in literal data structures? Needed for persisting state or configuration files?
- Indentation based, significant white-space? Useful for using the REPL as a shell itself.
- Add `count` built-in or let it be defined via `reduce`? Performance?
- Add `has?` built-in or let it be defined through conditions? Performance?

# Checklist #

- Data/code uniformity.
- Easy literals: list, map, set and function.
- Lazy arguments.
- Keyword arguments.
- Optional typing.
- Varargs.
- Dynamic function calls.
- Type identification.
- No null value.
- Multiple return values.
- Unicode (text) strings != byte strings.
- Error handling.
- Debugger.
- REPL.
- Shell scripting. http://rigaux.org/language-study/scripting-language/
- Embeddable as a scripting language.
- Documentation available at run-time.
- Live changes (hot-reloading) support.
- Package manager.
- Avoid verbs that are also nouns.
- Avoid the semipredicate problem.
- "A programming language is low level when its programs require attention to the irrelevant." (Alan Perlis).
- Low cognitive load and typing effort (US keyboard layout, favor home row keys).
