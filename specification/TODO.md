- Specify prototypical inheritance (differential inheritance, eg. intro, `get`, `insert` and `remove` handling, etc): http://steve-yegge.blogspot.com/2008/10/universal-design-pattern.html
- Evaluate typing difficulty of each identifier and syntax quantitatively.
  - Can the syntax grammar be simplified without hurting readability and flexibility?
  - Use easier synonyms for hard to type words.
  - Bulk analyze source code out there for analysis?
  - Frequency of syntax tokens, familiarity, ease of typing, speaking, identifiers.
  - https://en.wikipedia.org/wiki/Comparison_of_programming_languages_(syntax)
  - http://hyperpolyglot.org/scripting
  - https://github.com/anvaka/common-words/blob/master/README.md
- http://www.infoq.com/presentations/Value-Identity-State-Rich-Hickey
- "Empirical Analysis of Programming Language Adoption", Leo A. Meyerovich, Ariel Rabkin: http://sns.cs.princeton.edu/docs/asr-oopsla13.pdf
- Look for best/worst features of other languages: Wren, Perl, F#, Matlab, Rust, Ruby, Go, Julia, JavaScript, Clojure, Kotlin, Python, Haskell, Erlang, Typed Racket, PureScript, Elm, Io, Smalltalk, Java, Scheme, ML, Lua, Haxe, Tcl, Shen, REBOL, Mathematica, HyperCard, Awk, Parabola.io, GNU Octave, Maxima Algebra System
- Indentation based syntax? The REPL becomes the shell, it just adds global functions as commands and other niceties.
  - If a line starts with a parenthesis it disables significant indentation inside the entire expression.
  - Otherwise each new line is a function call, with same-line arguments passed as-is, and indented new lines passed as function calls, unless it's a keyword argument.
  - All data types are callable as functions, and except for functions each value returns itself as the result.
- Guarantee efficient self-recursive function calls, tail function calls, and self-tail function calls?

# Functions

No need to have an easy built-in syntax for function literals with or without parameters, because there needs to be a helper for creating functions that throw exceptions on parameter validation anyway, such as number of parameters, type of parameters, preconditions, etc.

Deferred functions can be invoked, even though they might have symbols in it, because they're evaluated at call time. It also allows for optional dynamic binding, with the ability to inspect the function body.

Defer's escape function accepts a variable number of arguments to splice.

Lists have only numeric keys. Easy to iterate lists (randomly, backwards, binary search, etc).

Can build functions manually.

Specify that a symbol is also allowed as the first value in function lists.

```
let msg: 'hello'
  print msg

(defer ((escape + 1 2)) \escape)

# Optional prototype param to filter keys
(local list Number)
(local set ?)
```

## Questions

Grammar "generics" for list of symbols? Function calls too (eg. number units, tagged text literals). Remove grammar limitation and add runtime error checking since it's needed anyway?

Makes more sense to be a set/map since parameter names must be unique? Allows lists to have only numeric keys. However it equires more keystrokes to type the set syntax than the list syntax. But also don't want more than one way to do something. Would be nicer if the list syntax allowed for both at will, just like the function list syntax. Or the map merged with set even more.
