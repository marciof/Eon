# To Do #

- Specify prototypical inheritance (eg. intro, `get` handling, etc).
  - http://steve-yegge.blogspot.com/2008/10/universal-design-pattern.html
- Remove `debug` (turn into exceptions with additional data on the error) and make `(defer)` return the current continuation for the current scope. Build exceptions on top of continuations. Build `assert` on top of exceptions.
  - http://www.javaslang.io/javaslang-docs/#_try
  - http://michaeldrogalis.tumblr.com/post/40181639419/trycatch-complects-we-can-do-so-much-better
  - http://matt.might.net/articles/implementing-exceptions/
  - http://axisofeval.blogspot.com/2011/04/whats-condition-system-and-why-do-you.html
- Indentation based/optional parentheses for shell/CLI?
- http://www.infoq.com/presentations/Value-Identity-State-Rich-Hickey
- https://eev.ee/blog/2016/12/01/lets-stop-copying-c/
- Need to specify which Unicode version is used?
- Look for best/worst features of other languages: JavaScript, Clojure, Python, Ruby, Haskell, Elm, Io, Rust, Erlang, Smalltalk, Java, Scheme, Go, ML, Lua, Haxe, Tcl, Shen, Matlab, R.
  - Perl Pocket Reference

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
- Exceptions (error handling).
- Shell language support. http://rigaux.org/language-study/scripting-language/
- Live changes editor support. 
- Lazy functional. Eg. lazy.js, "no iteration takes place until you call each, and no intermediate arrays are created", `Lazy(txt).split("\n").take(5)`

- "A programming language is low level when its programs require attention to the irrelevant." (Alan Perlis).
- Low cognitive load and typing effort (US keyboard layout, favor home row keys).
- Avoid verbs that are also nouns.
