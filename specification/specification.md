# Structure

## Module

A Unicode textual representation of expressions encoded in UTF-8 without a Byte Order Mark, with a valid symbol for its name.

# Prototypes

## Boolean

A binary logical value that can only be either true or false.

## Function

An immutable sequence composed of a function followed by zero or more values, the arguments. It extends the list prototype.

Calling a function creates a new scope, prototypically inherited from the previous scope, composed of closure variables and deferred argument key/value pairs, and then evaluates it in this new scope returning the result.

### Examples

```
(+ 1 2)
# 3
```

## List

An immutable sequence of elements. It extends the map prototype by associating consecutive positive integers with elements in ascending order of keys.

### Examples

```
[]
# []

["x" "y"]
# ["x" "y"]

[8 2 2 'key: 'value]
# [8 2 2 key: value]

['name: "Bob"]
# [name: "Bob"]
```

## Map

An immutable collection of unique keys and of values, where each unique key is associated with a single value.

If a given key has no associated value, it's then handled as in a set, where the key and value are one and the same.

If the same key is repeated multiple times, it's associated with only the last value.

### Examples

```
{}
# {}

{'name: "Bob" 'age: 30}
# {name: "Bob" age: 30}

{"x" "y"}
# {"x" "y"}

{8 2 2 'key: 'value}
# {8 2 key: value}
```

## Number

A quantity.

### Examples

```
2
# 2

-7.3
# -7.3

+9
# 9

1.(3)
# 1.(3)

4_294_967_296
# 4294967296
```

## Reference

A mutable container for a value. It extends the list prototype by restricting its length to exactly one element and making the key and value one and the same.

### Examples

```
(reference "Bob")
```

## Symbol

An immutable case-sensitive name. It extends the text prototype by restricting the characters that can be used.

### Examples

```
'abc
# abc

'is?
# is?

'!
# !

'...
# ...
```

## Text

An immutable sequence of Unicode characters, each one identified by a code-point. It extends the list prototype by associating non-negative integer elements to code-points.

### Examples

```
""
# ""

"Bob"
# "Bob"

"x"
# "x"
```

# Built-ins

## `=`

```
(= x y ...): Boolean
```

A function that compares two or more values and returns true if they are all equal, or false otherwise.

If less than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

### Examples

```
(= 1 1.0)
# true

(= 1 +1)
# true

(= -0 +0)
# true

(= "A" "A" "A")
# true

(= "A" "a")
# false

(= [1 2 3] [1 2 3])
# true

(= [] {})
# false

(= {0 1} {1 0})
# true

(= 0 "")
# false
```

## `<`

```
(< x y ...): Boolean
```

A function that compares two or more numbers and returns true if each one is less than the next, or false otherwise.

If less than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug 'prototype-mismatch)`.

### Examples

```
(< 1 -2)
# false

(< 8 10 10.1)
# true
```

## `>`

```
(> x y ...): Boolean
```

A function that compares two or more numbers and returns true if each one is greater than the next, or false otherwise.

If less than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug 'prototype-mismatch)`.

## `+`

```
(+ x:Number ...): Number
```

A function that adds one or more numbers.

If no arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug 'prototype-mismatch)`.

Adding negative infinity to positive infinity returns the result of `(debug 'undefined-arithmetic)`.

## `-`

```
(- x:Number ...): Number
```

A function that subtracts one or more numbers.

If no arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug 'prototype-mismatch)`.

Subtracting infinity from infinity returns the result of `(debug 'undefined-arithmetic)`.

## `*`

```
(* x:Number y:Number ...): Number
```

A function that multiplies two or more numbers.

If less than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug 'prototype-mismatch)`.

Multiplying zero and infinity returns the result of `(debug 'undefined-arithmetic)`.

## `/`

```
(/ x:Number y:Number ...): Number
```

A function that divides two or more numbers.

If less than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug 'prototype-mismatch)`.

Dividing any number by zero or infinity by infinity returns the result of `(debug 'undefined-arithmetic)`.

### Examples

```
(/ 12 3)
# 4

(/ 7 10)
# 0.7

(/ 1 3)
# 0.(3)

(/ 0 6)
# 0

(/ 1 0.(0)1)
# infinity
```

## `debug`

```
(debug)
(debug name:Symbol)
```

A function that interrupts normal execution flow. In development mode it triggers a debugger, while in production mode it halts execution with an appropriate error message.

If more than one argument is passed, it returns the result of `(debug 'parameter-mismatch)`.

