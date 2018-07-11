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

# Function parameters

```
let msg: 'hello'
  print msg

({x y}: + x y)
({x y:Number}: + x y)
([x y]: + x y)
([x y:Number]: + x y)

(x: + x 1)
({x}: + x 1)
([x]: + x 1)

({}: + 1 2)
([]: + 1 2)

(defer ((escape + 1 2)) \escape)

# Optional prototype param to filter keys
(local list Number)
(local set ?)
```

Rules: 
- Function literals use dynamic binding.
- Parameters are specified as sets.
- Defer's escape accepts varargs to splice.

No point in having specific syntax for parameters since there needs to be a helper for creating functions that throw exceptions on parameter validation anyway? (eg. number, type, etc.) Problem is being able to inspect a function body without specific syntax. 

Get prototype of a built in function to get the function definition data type? Or ()? How does that compare to quoting a function? What data type is it?

- Function call list
- Function definition list

Questions:
- Allow quoted parameter names to turn on/off deferred arguments? More performant and practical, but more complex syntax?
- Inspecting for names vs values in function definitions.
- Do validation on the number of parameters?
- How to accept varargs? Build function manually? Use a single symbol for the parameter list?
  - `([x y [rest]]: + 1 2)`
  - `([x y [] rest]: + 1 2)`
  - `([x y rest []]: + 1 2)`
- Allow attaching metadata to parameter definitions? Eg. could be used for type hints, default values.

Don't like the extra complexity. Much simpler to just always accept only plain function lists. Does `(evaluate +)` call it? If it doesn't then that means there should be a separate data type for function definitions vs function calls.

Confusion between building a function call vs a function definition?

Having dynamic binding still doesn't explain unquoted symbols in deferred function calls. Can store value, but then it can't be easily inspected. Always use evaluate? Or store function body as metadata? Unnecessarily complicated? Calling a function already evaluates, so a function list can have unquoted symbols? Can fix bindings to have lexical binding while using symbols in function lists for easy inspection.

Requirements:
- Force parameters to be specified only with a set, no lists.
- No need to quote parameters in function definitions, but if they're quoted it means they're deferred and not evaluated at call time.
- Lists have only numeric keys. Easy to iterate lists (randomly, backwards, binary search, etc).
- Set values are always unique.
- Can build functions manually.
- Syntax sugar for a single parameter.
- Varargs require manually building the function.
- Function definitions have dynamic binding by default. No implicit/hidden state in the form of attached lexical bindings. Can build functions manually.

  - Specify that a symbol is also allowed as the first value in function lists. (Grammar "generics" for list of symbols?) Function calls too (eg. number units, tagged text literals). Remove grammar limitation and add runtime error checking since it's needed anyway?
  - Document parameter mismatch error conditions when calling function definitions.
  - Makes more sense to be a set/map since parameter names must be unique? Allows lists to have only numeric keys. However it equires more keystrokes to type the set syntax than the list syntax. But also don't want more than one way to do something. Would be nicer if the list syntax allowed for both at will, just like the function list syntax. Or the map merged with set even more.
  - Are parameters auto deferred or can they have actual values, like optional type information?
