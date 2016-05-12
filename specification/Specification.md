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

A function is a sequence composed of a function followed by zero or more expression arguments. It extends the *List* type.

Calling a function creates a new scope composed of the arguments, each one deferred, and then is evaluated within the new scope, returning the result.

### Examples ###

```
>>> (set 'double '(* 2 (get 1)))
(* 2 (get 1))
>>> (double 4)
8
```

## List ##

A list is a sequence of elements. It extends the *Map* type by associating consecutive positive integers with elements in ascending order of keys.

### Examples ###

```
>>> []
[]
>>> ["x" "y"]
["x" "y"]
>>> [8 2 2 'key: 'value]
[8 2 2 'key: 'value]
>>> ['name": "Bob"]
['name: "Bob"]
```

## Map ##

A map is a collection of unique keys and of values, where each unique key is associated with a single value.

If a given key has no associated value, it's then handled as in a set, where the key and value are one and the same.

If the same key is repeated multiple times, it's associated with only the last value.

### Examples ###

```
>>> {}
{}
>>> {'name: "Bob" 'age: 30}
{name: "Bob" age: 30}
>>> {"x" "y"}
{"x" "y"}
>>> {8 2 2 'key: 'value}
{8 2 key: value}
```

## Number ##

A number is a quantity.

### Examples ###

```
>>> 2
2
>>> -7.3
-7.3
>>> +9
9
>>> 1.(3)
1.(3)
```

## Symbol ##

A symbol is a case-sensitive name. It extends the *Text* type by restricting the characters that can be used.

### Examples ###

```
>>> 'abc
abc
>>> 'is?
is?
>>> '!
!
```

## Text ##

A text is a sequence of Unicode characters, each one identified by a code-point. It extends the *List* type by associating non-negative integer elements to code-points.

### Examples ###

```
>>> ""
""
>>> "Bob"
"Bob"
```

# Built-ins #

## `=` ##

Compares two or more values and returns true if they all are or have the same value, or false otherwise.

If less than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

```
(= x y ...) : Boolean
```

### Examples ###

```
>>> (= "A" "A")
true
>>> (= "A" "a")
false
>>> (= [1 2 3] [1 2 3])
true
>>> (= [] {})
false
>>> (= {0 1} {1 0})
true
>>> (= 0 "")
false
```

## `+` ##

Adds one or more numbers.

If no arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug 'type-mismatch)`.

Adding negative infinity to positive infinity returns the result of `(debug 'undefined-arithmetic)`.

```
(+ x:Number ...) : Number
```

## `-` ##

Subtracts one or more numbers.

If no arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug 'type-mismatch)`.

Subtracting infinity from infinity returns the result of `(debug 'undefined-arithmetic)`.

```
(- x:Number ...) : Number
```

## `*` ##

Multiplies two or more numbers.

If less than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug 'type-mismatch)`.

Multiplying zero and infinity returns the result of `(debug 'undefined-arithmetic)`.

```
(* x:Number y:Number ...) : Number
```

## `/` ##

Divides two or more numbers.

If less than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug 'type-mismatch)`.

Dividing any number by zero or infinity by infinity returns the result of `(debug 'undefined-arithmetic)`.

```
(/ x:Number y:Number ...) : Number
```

### Examples ###

```
>>> (/ 12 3)
4
>>> (/ 7 10)
0.7
>>> (/ 1 3)
0.(3)
>>> (/ 0 6)
0
>>> (/ 1 0.(0)1)
infinity
```

## `debug` ##

Interrupts normal execution flow.

If more than one argument is passed, it returns the result of `(debug 'parameter-mismatch)`.

If the `identifier` argument isn't a symbol, it returns the result of `(debug 'type-mismatch)`.

```
(debug)
```

```
(debug identifier:Symbol)
```

> **Note**
>
> While unspecified, the usual implementation triggers a debugger or halts execution with an appropriate error message.

## `defer` ##

Creates a snapshot of the current control flow (also known as a continuation), or of an expression thereby preventing it from being evaluated. The latter form is the named counterpart of the *Defer* grammar.

If more than two arguments are passed or the continuation isn't passed one argument, it returns the result of `(debug 'parameter-mismatch)`.

If the `escape` argument isn't a symbol, it returns the result of `(debug 'type-mismatch)`.

```
(defer) : Function
```

```
(defer expression)
```

```
(defer expression escape:Symbol)
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
>>> (* 2 (do (set 'c (defer)) (c 3)))
6
>>> (c 4)
8
>>> (c 2)
6
```

## `get` ##

Retrieves the value associated with a key in a collection or the environment by default.

If zero or more than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If the `map` argument isn't a map, it returns the result of `(debug 'type-mismatch)`.

If the association does not exist, it returns the result of `(debug 'undefined-key)`.

```
(get key)
```

```
(get map:Map key)
```

### Examples ###

```
>>> (get [8 2 2] 1)
8
>>> (get {"a" "b"} "b")
"b"
>>> (get {'name: "Bob"} 'name)
"Bob"
>>> (get '(+ 6 7) 2)
6
>>> (set 'x 3)
3
>>> (get 'x)
3
>>> x
3
```

## `load` ##

Loads a *module* or a *package* on a given path.

A path is a list of zero or more package names, ending with the name of the intended module or package.

```
(load package:List) : Map
```

```
(load module:List) : Text
```

## `parse` ##

Parses the textual representation of an expression.

```
(parse expression:Text)
```

```
(parse expression:Text position:Number)
```

## `prototype` ##

Retrieves the original value used to construct another one from.

If zero or more than one argument are passed, it returns the result of `(debug 'parameter-mismatch)`.

```
(prototype value)
```

### Examples ###

```
>>> (prototype "Hello")
""
>>> (prototype "")
""
>>> (prototype [8 2 2])
[]
>>> (prototype get)
()
>>> (prototype 8)
0
```

## `splice` ##

Adds elements to and removes keys from a map or the environment by default, and returns the changed collection.

If a key from a new key/value pair being added is already present, the new value replaces the previous one.

If removing non-contiguous positions (keys) from a list, new elements are added to the last specified position.

If less than two or more than three arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If the `map` argument isn't a map, it returns the result of `(debug 'type-mismatch)`.

```
(splice keys elements)
```

```
(splice map:Map keys elements)
```

### Examples ###

```
>>> (splice ["x" "y"] {2} ["z"])
["x" "z"]
>>> (splice ["x" "y"] {1} [])
["y"]
>>> (splice ["x" "y"] {2} ["z" "y"])
["x" "z" "y"]
>>> (splice ["x"] {} ["y" "z"])
["x" "y" "z"]
>>> (splice {} {'x: 3})
{x: 3}
>>> x
3
```

## `traverse` ##

This symbol names a function that optionally calls another function for every key/value pair of a map, and then returns the total number of pairs in the map.

```
(traverse map:Map) : Number
```

```
(traverse map:Map visitor:Function) : Number
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

These are the syntactic transformations that occur for each associated non-terminal. Each letter represents a matching element of a grammar production.

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