If the `name` argument isn't a symbol, it returns the result of `(debug 'prototype-mismatch)`.

## `defer`

```
(defer expression)
(defer expression escape:Symbol)
```

A function that creates a snapshot of an expression thereby preventing it from being evaluated.

If less than one or more than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If the `escape` argument isn't a symbol, it returns the result of `(debug 'prototype-mismatch)`.

### Examples

```
(let x: 2

  (+ 1 x)
  # 3

  '(+ 1 x)
  # (+ 1 x)

  (defer (+ 1 x))
  # (+ 1 x)

  (defer (+ 1 (escape x)) 'escape))
  # (+ 1 2)
```

## `evaluate`

```
(evaluate expression)
(evaluate expression scope)
```

A function that evaluates an expression, optionally in a different scope, and returns the result.

If zero or more than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

### Examples

```
(evaluate "Bob")
# "Bob"

(let x: '(+ 8 2)

  (evaluate x)
  # 10

  (evaluate 'x))
  # (+ 8 2)

(let y: 2

  (evaluate 'y)
  # 2

  (evaluate 'y {'y: 8})
  # 8

  (evaluate 'y scope))
  # 2
```

## `get`

```
(get map:Map key)
```

A function that retrieves the value associated with a key in a map.

If less or more than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If the `map` argument isn't a map, it returns the result of `(debug 'prototype-mismatch)`.

If the association does not exist, it returns the result of `(debug 'unkown-key)`.

### Examples

```
(get [8 2 2] 1)
# 8

(get {"a" "b"} "b")
# "b"

(get '(+ 6 7) 2)
# 6

(let user: {'name: "Bob"}

  (get user 'name)
  # "Bob"

  user::name)
  # "Bob"
```

## `load`

```
(load module:List): Text
```

A function that loads a module by pathname.

A pathname is a list of zero or more names, ending with the module name.

### Examples

```
(load ['server])
(load ['image 'parser])
```

## `parse`

```
(parse expressions:Text): List
```

A function that parses the textual representation of one or more expressions, and returns a list of them parsed.

### Examples

```
(parse "123")
# [123]

(parse """Bob""")
# ["Bob"]

(parse "{x y} z")
# [{x y} z]

(parse "")
# []
```

## `prototype`

```
(prototype value)
(prototype value base-prototype)
```

A function that retrieves the original value used to create another one from, also known as its prototype, and optionally extends the prototype hierarchy creating a new prototype.

The prototype of a prototype is its base prototype, or itself if it doesn't have one.

If zero or more than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

When extending the prototype hierarchy, if both the `value` and `base-prototype` don't share a common ancestor prototype, it returns the result of `(debug 'prototype-mismatch)`.

### Examples

```
(prototype "Bob")
# ""

(prototype "")
# ""

(prototype [8 2 2])
# []

(prototype get)
# ()

(prototype 8)
# 0

