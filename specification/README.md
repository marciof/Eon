# To Do #

- Specify splice for each data type, and edge cases (eg. removing a key that doesn't exist).
- Simplify syntax, don't make it contextual, be easy to analyze and parsed without a symbol table.
- Specify all values and built-ins, how they are evaluated, and so on. Remove all mentions of "function".
- Add simple math operators.
- Mention collection hierarchy (needed because "splice", "get", "traverse" work with any collection), and ":" is part of their syntax to associate a key with a value (quotes left value).
- Documentation via Python-like docstrings in Markdown.
- EBNF diagram? http://www.bottlecaps.de/rr/ui

# Research #

- Built-in parallelism?
- http://www.infoq.com/presentations/Simple-Made-Easy
- www.infoq.com/presentations/Value-Identity-State-Rich-Hickey
- Immutability by default. No need for defensive copying (eg "who owns this data"), easier for concurrency, etc. Clojure, Elm, ImmutableJs
- Transducers = transform + reduce.
  - "the reduce function is the base transformation; any other transformation can be expressed in terms of it (map, filter, etc)"
  - http://jlongster.com/Transducers.js--A-JavaScript-Library-for-Transformation-of-Data
  - http://blog.cognitect.com/blog/2014/8/6/transducers-are-coming
- Lazy functional style.
  - http://philosopherdeveloper.com/posts/introducing-lazy-js.html
  - eager: text.split("\n").slice(0, 5)
  - lazy: Lazy(text).split("\n").take(5)
- Reactive programming.
  - https://gist.github.com/staltz/868e7e9bc2a7b8c1f754
  - count clicks stream eg: [---c----c--c->], map (1 each c), [---1----1--1->], scan(+), [---1----2--3->]
- http://blog.fogus.me/2011/09/08/10-technical-papers-every-programmer-should-read-at-least-twice/
- Look for best and worst features of other programming languages. Check JavaScript, Clojure, Python, Perl, Ruby, Haskell, Io, Rust, Erlang, Smalltalk, Java, Scheme, Go, ML, Lua.

# Checklist #

- Data/code uniformity.
- Easy list, map, set and code literals. 
- Lazy arguments.
- Keyword arguments.
- Dynamic function calls.
- Type identification.
- Varargs.
- Low cognitive load and typing difficulty (US keyboard layout, prefer home row keys).

# Scratchpad #

```
>>> {x: 1 y: 5} ## map
{x: 1 y: 5}
>>> {1 5 5} ## set
{1 5}
>>> {1 "x": "x"} ## map/set
{1 "x": "x"}
>>> [+ 1 5] ## list
[+ 1 5]
>>> '(+ 1 5) ## code
(+ 1 5)
>>> (+ 1 5) ## code evaluate
6
>>> 'x ## symbol
x
>>> '5 ## number
5
>>> (map [1 5] '(+ _ 1))
>>> (length [1 5])
>>> (range from: 1 to: 3)
```
