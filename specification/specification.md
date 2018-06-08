# Table of Contents

- [Introduction](#introduction)
- [Structure](#structure)
- [Prototypes](#prototypes)
  - [Boolean](#boolean)
  - [Function](#function)
  - [List](#list)
  - [Map](#map)
  - [Number](#number)
  - [Set](#set)
  - [Symbol](#symbol)
  - [Text](#text)
- [Built-ins](#built-ins)
  - [`=`](#equal)
  - [`<`](#less-than)
  - [`>`](#greater-than)
  - [`+`](#add)
  - [`-`](#subtract)
  - [`*`](#multiply)
  - [`/`](#divide)
  - [`bindings`](#bindings)
  - [`count`](#count)
  - [`defer`](#defer)
  - [`evaluate`](#evaluate)
  - [`get`](#get)
  - [`infinity`](#infinity)
  - [`insert`](#insert)
  - [`load`](#load)
  - [`local`](#local)
  - [`next`](#next)
  - [`prototype`](#prototype)
  - [`remove`](#remove)
  - [`unwind`](#unwind)
- [Grammar](#grammar)
  - [Transformations](#transformations)
- [Coding Style](#coding-style)

# Introduction

## Goals

Simple:
- Minimal syntax, but readable.
- Prototype-based object model.
- Flat over nested, helpers over wrappers.
- No undefined behavior, consistent, uniform.
- Everything is a value, never null.
- Right things easier than wrong things, encouraged, and the only way.
- Immutable data structures, no defensive copying.
- Principle of Least Surprise: *"The design should match the user's experience, expectations, and mental models."*
- *"Keep the language specification simple enough to hold in a programmer's head."*

Powerful:
- Homoiconic, code as data.
- No arbitrary limits: *"Zero-one-infinity rule."*
- Unified macros, methods and functions via multiple dispatch and callee controlling argument evaluation.
- High-level: *"A programming language is low level when its programs require attention to the irrelevant."*
- Documentation available at run-time.
- Embeddable.

Practical:
- REPL.
- Fast enough (zero-copy; quick feedback, low latency; or maximum resource usage when appropriate).
- Easy data type literals: lists, maps, sets, functions, text (strings), numbers.
- Multi-platform: *"Write once, run everywhere."*
- Native code interop, FFI (Foreign Function Interface).
- Shell-scripting (`#!`, hash-bang syntax naturally supported).
- Permissive license.
- Low cognitive load and typing effort (US keyboard layout, favor home row keys).
- Standard tooling: single-style source code formatter, testing framework, profiler, debugger local/remote, package manager, command-line documentation viewer.

# Structure

## Module

A Unicode textual representation of expressions encoded in UTF-8 without a Byte Order Mark, with a valid [symbol](#symbol) for its name.

# Prototypes

A [prototype](#prototype) is the original value used to create another one from. The prototype of a prototype is its base prototype, or itself if it doesn't have one.

Not all values can be literally represented in source code, since not all have an associated [grammar](#grammar) production. They can however be assigned names using [symbols](#symbol) and stored in the [bindings](#bindings) map.

## Boolean

A binary logical value that can only be either true or false. It does not have a literal source code representation.

- **Prototype:** true
- **Base Prototype:** -

### Examples

```
(prototype (= 1 1))
# true

(prototype (prototype (= 1 1)))
# true

(prototype (= 1 2))
# true

(prototype (prototype (= 1 2)))
# true
```

## Function

An immutable sequence composed of a function followed by zero or more values as the arguments. This sequence associates consecutive positive integer keys in ascending order with positional arguments, including any keyword arguments as well.

Calling a function creates a new [bindings](#bindings) map using the [deferred](#defer) function call, [prototypically](#prototype) inherited from the current bindings in scope, and then evaluates it using the new bindings returning the result. Calling an empty function evaluates to itself.

Code is decoupled from data, which means dynamic binding is the default behavior. However, lexical binding can also be implemented by closing `bindings`.

- **Prototype:** empty [function](#function), `()`
- **Base Prototype:** empty [map](#map), `{:}`

### Examples

```
(* 4 5)
# 20

(* multiplicand: 4 multiplier: 5)
# 20

(\(* 4 5))
# 20

\()
# ()

()
# ()

\(- 1)
# (- 1)

(prototype \(+ 1 2))
# ()

(prototype \())
# {:}
```

## List

An immutable sequence of elements, that associates consecutive positive integer keys in ascending order with values.

- **Prototype:** empty [list](#list), `[]`
- **Base Prototype:** empty [map](#map), `{:}`

### Examples

```
[]
# []

['x' 'y']
# ['x' 'y']

[8 2 2 \abc]
# [8 2 2 \abc]

(prototype ['x'])
# []

(prototype [])
# {:}
```

## Map

An immutable insertion ordered collection, that associates unique keys with values.

If the same key appears multiple times, the last associated value takes precedence over all previous ones.

- **Prototype:** empty [map](#map), `{:}`
- **Base Prototype:** -

### Examples

```
{:}
# {:}

{\name: 'Bob' \age: 20}
# {name: 'Bob' age: 20}

{\key: 8 \key: \value}
# {key: value}

(prototype {\name: 'Bob'})
# {:}

(prototype {:})
# {:}
```

## Number

A rational number.

- **Prototype:** integer zero, `0`
- **Base Prototype:** -

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

3Km
# (Km 3)

(prototype 3)
# 0

(prototype infinity)
# 0

(prototype 0)
# 0
```

## Set

An immutable collection of unique elements, that associates keys to be the same as values.

- **Prototype:** empty [set](#set), `{}`
- **Base Prototype:** empty [map](#map), `{:}`

### Examples

```
{}
# {}

{'x' 'y'}
# {'x' 'y'}

{8 2 2 \abc}
# {8 2 \abc}

(prototype {'x'})
# {}

(prototype {})
# {:}
```

## Symbol

An immutable case-sensitive name, that restricts the character set used according to the [grammar](#grammar). The empty symbol does not have a literal source code representation.

- **Prototype:** empty symbol
- **Base Prototype:** empty [text](#text), `''`

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

(prototype (prototype \xyz))
# ''
```

## Text

An immutable sequence of Unicode characters, each one identified by a numeric code-point. Also known as a string.

- **Prototype:** empty [text](#text), `''`
- **Base Prototype:** empty [list](#list), `[]`

### Examples

```
''
# ''

'café'
# 'café'

'<a href=''http://www.example.com''>'
# '<a href=''http://www.example.com''>'

hex'1F'
# (hex '1F')

(prototype 'Bob')
# ''

(prototype '')
# []
```

# Built-ins

In the following examples, `Any` is a placeholder that denotes any possible data type, and `...` is a placeholder that denotes zero or more arguments.

## `=` <a id="equal"/>

```
(= x:Any y:Any ...:Any): Boolean
```

A [function](#function) that compares two or more values (with short-circuit) and returns true if they are all equal, or false otherwise.

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Less than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`

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

## `<` <a id="less-than"/>

```
(< x:Number y:Number ...:Number): Boolean
```

A [function](#function) that compares two or more [numbers](#number) (with short-circuit) and returns true if each one is less than the next, or false otherwise.

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Less than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *Argument isn't a prototype of nor a number:* [unwinds](#unwind) global scope with `\prototype-mismatch`

## `>` <a id="greater-than"/>

```
(> x:Number y:Number ...:Number): Boolean
```

A [function](#function) that compares two or more [numbers](#number) (with short-circuit) and returns true if each one is greater than the next, or false otherwise.

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Less than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *Argument isn't a prototype of nor a number:* [unwinds](#unwind) global scope with `\prototype-mismatch`

## `+` <a id="add"/>

```
(+ x:Number ...:Number): Number
```

A [function](#function) that adds one or more [numbers](#number).

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *No arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *Argument isn't a prototype of nor a number:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *Adding negative and positive infinity:* [unwinds](#unwind) global scope with `\undefined-result`

## `-` <a id="subtract"/>

```
(- x:Number ...:Number): Number
```

A [function](#function) that subtracts one or more [numbers](#number).

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *No arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *Argument isn't a prototype of nor a number:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *Subtracting infinity from infinity:* [unwinds](#unwind) global scope with `\undefined-result`

## `*` <a id="multiply"/>

```
(* multiplicand:Number multiplier:Number ...:Number): Number
```

A [function](#function) that multiplies two or more [numbers](#number).

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Less than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *Argument isn't a prototype of nor a number:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *Multiplying zero and infinity:* [unwinds](#unwind) global scope with `\undefined-result`

## `/` <a id="divide"/>

```
(/ dividend:Number divisor:Number ...:Number): Number
```

A [function](#function) that divides two or more [numbers](#number).

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Less than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *Argument isn't a prototype of nor a number:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *Dividing by zero or infinity by infinity:* [unwinds](#unwind) global scope with `\undefined-result`

### Examples

```
(/ 12 3)
# 4

(/ 1 3)
# 0.(3)
```

## `bindings`

```
bindings: Map
```

Bindings currently in scope, which is a [map](#map) that associates [symbols](#symbol) to values.

The bindings map always [prototypically](#prototype) inherits from the previous bindings map in scope, or none if it's at the [module](#module) (or global) scope. Each [function](#function) call creates a new bindings map that prototypically inherits from the previous one, and this always points to the one currently in scope.

## `count`

```
(count map:Map): Number
```

A [function](#function) that returns the number of key/value pairs in a `map`. If `map` is a prototype of or a [built-in](#built-in) [function](#function) then it returns `0`.

### Complexity

- Time: `O(1)`
- Space: `O(1)`

### Conditions

- *Less or more than one argument:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`map` argument isn't a prototype of nor a map:* [unwinds](#unwind) global scope with `\prototype-mismatch`

### Examples

```
(count {})
# 0

(count {:})
# 0

(count {\name: 'Bob'})
# 1

(count [\x \y])
# 2

(count {\x \y \y})
# 2

(count 'Bob')
# 3

(count \())
# 0

(count \xyz)
# 3
```

## `defer`

```
(defer expression:Any): Any
(defer expression:Any escape:Symbol): Any
```

A [function](#function) that creates a snapshot of an `expression` thereby preventing it from being evaluated, optionally with an `escape` [symbol](#symbol) for re-enabling [evaluation](#evaluate) inside it.

### Complexity

- Time: `O(1+k)` where `k` is the number of `escape` calls
- Space: `O(1)`

### Conditions

- *Zero or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`escape` argument isn't a prototype of nor a symbol:* [unwinds](#unwind) global scope with `\prototype-mismatch`

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
(evaluate expression:Any)
(evaluate expression:Any bindings:Map): Any
```

A [function](#function) that evaluates an `expression` and returns the result, optionally using different `bindings`.

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Zero or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`bindings` argument isn't a prototype of nor a map:* [unwinds](#unwind) global scope with `\prototype-mismatch`

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

  (evaluate \y bindings))
  # 2
```

## `get`

```
(get map:Map key:Any): Any
(get map:Map key:Any default:Any): Any
```

A [function](#function) that retrieves the value associated with a `key` in a `map`, optionally using a lazily evaluated `default` value if no such association exists.

### Complexity

- Time: `O(1)`
- Space: `O(1)`

### Conditions

- *Less than two or more than three arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`map` argument isn't a prototype of nor a map:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *Association doesn't exist and a `default` value isn't provided:* [unwinds](#unwind) global scope with `\unknown-key`

### Examples

```
(get [8 2 2] 1)
# 8

(get {'a' 'b'} 'b')
# 'b'

(get \(+ 6 7) 2)
# 6

(get 'Bob' 3)
# 98

(get \Bob 3)
# 98

(get {:} \age 20)
# 20

(get {\age: 30} \age 20)
# 30

(let user: {\name: 'Bob'}
     users: [user]

  (get user \name)
  # 'Bob'

  user::name
  # 'Bob'

  users::1::name)
  # 'Bob'
```

## `infinity`

```
infinity: Number
```

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
(insert set:Set value:Any): Set
```

A [function](#function) that adds a `value` to a `set`, and returns the new [set](#set). If `value` is already present, then `set` is returned unchanged.

```
(insert list:List value:Any): List
(insert function:Function value:Any): Function
```

A [function](#function) that associates a `value` with the next highest positive integer key in a `list` or `function`, and returns the new [list](#list) or [function](#function) respectively.

```
(insert map:Map key:Any value:Any): Map
```

A [function](#function) that associates a `key` with a `value` in a `map`, and returns the new [map](#map). If `key` already exists, then its associated value becomes `value`.

```
(insert list:List key:Number value:Any): List
(insert function:Function key:Any value:Any): Function
```

A [function](#function) that associates a `key` with a `value` in a `list` or `function`, and returns the new [list](#list) or [function](#function) respectively. If `key` already exists and isn't a positive integer, then its associated value becomes `value`. If `key` already exists and is a positive integer, then it displaces instead the existing key and all following integer keys, if any, incrementing each by one.

### Conditions

- *Less than two or more than three arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`map` argument isn't a prototype of nor a map:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *`map` argument is a prototype of or a set and `key` isn't equal to `value`:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`set` argument isn't a prototype of nor a set:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *`list` argument is a prototype of or a list and `key` isn't a positive integer less than or equal to its length plus one:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`function` argument is a prototype of or a function and when `key` is a number it isn't a positive integer less than or equal to its highest positive integer key plus one:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`function` argument is a prototype of or a function and `value` isn't a prototype of or a function when inserting it into the first position:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`function` argument is a prototype of or a built-in function:* [unwinds](#unwind) global scope with `\prototype-mismatch`

### Examples

```
(insert [8] 1 9)
# [9 8]

(insert [8] 9)
# [8 9]

(insert ['x' 'y'] 3 'z')
# ['x' 'y' 'z']

(insert {1 2} 3)
# {1 2 3}

(insert 'Bo' 98)
# 'Bob'

(insert 'ob' 1 66)
# 'Bob'

(insert {:} \name 'Bob')
# {name: 'Bob'}

(insert {\name: 'Bob'} \name 'John')
# {name: 'John'}

(insert \x (get 'y' 1))
# xy
```

## `load`

```
(load path:List ...:Any): Any
```

A [function](#function) that loads a [module](#module) by `path`, with zero or more arguments, and returns the value from the last evaluated expression. A `path` is a list of zero or more names, ending with the [module](#module) name.

### Complexity

- Time: `O(1)`
- Space: `O(n)`

### Conditions

- *Less than one argument:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`path` argument isn't a prototype of nor a non-empty list of symbols:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *Module can't be found:* [unwinds](#unwind) global scope with `\unknown-module`
- *Module doesn't evaluate to at least one value:* [unwinds](#unwind) global scope with `\undefined-result`

### Examples

```
(load [\io])
```

## `local`

```
(local map:Map): Map
```

A [function](#function) that returns a [map](#map) with the non-inherited key/value pairs from a [prototyped](#prototype) `map`.

### Complexity

- Time: `O(1)`
- Space: `O(1)`

### Conditions

- *Less or more than one argument:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`map` argument isn't a prototype of nor a map:* [unwinds](#unwind) global scope with `\prototype-mismatch`

### Examples

```
(let x: 1
  (let y: 2

    (local bindings)
    # {y: 2}

    (local (prototype bindings))))
    # {x: 1}
```

## `next`

```
(next map:Map): Any
(next map:Map key:Any): Any
```

A [function](#function) that returns the first key or the key following `key` in a `map`.

### Complexity

- Time: `O(1)`
- Space: `O(1)`

### Conditions

- *Zero or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`map` argument isn't a prototype of nor a map:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *`map` is empty or `key` is the last key:* [unwinds](#unwind) global scope with `\unknown-key`

### Examples

```
(next [\x \y \z])
# 1

(next [\x \y \z] 2)
# 3

(next {\name: 'Bob' \age: 20})
# name
```

## `prototype`

```
(prototype value:Any): Any
```

A [function](#function) that retrieves the [prototype](#prototypes) of `value`.

```
(prototype value:Any base:Any): Any
```

A [function](#function) that extends the prototype hierarchy using `base` thereby creating a new [prototype](#prototypes).

### Complexity

- Time: `O(1)`
- Space: `O(1)`

### Conditions

- *Zero or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`value` and `base-prototype` don't share a common ancestor prototype:* [unwinds](#unwind) global scope with `\prototype-mismatch`

### Examples

```
(prototype 'Bob')
# ''

(prototype '')
# []

(let Person: (prototype {\name: ''} {:})
     bob: (insert Person \name 'Bob')

  Person
  # {name: ''}

  (prototype Person)
  # {:}

  bob
  # {name: 'Bob'}
  
  (prototype bob)
  # Person

  (prototype (prototype bob)))
  # {:}
```

## `remove`

```
(remove map:Map key:Any): Map
```

A [function](#function) that disassociates a `key` from a value in a `map`, and returns the new [map](#map). If `key` isn't present, then `map` is returned unchanged.

```
(remove list:List key:Number): List
(remove function:Function key:Any): Function
```

A [function](#function) that disassociates a `key` from a value in a `list` or `function`, and returns the new [list](#list) or [function](#function) respectively. If `key` isn't present, then `list` or `function` is returned unchanged. If `key` is present and is a positive integer, then it displaces instead all following integer keys, if any, decrementing each by one.

### Complexity

Map:

- Time: `O(1)`
- Space: `O(1)`

Set:

- Time: `O(1)`
- Space: `O(1)`

List:

- Time: `O(n)`
- Space: `O(1)`

Function:

- Time: `O(n)` for number keys, otherwise `O(1)`
- Space: `O(1)`

### Conditions

- *Less or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`map` argument isn't a prototype of nor a map:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *`list` argument is a prototype of or a list and `key` isn't a positive integer:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`function` argument is a prototype of or a function and when `key` is a number it isn't a positive integer:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`function` argument is a prototype of or a non-empty function and `key` is `1`:* [unwinds](#unwind) global scope with `\parameter-mismatch`

### Examples

```
(remove [7 8 9] 2)
# [7 9]

(remove ['x' 'y'] 3)
# ['x' 'y']

(remove {'x' 'y'} 'y')
# {'x'}

(remove 'Bob' 2)
# 'Bb'

(remove {\name: 'Bob' \age: 20} \age)
# {name: 'Bob'}

(remove {\name: 'Bob'} \age)
# {name: 'Bob'}
```

## `unwind`

```
(unwind value:Any): Any
(unwind value:Any bindings:Map): Any
```

A [function](#function) that aborts the current scope or the scope associated with the given `bindings`, and returns `value` as the result.

Unwinding is a non-local early exit of a given scope. Unwinding the [module](#module) (or global) scope exits the currently executing module.

### Complexity

- Time: `O(1)`
- Space: `O(1)`

### Conditions

- *Zero or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`bindings` argument isn't a prototype of nor a bindings map:* [unwinds](#unwind) global scope with `\prototype-mismatch`

### Examples

```
(let x: 1

  (let y: 2
    y)
  # 2

  (let y: 2
    (unwind 3)
    y)
  # 3

  (let y: 2
    (unwind 3 (prototype bindings))
    y)

  x)
# 3  
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
Number ::= Sign? Digit+ ("." <U+2E> (Digits | Digits? Function-Begin Digits Function-End))? Symbol?
Sign ::= "+" <U+2B> | "-" <U+2D>
Digits ::= Digit+ (Text-Quote? Digit+)*
Digit ::= "0" <U+30> | "1" <U+31> | "2" <U+32> | "3" <U+33> | "4" <U+34> | "5" <U+35> | "6" <U+36> | "7" <U+37> | "8" <U+38> | "9" <U+39>
```

Symbol:

```
Symbol ::= not(Reserved-Character, White-Space, Sign, Digit) not(Reserved-Character, White-Space)* | Sign (not(Reserved-Character, White-Space, Digit) not(Reserved-Character, White-Space)*)?
Reserved-Character ::= List-Begin | List-End | Function-Begin | Function-End | Map-Begin | Map-End | Comment-Quote | Text-Quote | Defer | Pair-Separator
```

Text:

```
Text ::= Symbol? Text-Quote (not(Text-Quote) | Text-Quote{2})* Text-Quote
Text-Quote ::= "'" <U+22>
```

Map:

```
Map ::= Map-Empty | Map-Begin White-Space* Pair (White-Space+ Pair)* White-Space* Map-End
Map-Empty ::= Map-Begin Pair-Separator Map-End
Pair ::= Expression Pair-Separator White-Space* Expression
Pair-Separator ::= ":" <U+3A>
Map-Begin ::= "{" <U+7B>
Map-End ::= "}" <U+7D>
```

List:

```
List ::= List-Begin White-Space* (Expression (White-Space+ Expression)* White-Space*)? List-End
List-Begin ::= "[" <U+5B>
List-End ::= "]" <U+5D>
```

Set:

```
Set ::= Map-Begin White-Space* (Expression (White-Space+ Expression)* White-Space*)? Map-End
```

Function:

```
Function ::= Function-Begin White-Space* (Function (White-Space+ Function-Value)* White-Space*)? Function-End
Function-Value ::= Expression | Pair
Get-Chain ::= Symbol (Pair-Separator{2} (Symbol | Number))+
Function-Begin ::= "(" <U+28>
Function-End ::= ")" <U+28>
```

## Transformations

These are the syntactic transformations that occur for each associated non-terminal. Each letter represents a matching element of a grammar production.

|Non-Terminal       |Syntax|Transformation|Example       |Notes         |
|-------------------|------|--------------|--------------|--------------|
|*Get-Chain*        |`x::y`|`(get x \y)`  |`user::name`  |Left to right.|
|*Text*             |`xy`  |`(x y)`       |`hex'1F'`     |              |
|*Function-Value*   |`x`   |`N:x`         |`(f)`         |Position `N`. |
|*Number*           |`xy`  |`(y x)`       |`2Km`         |              |
|*Defer*            |`\x`  |`(defer x)`   |`\length`     |              |

# Coding Style

The human language used should be English.

## Documentation

Documentation should be written in [CommonMark](http://commonmark.org) format. Avoid verbs that are also nouns to prevent ambiguity.

## Naming

All names should use hyphens as the word delimiter.

### Function

The name of a [function](#function) should generally use a verb as the first word. Predicate functions should end in `?`. Mutator functions should end in `!`. Accessor functions should start with a noun instead of a verb and end in `-of`.

### Module

The name of a [module](#module) should be a noun, in lower-case.

### Prototype

The name of a [prototype](#prototype) should be a noun, capitalized.
