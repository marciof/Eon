# Structure #

## Module ##

A module is the Unicode textual representation of *Expressions* encoded in UTF-8 without a Byte Order Mark, with a valid *Symbol* for its name.

> **Note**
>
> While unspecified, the usual implementation is a file or a stream.

## Package ##

A package is a set of zero or more modules and/or packages with a valid *Symbol* for its name.

> **Note**
>
> While unspecified, the usual implementation is a directory or a
> compressed file.

# Types #

## Boolean ##

A boolean is a binary logical value that can only be either *true* or *false*.

## Function ##

A function is a list composed of a function followed by zero or more expression arguments.

### Evaluation ###

1. Create a new scope composed of the arguments, each one deferred.
2. Evaluate the function within the new scope, and return the result.

### Examples ###

```
>>> (set 'double '(* 2 ((get 1))))
(* 2 ((get 1)))
>>> (double 4)
8
```

## List ##

A list is a sequence of zero or more elements.

### Examples ###

```
>>> ["x" "y"]
["x" "y"]
>>> [1 2 3 'key: 'value]
[1 2 3 'key: 'value]
```

## Map ##

A map is a collection of unique keys and of values, where each unique key is associated with a single value.

## Number ##

A number is a quantity.

The evaluator accepts a single number, and returns it unchanged.

```
(Number number:Number) : Number
```

## Set ##

A set is a collection of unique elements.

The evaluator accepts zero or more sets, and merges them into a new empty set.

```
(Set set:Set ...) : Set
```

## Symbol ##

A symbol is a case-sensitive name.

The evaluator accepts one or more symbols or one or more texts, and concatenates them into a new symbol. Texts are first converted to symbols.

```
(Symbol symbol:Symbol ...) : Symbol
```

```
(Symbol text:Text ...) : Symbol
```

### Text to Symbol Conversion ###

1. If the text is a grammatically valid *Symbol*, use each Unicode character as-is in sequence to build a new symbol and return it.
2. Otherwise, use the result of `(debug 'symbol text positions)` as the new text, where `text` is the given text and `positions` is a list of invalid character positions, and repeat this process from the start.

## Text ##

A text is a sequence of Unicode characters, each one identified by a code point.

The evaluator accepts zero or more texts or one or more code points, and concatenates them into a new empty text. Code points are first converted to characters.

```
(Text text:Text ...) : Text
```

```
(Text code-point:Number ...) : Text
```

### Code Point to Character Conversion ###

1. If the code point number is within the valid Unicode range, return the associated Unicode character.
2. Otherwise, use the result of `(debug 'text/character code-point)` as the new code point, where `code-point` is the given code point, and repeat this process
from the start.

# Built-ins #

## `=` ##

Compares two values and returns true if they are or have the same value, or false otherwise.

```
(= a b) : Boolean
```

### Examples ###

```
>>> (= "A" "A")
true
>>> (= "A" "a")
false
>>> (= '(1 2 3) '(1 2 3))
true
>>> (= () {})
false
>>> (= {0 1} {1 0})
true
>>> (= 0 "")
false
```

## `debug` ##

Interrupts normal execution flow.

```
(debug)
```

```
(debug identifier:Symbol ...)
```

> **Note**
>
> While unspecified, the usual implementation triggers a debugger or halts execution with an appropriate error message.

## `defer` ##

Creates a snapshot of the current control flow (also known as a continuation), or of an expression thereby preventing it from being evaluated. The latter form is the named counterpart of the *Defer* grammar.

```
(defer) : List
```

```
(defer expression)
```

```
(defer expression escape)
```

### Examples ###

```
>>> (set 'x 2)
2
>>> (+ 1 x)
3
>>> '(+ 1 x)
(+ 1 x)
>>> (defer (+ 1 x))
(+ 1 x)
>>> (defer (+ 1 (escape x)) 'escape)
(+ 1 2)
```

## `get` ##

This symbol names a function that retrieves the value associated with a key. If the association does not exist, it returns the result of either `(debug 'scope/key/undefined key)` or `(debug 'map/key/undefined key)` depending on which one was called.

```
(get key)
```

```
(get map:Map key)
```

## `load` ##

This symbol names a function that loads a *module* or a *package* on a given path.

A path is a list of zero or more package names, ending with the name of the intended module or package.

```
(load package:List) : Set
```

```
(load module:List) : Text
```

## `parse` ##

This symbol names a function that parses the textual representation of an expression.

```
(parse expression:Text)
```

```
(parse expression:Text position:Number)
```

## `prototype` ##

Retrieves the original value used to construct another from.

```
(prototype value)
```

### Examples ###

```
>>> (prototype "Hello")
""
>>> (prototype "")
""
>>> (prototype '(1 2 3))
()
>>> (prototype get)
get
```

## `splice` ##

This symbol names a function that adds elements and removes keys in a collection, and returns the changed collection. If no collection is specified, the environment is modified instead.

