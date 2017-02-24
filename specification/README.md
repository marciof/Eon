# To Do #

- Specify prototypical inheritance (eg. intro, `get` handling, etc).
  - http://steve-yegge.blogspot.com/2008/10/universal-design-pattern.html
- Make it clear that `scope` uses prototypical inheritance (it always inherits from the previous scope, on each function call, and the symbol always points to the latest one). Can use `prototype` to go up the `scope` chain, useful for debugging.
- How to do safe/restricted `evaluate`? Useful for evaluating user input without giving unrestricted access. Add a `scope` parameter?
- How to raise exceptions? (Build `assert` and `debug` on top of exceptions? `debug` needs optional `data` parameter for easier identification of what caused it?)
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
- Exceptions (error handling).
- Shell language support. http://rigaux.org/language-study/scripting-language/
- Live changes editor support. 
- Lazy functional. Eg. lazy.js, "no iteration takes place until you call each, and no intermediate arrays are created", `Lazy(txt).split("\n").take(5)`

# Guidelines #

- "A programming language is low level when its programs require attention to the irrelevant." (Alan Perlis).
- Low cognitive load and typing difficulty (US keyboard layout, favor home row keys).
