# To Do #

- `scope` built-in, map, mutable, no optional parameters to `slice`, `get`, optional parameter to `evaluate` to run unsafe code.
- Specify all values and built-ins.
- EBNF diagram: http://www.bottlecaps.de/rr/ui
- Specify documentation format.
- Fix continuation example.

# Research #

- Immutability by default? No need for defensive copying (eg "who owns this data"), easier for concurrency, etc. Clojure, Elm, ImmutableJs
- http://www.infoq.com/presentations/Simple-Made-Easy
- http://www.infoq.com/presentations/Value-Identity-State-Rich-Hickey
- Look for best/worst features of other languages: JavaScript, Clojure, Python, Perl, Ruby, Haskell, Elm, Io, Rust, Erlang, Smalltalk, Java, Scheme, Go, ML, Lua.

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