When the collection is a map, if a key from a new key/value pair being added is already present, the new value replaces the previous one.

```
(splice keys elements)
```

```
(splice collection keys elements)
```

### Examples ###

```
# Replace.
>>> (splice ["x" "y"] {2} ["z"])
["x" "z"]

# Remove.
>>> (splice ["x" "y"] {1} [])
["y"]

# Insert.
>>> (splice ["x" "y"] {2} ["z" "y"])
["x" "z" "y"]

# Concatenate.
>>> (splice ["x"] {} ["y" "z"])
["x" "y" "z"]

# Assign.
>>> (splice {} ['x: 3])
[x: 3]
>>> x
3
```

## `traverse` ##

This symbol names a function that optionally calls another function for every key/value pair of a map, and then returns the total number of pairs in the map.

```
(traverse collection) : Number
```

```
(traverse collection visitor:Function) : Number
```

# Grammar #

The grammar is expressed in Extended Backus-Naur Form syntax with the following changes:

* `i*`: Zero or more occurrences of item `i`.
* `i+`: One or more occurrences of item `i`.
* `i?`: Optional item `i`.
* `i{x}`: Exactly `x` occurrences of item `i`.
* `not(i)`: Everything but the enclosed item `i`.
* `(U+x)`: Unicode character with hexadecimal value of `x`.

```
Expressions ::= White-Space* (Expression (White-Space+ Expression)* White-Space*)?
Expression ::= Defer* (Symbol | Number | Quantity | List | Map | Text | Code | Ellipsis)
White-Space ::= Space | End-of-Line | Comment
Comment ::= Comment-Quote not(End-of-Line)* End-of-Line
Symbol ::= not(Reserved-Character, White-Space, Sign, Digit) not(Reserved-Character, White-Space)*
Reserved-Character ::= List-Begin | List-End | Code-Begin | Code-End | Map-Begin | Map-End | Comment-Quote | Text-Quote | Defer | Pair-Separator | Unit-Separator
Quantity ::= Number (Symbol | Dotted-Expression)
Number ::= Terminating-Decimal | Repeating-Decimal
Terminating-Decimal ::= Sign? Digit+ (Unit-Separator Digit+)?
Repeating-Decimal ::= Sign? Digit+ Unit-Separator Digit* List-Begin Digit+ List-End Digit*
List ::= List-Begin Expressions List-End
Dotted-Expression ::= Symbol (Unit-Separator Symbol)+
Map ::= Map-Begin White-Space* ((Expression | Pair) (White-Space+ (Expression | Pair))* White-Space*)? Map-End
Pair ::= Expression White-Space* Pair-Separator White-Space* Expression
Text ::= Literal-Text | Custom-Text
Literal-Text ::= Text-Quote (not(Text-Quote) | Text-Quote{2})* Text-Quote
Custom-Text ::= (Symbol | Dotted-Expression) Literal-Text (Symbol | Dotted-Expression | Number | Quantity)?
Code ::= Code-Begin White-Space* (Pair | Expression) (White-Space+ (Pair | Expression))* White-Space* Code-End
Ellipsis ::= Unit-Separator{3}
Space ::= (U+20)
End-of-Line ::= (U+A)
Comment-Quote ::= # (U+23)
Text-Quote ::= " (U+22)
Defer ::= ' (U+27)
Unit-Separator ::= . (U+2E)
Digit ::= 0 (U+30) | 1 (U+31) | 2 (U+32) | 3 (U+33) | 4 (U+34) | 5 (U+35) | 6 (U+36) | 7 (U+37) | 8 (U+38) | 9 (U+39)
Sign ::= + (U+2B) | - (U+2D)
Code-Begin ::= ( (U+28)
Code-End ::= ) (U+28)
Map-Begin ::= { (U+7B)
Map-End ::= } (U+7D)
List-Begin ::= [ (U+5B)
List-End ::= ] (U+5D)
Pair-Separator ::= : (U+3A)
```

## Transformations ##

These are the syntactic transformations that occur for each associated non-terminal. Each letter represents a matching element of a production.

|Non-Terminal       |Syntax|Transformation|Association   |
|-------------------|------|--------------|--------------|
|*Dotted-Expression*|`x.y` |`(get x 'y)`  |Left to right.|
|*Custom-Text*      |`xyz` |`(x y z)`     |              |
|*Quantity*         |`xy`  |`(y x)`       |              |
|*Defer*            |`'x`  |`(defer x)`   |              |

# Coding Style #

The human language used should be English.

## Naming ##

All names should use hyphens as the word delimiter.

### Function ###

The name of a function should use a verb as the first word. If it is an accessor function it should end in `-of`. Predicate functions should instead append a `?` to the name.

### Module ###

The name of a module should be a noun, in lower-case.

### Package ###

The name of a package should be a noun, in lower-case, and usually in singular form.

### Type ###

The name of a type should be a noun, properly capitalized.