(let Person: (prototype {'name: ""} {})
     bob: (put Person 'name "Bob")

  Person
  # {name: "" age: 0}

  (prototype Person)
  # {}

  bob
  # {name: "Bob" age: 20}
  
  (prototype bob)
  # Person

  (prototype {'name: "Bob" 'age: 20}))
  # {}
```

## `put`

```
(put map:Map key): Map
(put map:Map key value): Map
```

A function that associates a key with a value in a map, and returns the new map.

If less than two or more than three arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If the `map` argument isn't a map, it returns the result of `(debug 'prototype-mismatch)`.

### Examples

```
(put [8] 1 9)
# [9]

(put ["x" "y"] 3 "z")
# ["x" "y" "z"]

(put ["x" "y"] 4 "z")
# [x y 4:z]

(put {1 2} 3)
# {1 2 3}

(put {} 'name "Bob")
# {name: "Bob"}

(put {'name: "Bob"} 'name "John")
# {name: "John"}
```

## `reduce`

```
(reduce map:Map default reducer:Function)
```

A function that iterates over a map, calling the reducing function with each previously returned value (starting with the initial default value), each map value, and each map key, and then returns the last reduced value.

If the map is empty the default value is immediately returned.

If less or more than three arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If the `map` argument isn't a map or the `reducer` argument isn't a function, it returns the result of `(debug 'prototype-mismatch)`.

### Examples

```
(reduce
  [8 2 2]
  0
  '(+ (get scope 1)
      (get scope 3)))
# 12
```

## `reference`

```
(reference value)
```

A function that creates a new reference to a value.

If less or more than one argument is passed, it returns the result of `(debug 'parameter-mismatch)`.

### Examples

```
(let name: (reference "Bob")

  (get name)
  # "Bob"

  (put name "John")

  (get name))
  # "John"
```

## `remove`

```
(remove map:Map key): Map
```

A function that disassociates a key from a value in a map, and returns the new map.

If less or more than two arguments are passed, it returns the result of `(debug 'parameter-mismatch)`.

If the `map` argument isn't a map, it returns the result of `(debug 'prototype-mismatch)`.

### Examples

```
(remove [8] 1)
# []

(remove ["x" "y"] 3)
# ["x" "y"]

(remove {"x" "y"} "y")
# {"x"}

(remove {'name: "Bob" 'age: 20} 'age)
# {name: "Bob"}
```

## `scope`

A reference to a map of identifiers to values in the current scope.

The scope map always prototypically inherits from the previous scope map, or none if it's the module scope map. Each function call creates a new scope map that prototypically inherits from the previous one, and this reference always points to the current one.

### Examples

```
(let x: 2

  x
  # 2

  (get (get scope) 'x)
  # 2

  (let x: 8

    x
    # 8

    (get (get scope) 'x)
    # 8

    (get (prototype (get scope)) 'x)))
    # 2

(let y: 3

  y
  # 3

  (put scope (put (get scope) 'y 5))

  y
  # 5)
```

# Grammar

The grammar is expressed in Extended Backus-Naur Form syntax with the following changes:

* `i*`: Zero or more occurrences of item `i`.
* `i+`: One or more occurrences of item `i`.
* `i?`: Optional item `i`.
* `i{x}`: Exactly `x` occurrences of item `i`.
* `not(i)`: Everything but the enclosed item `i`.
* `(U+x)`: Unicode character with hexadecimal value of `x`.

```
Expressions ::= White-Space* (Expression (White-Space+ Expression)* White-Space*)?
Expression ::= Defer* (Symbol | Number | Quantity | List | Map | Text | Function | Get-Expression)
White-Space ::= Space | End-of-Line | Comment
Comment ::= Comment-Quote not(End-of-Line)* End-of-Line
Symbol ::= not(Reserved-Character, White-Space, Sign, Digit) not(Reserved-Character, White-Space)* | Sign (not(Reserved-Character, White-Space, Digit) not(Reserved-Character, White-Space)*)?
Reserved-Character ::= List-Begin | List-End | Parenthesis-Begin | Parenthesis-End | Map-Begin | Map-End | Comment-Quote | Text-Quote | Defer | Pair-Separator
Quantity ::= Number (Symbol | Get-Expression)
Get-Expression ::= Symbol (Pair-Separator Pair-Separator Symbol)+
Number ::= Terminating-Decimal | Repeating-Decimal
Terminating-Decimal ::= Sign? Digits (Unit-Separator Digits)?
Repeating-Decimal ::= Sign? Digits Unit-Separator Digits? Parenthesis-Begin Digits Parenthesis-End Digits?
Digits ::= Digit+ (Digit-Group-Separator Digits)*
Pair ::= Expression Pair-Separator White-Space* Expression
Map-Expressions ::= White-Space* ((Expression | Pair) (White-Space+ (Expression | Pair))* White-Space*)?
Function ::= Parenthesis-Begin Map-Expressions Parenthesis-End
List ::= List-Begin Map-Expressions List-End
Map ::= Map-Begin Map-Expressions Map-End
Text ::= Literal-Text | Tagged-Text
Literal-Text ::= Text-Quote (not(Text-Quote) | Text-Quote{2})* Text-Quote
Tagged-Text ::= (Symbol | Get-Expression) Literal-Text (Symbol | Get-Expression | Number | Quantity)?
Space ::= (U+20)
End-of-Line ::= (U+A)
Comment-Quote ::= # (U+23)
Text-Quote ::= " (U+22)
Defer ::= ' (U+27)
Parenthesis-Begin ::= ( (U+28)
Parenthesis-End ::= ) (U+28)
Map-Begin ::= { (U+7B)
Map-End ::= } (U+7D)
List-Begin ::= [ (U+5B)
List-End ::= ] (U+5D)
Unit-Separator ::= . (U+2E)
Pair-Separator ::= : (U+3A)
Digit-Group-Separator ::= _ (U+5E)
Sign ::= + (U+2B) | - (U+2D)
Digit ::= 0 (U+30) | 1 (U+31) | 2 (U+32) | 3 (U+33) | 4 (U+34) | 5 (U+35) | 6 (U+36) | 7 (U+37) | 8 (U+38) | 9 (U+39)
```

## Transformations

These are the syntactic transformations that occur for each associated non-terminal. Each letter represents a matching element of a grammar production.

|Non-Terminal    |Syntax|Transformation|Association   |Example     |
|----------------|------|--------------|--------------|------------|
|*Get-Expression*|`x::y`|`(get x 'y)`  |Left to right.|`user::name`|
|*Tagged-Text*   |`xyz` |`(x y z)`     |              |`hex"1F"`   |
|*Quantity*      |`xy`  |`(y x)`       |              |`2Km`       |
|*Defer*         |`'x`  |`(defer x)`   |              |`'length`   |

# Coding Style

The human language used should be English.

## Documentation

Documentation should be written in [CommonMark](http://commonmark.org) format.

## Naming

All names should use hyphens as the word delimiter.

### Function

The name of a function should use a verb as the first word. If it is an accessor function it should end in `-of`. Predicate functions should instead append a `?` to the name.

### Module

The name of a module should be a noun, in lower-case.

### Prototype

The name of a prototype should be a noun, properly capitalized.
