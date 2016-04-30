# To Do #

- Defer only quotes, as does function calling to arguments. A code list is always callable. What happens to symbols inside a code list? 
- Specify splice for each data type, and edge cases (eg. removing a key that doesn't exist).
- Specify all values and built-ins, how they are evaluated, and so on.
- Mention collection hierarchy (needed because "splice", "get", "traverse" work with any collection), and ":" is part of their syntax to associate a key with a value (quotes left value).
- Documentation via Python-like docstrings in Markdown format.
- EBNF diagram? http://www.bottlecaps.de/rr/ui

# Research #

- Indentation based syntax?
  - Optional parentheses for grouping.
  - Arguments are first space-separated, then line-separated by indentation.
  - Function calls with no arguments requires parentheses for disambiguation.
- http://www.infoq.com/presentations/Value-Values
- http://www.infoq.com/presentations/Simple-Made-Easy
- http://www.infoq.com/presentations/Value-Identity-State-Rich-Hickey
- Immutability by default? No need for defensive copying (eg "who owns this data"), easier for concurrency, etc. Clojure, Elm, ImmutableJs
- Transducers = transform + reduce.
  - "the reduce function is the base transformation; any other transformation can be expressed in terms of it (map, filter, etc)"
  - http://jlongster.com/Transducers.js--A-JavaScript-Library-for-Transformation-of-Data
  - http://blog.cognitect.com/blog/2014/8/6/transducers-are-coming
- Reactive programming.
  - https://gist.github.com/staltz/868e7e9bc2a7b8c1f754
  - count clicks stream eg: [---c----c--c->], map (1 each c), [---1----1--1->], scan(+), [---1----2--3->]
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
