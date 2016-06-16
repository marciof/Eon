# To Do #

- Specify all values and built-ins.
- EBNF diagram: http://www.bottlecaps.de/rr/ui
- Specify documentation syntax.

# Research #

- Immutability by default? No need for defensive copying (eg "who owns this data"), easier for concurrency, etc. Clojure, Elm, ImmutableJs
- http://www.infoq.com/presentations/Simple-Made-Easy
- http://www.infoq.com/presentations/Value-Identity-State-Rich-Hickey
- Reactive programming.
  - https://gist.github.com/staltz/868e7e9bc2a7b8c1f754
  - count clicks stream eg: [---c----c--c->], map (1 each c), [---1----1--1->], scan(+), [---1----2--3->]
- Promises, async, await: https://zeit.co/blog/async-and-await
- Look for best/worst features of other languages: JavaScript, Clojure, Python, Perl, Ruby, Haskell, Io, Rust, Erlang, Smalltalk, Java, Scheme, Go, ML, Lua.

# Checklist #

- Data/code uniformity.
- Easy list, map, set and code literals. 
- Lazy arguments.
- Keyword arguments.
- Parameters with optional typing.
- Varargs.
- Dynamic function calls.
- Type identification.
- No null value.
- Shell language.
- Lazy functional. Eg. lazy.js, "no iteration takes place until you call each, and no intermediate arrays are created", `Lazy(txt).split("\n").take(5)`
