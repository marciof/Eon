# Table of Contents

- [Introduction](#introduction)
- [Structure](#structure)
  - [Module](#module)
- [Prototypes](#prototypes)
  - [Boolean](#boolean)
  - [Function](#function)
  - [List](#list)
  - [Map](#map)
  - [Number](#number)
  - [Reference](#reference)
  - [Symbol](#symbol)
  - [Text](#text)
- [Built-ins](#built-ins)
- [Grammar](#grammar)
- [Coding Style](#coding-style)

# Introduction

## Goals

Simple:
- Minimal syntax, but readable.
- Prototype-based object model.
- Flat over nested.
- No undefined behavior, consistent.
- Everything is a value, never null.
- Right things easier than wrong things, encouraged, and the only way.
- Immutable data structures (except for references), no defensive copying.
- Principle of Least Surprise: "The design should match the user's experience, expectations, and mental models."
- "Keep the language specification simple enough to hold in a programmer's head."

Powerful:
- Homoiconic, code as data.
- No arbitrary limits: "Zero-one-infinity rule".
- Unified macros, methods and functions. Callee controls argument evaluation.
- High-level: "A programming language is low level when its programs require attention to the irrelevant."
- Documentation available at run-time.
- Embeddable.

Practical:
- REPL.
- Fast enough.
- Easy data type literals: lists, maps, sets, functions, strings, numbers.
- Multi-platform: "Write once, run everywhere".
- Native code interop, FFI (Foreign Function Interface).
- Shell-scripting (hash-bang syntax, `#!`, naturally supported).
- Permissive license.
- Low cognitive load and typing effort (US keyboard layout, favor home row keys).

# Structure

## Module

A Unicode textual representation of expressions encoded in UTF-8 without a Byte Order Mark, with a valid [symbol](#symbol) for its name.

# Prototypes

A prototype is the original value used to create another one from. The prototype of a prototype is its base prototype, or itself if it doesn't have one (root prototype).

## Boolean

A binary logical value that can only be either true or false.

## Function

An immutable sequence composed of a function followed by zero or more values, the arguments. It extends the [list](#list) prototype.

Calling a function creates a new [scope](#scope) using the [deferred](#defer) function call list, [prototypically](#prototype) inherited from the previous scope, and then evaluates it in this new scope returning the result.

Arguments in a function call are specified positionally or via keyword parameters.

### Examples

```
(* 4 5)
# 3

(* multiplicand: 4 multiplier: 5)
# 20

\(- 1)
# (- 1)

()
# ()
```

## List

An immutable sequence of values. It extends the [map](#map) prototype by associating consecutive positive integer keys in ascending order with values.

### Examples

```
[]
# []

['x' 'y']
# ['x' 'y']

[8 2 2 \key: \value]
# [8 2 2 key: value]
```

## Map

An immutable insertion ordered collection of unique keys each one associated with a single value.

If a given key has no associated value, it's then handled as in a set where the key and value are the same, however they're still separate from each other. A set element expression is only evaluated once even though it's used for both the key and value.

If the same key is repeated multiple times, it's associated with only the last value.

### Examples

```
{}
# {}

{\name: 'Bob' \age: 30}
# {name: 'Bob' age: 30}

{'x' 'y'}
# {'x' 'y'}

{8 2 2 \key: \value}
# {8 2 key: value}
```

## Number

A rational number.

### Examples

```
2
# 2

-17.3
# -17.3

+9
# 9

1.(3)
# 1.(3)

4'294'967'296
# 4294967296

infinity
# infinity
```

## Reference

A mutable container for a value.

### Examples

```
(reference 'Bob')
# (reference 'Bob')
```

## Symbol

An immutable case-sensitive name. It extends the [text](#text) prototype by restricting the character set used.

### Examples

```
\abc
# abc

\is?
# is?

\!
# !

\...
# ...
```

## Text

An immutable sequence of Unicode characters, each one identified by a code-point. It extends the [list](#list) prototype by associating non-negative integer elements to code-points.

### Examples

```
''
# ''

'café'
# 'café'

'<a href=''http://www.example.com''>'
# '<a href=''http://www.example.com''>'
```

# Built-ins

## `=`

```
(= x y ...): Boolean
```

A [function](#function) that compares two or more values and returns true if they are all equal, or false otherwise.

### Conditions

If less than two arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

### Examples

```
(= 1 1.0)
# true

(= -0 +0)
# true

(= 'A' 'a')
# false

(= [1 2 3] [1 2 3])
# true

(= [] {})
# false

(= {0 1} {1 0})
# true
```

## `<`

```
(< x y ...): Boolean
```

A [function](#function) that compares two or more [numbers](#number) and returns true if each one is less than the next, or false otherwise.

### Conditions

If less than two arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug \prototype-mismatch)`.

## `>`

```
(> x y ...): Boolean
```

A [function](#function) that compares two or more [numbers](#number) and returns true if each one is greater than the next, or false otherwise.

### Conditions

If less than two arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug \prototype-mismatch)`.

## `+`

```
(+ x:Number ...): Number
```

A [function](#function) that adds one or more [numbers](#number).

### Conditions

If no arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug \prototype-mismatch)`.

Adding negative infinity to positive infinity returns the result of `(debug \undefined-arithmetic)`.

## `-`

```
(- x:Number ...): Number
```

A [function](#function) that subtracts one or more [numbers](#number).

### Conditions

If no arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug \prototype-mismatch)`.

Subtracting infinity from infinity returns the result of `(debug \undefined-arithmetic)`.

## `*`

```
(* multiplicand:Number multiplier:Number ...): Number
```

A [function](#function) that multiplies two or more [numbers](#number).

### Conditions

If less than two arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug \prototype-mismatch)`.

Multiplying zero and infinity returns the result of `(debug \undefined-arithmetic)`.

## `/`

```
(/ dividend:Number divisor:Number ...): Number
```

A [function](#function) that divides two or more [numbers](#number).

### Conditions

If less than two arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

If any of the arguments isn't a number, it returns the result of `(debug \prototype-mismatch)`.

Dividing any number by zero or infinity by infinity returns the result of `(debug \undefined-arithmetic)`.

### Examples

```
(/ 12 3)
# 4

(/ 1 3)
# 0.(3)
```

## `count`

```
(count map:Map): Number
```

A [function](#function) that returns the number of key/value pairs in a `map`.

### Conditions

If less or more than one argument is passed, it returns the result of `(debug \parameter-mismatch)`.

If the `map` argument isn't a map, it returns the result of `(debug \prototype-mismatch)`.

### Examples

```
(count {})
# 0

(count {\name: 'Bob'})
# 1

(count [\x \y])
# 2

(count {\x \y})
# 2

(count ())
# 0

(count \xyz)
# 3
```

## `debug`

```
(debug)
(debug name:Symbol)
```

A [function](#function) that interrupts normal execution flow. In development mode it triggers a debugger, while in production mode it halts execution with an appropriate error message.

### Conditions

If more than one argument is passed, it returns the result of `(debug \parameter-mismatch)`.

If the `name` argument isn't a symbol, it returns the result of `(debug \prototype-mismatch)`.

## `defer`

```
(defer expression)
(defer expression escape:Symbol)
```

A [function](#function) that creates a snapshot of an `expression`, optionally with an `escape` [symbol](#symbol) for re-enabling [evaluation](#evaluate) inside it, thereby preventing it from being evaluated.

### Conditions

If less than one or more than two arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

If the `escape` argument isn't a symbol, it returns the result of `(debug \prototype-mismatch)`.

### Examples

```
(let x: 2

  (+ 1 x)
  # 3

  \(+ 1 x)
  # (+ 1 x)

  (defer (+ 1 x))
  # (+ 1 x)

  (defer (+ 1 (escape x)) \escape))
  # (+ 1 2)
```

## `evaluate`

```
(evaluate expression)
(evaluate expression scope:List)
```

A [function](#function) that evaluates an `expression`, optionally in a different `scope`, and returns the result.

### Conditions

If zero or more than two arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

### Examples

```
(evaluate 'Bob')
# 'Bob'

(let x: \(+ 8 2)

  (evaluate x)
  # 10

  (evaluate \x))
  # (+ 8 2)

(let y: 2

  (evaluate \y)
  # 2

  (evaluate \y {\y: 8})
  # 8

  (evaluate \y (get scope)))
  # 2
```

## `get`

```
(get map:Map key)
```

A [function](#function) that retrieves the value associated with a `key` in a `map`.

```
(get reference:Reference)
```

A [function](#function) that dereferences a `reference`.

### Conditions

If less than one or more than two arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

If the `map` argument isn't a map or the `reference` argument isn't a reference, it returns the result of `(debug \prototype-mismatch)`.

If the association doesn't exist, it returns the result of `(debug \unkown-key)`.

### Examples

```
(get [8 2 2] 1)
# 8

(get {'a' 'b'} 'b')
# 'b'

(get \(+ 6 7) 2)
# 6

(get {} \name 'John')
# 'John'

(let user: {\name: 'Bob'}

  (get user \name)
  # 'Bob'

  user::name)
  # 'Bob'

(get (reference 123))
# 123
```

## `infinity`

A quantity greater than any [number](#number).

### Examples

```
(* 2 infinity)
# infinity

(/ 1 infinity)
# 0
```

## `insert`

```
(insert map:Map value): Map
(insert map:Map key value): Map
```

A [function](#function) that associates a `key` with a `value` in a `map`, and returns the new [map](#map).

If the `key` already exists, its value is instead replaced in [maps](#map) or displaced in [lists](#list).

If no `key` is passed, then the `value` is inserted at the end of the `map`.

```
(insert reference:Reference value): Reference
```

A [function](#function) that changes the referenced value in a `reference`, and returns the same [reference](#reference).

### Conditions

If less than two or more than three arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

If the `map` argument isn't a map or the `reference` argument isn't a reference, it returns the result of `(debug \prototype-mismatch)`.

### Examples

```
(insert [8] 1 9)
# [9 8]

(insert [8] 9)
# [8 9]

(insert ['x' 'y'] 3 'z')
# ['x' 'y' 'z']

(insert ['x' 'y'] 4 'z')
# [x y 4: z]

(insert {1 2} 3)
# {1 2 3}

(insert {} \name 'Bob')
# {name: 'Bob'}

(insert {\name: 'Bob'} \name 'John')
# {name: 'John'}

(insert {\name: 'Bob'} \name)
# {name}

(get (insert (reference 123) 321))
# 321
```

## `load`

```
(load path:List ...)
```

A [function](#function) that loads a [module](#module) by `path` with zero or more arguments, and returns the value from the last evaluated expression. A `path` is a list of zero or more names, ending with the [module](#module) name.

### Conditions

If less than one argument is passed, it returns the result of `(debug \parameter-mismatch)`.

If the `path` argument isn't a non-empty list of symbols, it returns the result of `(debug \prototype-mismatch)`.

If the specified module doesn't exist, it returns the result of `(debug \unknown-module)`.

If the specified module is empty, meaning it doesn't evaluate to least one value, it returns the  result of `(debug \empty-module)`.

### Examples

```
(load [\io])
```

## `local`

```
(local map:Map): Map
```

A [function](#function) that returns a [map](#map) with the non-inherited key/value pairs from a [prototyped](#prototype) `map`.

### Conditions

If less or more than one argument is passed, it returns the result of `(debug \parameter-mismatch)`.

If the `map` argument isn't a map, it returns the result of `(debug \prototype-mismatch)`.

### Examples

```
(let x: 1
  (let y: 2

    (local (get scope))
    # {y: 2}

    (prototype (get scope))))
    # {x: 1}
```

## `next`

```
(next map:Map)
(next map:Map key)
```

A [function](#function) that returns the first key or the key following `key` in a `map`.

### Conditions

If less than one or more than two arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

If the `map` argument isn't a map, it returns the result of `(debug \prototype-mismatch)`.

If the `map` is empty or `key` is the last key, it returns the result of `(debug \unknown-key)`.

### Examples

```
(next [\x \y \z])
# x

(next [\x \y \z] \y)
# z

(next {\name: 'Bob' \age: 20})
# name

(next (reference 8))
# 8
```

## `prototype`

```
(prototype value)
```

A [function](#function) that retrieves the [prototype](#prototypes) of `value`.

```
(prototype value base-prototype)
```

A [function](#function) that extends the prototype hierarchy using `base-prototype` thereby creating a new [prototype](#prototypes).

### Conditions

If zero or more than two arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

When extending the prototype hierarchy, if both the `value` and `base-prototype` don't share a common ancestor prototype, it returns the result of `(debug \prototype-mismatch)`.

### Examples

```
(prototype 'Bob')
# ''

(prototype '')
# []

(prototype [])
# {}

(prototype {})
# {}

(prototype [8 2 2])
# []

(prototype get)
# ()

(prototype 8)
# 0

(let Person: (prototype {\name: ''} {})
     bob: (insert Person \name 'Bob')

  Person
  # {name: '' age: 0}

  (prototype Person)
  # {}

  bob
  # {name: 'Bob' age: 20}
  
  (prototype bob)
  # Person

  (prototype (prototype bob)))
  # {}
```

## `reference`

```
(reference value)
```

A [function](#function) that creates a new reference to a `value`.

### Conditions

If less or more than one argument is passed, it returns the result of `(debug \parameter-mismatch)`.

### Examples

```
(let name: (reference 'Bob')

  (get name)
  # 'Bob'

  (insert name 'John')

  (get name))
  # 'John'
```

## `remove`

```
(remove map:Map key): Map
```

A [function](#function) that disassociates a `key` from a value in a `map`, and returns the new [map](#map).

If there's no such `key`, the same `map` is returned unchanged.

### Conditions

If less or more than two arguments are passed, it returns the result of `(debug \parameter-mismatch)`.

If the `map` argument isn't a map or is a reference, it returns the result of `(debug \prototype-mismatch)`.

### Examples

```
(remove [8] 1)
# []

(remove ['x' 'y'] 3)
# ['x' 'y']

(remove {'x' 'y'} 'y')
# {'x'}

(remove {\name: 'Bob' \age: 20} \age)
# {name: 'Bob'}

(remove {\name: 'Bob'} \age)
# {name: 'Bob'}
```

## `scope`

A [reference](#reference) to a [list](#list) mapping identifiers to values in the current scope.

The scope list always [prototypically](#prototype) inherits from the previous scope list, or none if it's the [module](#module) scope. Each [function](#function) call creates a new scope list that prototypically inherits from the previous one, and this reference always points to the current one.

### Examples

```
(let x: 2

  x
  # 2

  (get (get scope) \x)
  # 2

  (let x: 8

    x
    # 8

    (get (get scope) \x)
    # 8

    (get (prototype (get scope)) \x)))
    # 2

(let y: 3

  y
  # 3

  (insert scope (insert (get scope) \y 5))

  y
  # 5)
```

# Grammar

The grammar is expressed in Extended Backus-Naur Form syntax with the following changes:

* `i*`: Zero or more occurrences of item `i`.
* `i+`: One or more occurrences of item `i`.
* `i?`: Optional item `i`.
* `i{x}`: Exactly `x` occurrences of item `i`.
* `not(i)`: Anything except the enclosed item `i`.
* `"i" <U+x>`: Unicode character `i` with hexadecimal value of `x`.

Expression:

```
Expressions ::= White-Space* (Expression (White-Space+ Expression)* White-Space*)?
Expression ::= Defer* (Number | Symbol | Text | Map | List | Function | Get-Chain)
Defer ::= "\" <U+27>
```

White-space:

```
White-Space ::= " " <U+20> | End-of-Line | Comment
Comment ::= Comment-Quote not(End-of-Line)* End-of-Line
Comment-Quote ::= "#" <U+23>
End-of-Line ::= "" <U+A>
```

Number:

```
Number ::= Sign? Digit+ ("." <U+2E> (Digits | Digits? Parenthesis-Begin Digits Parenthesis-End))? Symbol?
Sign ::= "+" <U+2B> | "-" <U+2D>
Digits ::= Digit+ (Text-Quote? Digit+)*
Digit ::= "0" <U+30> | "1" <U+31> | "2" <U+32> | "3" <U+33> | "4" <U+34> | "5" <U+35> | "6" <U+36> | "7" <U+37> | "8" <U+38> | "9" <U+39>
```

Symbol:

```
Symbol ::= not(Reserved-Character, White-Space, Sign, Digit) not(Reserved-Character, White-Space)* | Sign (not(Reserved-Character, White-Space, Digit) not(Reserved-Character, White-Space)*)?
Reserved-Character ::= List-Begin | List-End | Parenthesis-Begin | Parenthesis-End | Map-Begin | Map-End | Comment-Quote | Text-Quote | Defer | Pair-Separator
```

Text:

```
Text ::= Symbol? Text-Quote (not(Text-Quote) | Text-Quote{2})* Text-Quote
Text-Quote ::= "'" <U+22>
```

Map:

```
Map ::= Map-Begin White-Space* ((Set-Value | Pair) (White-Space+ (Set-Value | Pair))* White-Space*)? Map-End
Set-Value ::= Expression
Pair ::= Expression Pair-Separator White-Space* Expression
Pair-Separator ::= ":" <U+3A>
Map-Begin ::= "{" <U+7B>
Map-End ::= "}" <U+7D>
```

List:

```
List ::= List-Begin White-Space* ((List-Value | Pair) (White-Space+ (List-Value | Pair))* White-Space*)? List-End
List-Value ::= Expression
List-Begin ::= "[" <U+5B>
List-End ::= "]" <U+5D>
```

Function:

```
Function ::= Parenthesis-Begin White-Space* (Expression (White-Space+ Expression)* White-Space*)? Parenthesis-End
Get-Chain ::= Symbol (Pair-Separator{2} Symbol)+
Parenthesis-Begin ::= "(" <U+28>
Parenthesis-End ::= ")" <U+28>
```

## Transformations

These are the syntactic transformations that occur for each associated non-terminal. Each letter represents a matching element of a grammar production.

|Non-Terminal       |Syntax|Transformation|Example       |Notes         |
|-------------------|------|--------------|--------------|--------------|
|*Get-Chain*        |`x::y`|`(get x \y)`  |`user::name`  |Left to right.|
|*Text*             |`xy`  |`(x y)`       |`hex'1F'`     |              |
|*List-Value*       |`x`   |`N:x`         |`['a']`       |Position `N`. |
|*Set-Value*        |`x`   |`x:x`         |`{123}`       |              |
|*Number*           |`xy`  |`(y x)`       |`2Km`         |              |
|*Defer*            |`\x`  |`(defer x)`   |`\length`     |              |

# Coding Style

The human language used should be English.

## Documentation

Documentation should be written in [CommonMark](http://commonmark.org) format.

## Naming

All names should use hyphens as the word delimiter.

### Function

The name of a [function](#function) should generally use a verb as the first word. Predicate functions should end in `?`. Mutator functions should end in `!`. Accessor functions should start with a noun instead of a verb and end in `-of`.

### Module

The name of a [module](#module) should be a noun, in lower-case.

### Prototype

The name of a [prototype](#prototype) should be a noun, capitalized.
