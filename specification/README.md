# To Do #

- Specify prototypal inheritance (eg. intro, `get` handling, etc).
  - http://steve-yegge.blogspot.com/2008/10/universal-design-pattern.html
- Make it clear that `scope` uses prototypal inheritance (it always inherits from the previous scope, on each function call, and the symbol always points to the latest one). Can use `prototype` to go up the `scope` chain, useful for debugging.
- How to do safe/restricted `evaluate`? Useful for evaluating user input without giving unrestricted access. Add a `scope` parameter?
- Add optional `data` parameter to `debug` for easier identification of what caused it?
- How to do test assertions? Reuse `debug` or add an `assert`? Or replace `debug` with `assert`, which may be more useful for preconditions?
- How to raise exceptions?
  - http://www.javaslang.io/javaslang-docs/#_try
  - http://michaeldrogalis.tumblr.com/post/40181639419/trycatch-complects-we-can-do-so-much-better
  - http://matt.might.net/articles/implementing-exceptions/
  - http://axisofeval.blogspot.com/2011/04/whats-condition-system-and-why-do-you.html
- http://www.infoq.com/presentations/Value-Identity-State-Rich-Hickey
- Look for best/worst features of other languages: JavaScript, Clojure, Python, Perl, Ruby, Haskell, Elm, Io, Rust, Erlang, Smalltalk, Java, Scheme, Go, ML, Lua, Haxe, Tcl, Shen.

# Requirements #

- Data/code uniformity.
- Easy literals: list, map, set and function.
- Lazy arguments.
- Keyword arguments.
- Optional typing.
- Varargs.
- Dynamic function calls.
- Type identification.
- No null value.
- Shell language support. http://rigaux.org/language-study/scripting-language/
- Live changes editor support. 
- Lazy functional. Eg. lazy.js, "no iteration takes place until you call each, and no intermediate arrays are created", `Lazy(txt).split("\n").take(5)`

# Guidelines #

- "A programming language is low level when its programs require attention to the irrelevant." (Alan Perlis).
- Low cognitive load and typing difficulty (US keyboard layout, favor home row keys).
