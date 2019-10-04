# Table of Contents

- [Introduction](#introduction)
  - [Goals](#goals)
  - [Inspiration](#inspiration)
- [Coding Style](#coding-style)
  - [Documentation](#documentation)
  - [Naming](#naming)
- [Structure](#structure)
  - [Syntax](#syntax)
  - [Module](#module)
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
  - [`=` (equal)](#-equal)
  - [`<` (less than)](#-less-than)
  - [`>` (greater than)](#-greater-than)
  - [`+` (add)](#-add)
  - [`-` (subtract)](#-subtract)
  - [`*` (multiply)](#-multiply)
  - [`/` (divide)](#-divide)
  - [`bindings`](#bindings)
  - [`count`](#count)
  - [`defer`](#defer)
  - [`do`](#do)
  - [`evaluate`](#evaluate)
  - [`get`](#get)
  - [`insert`](#insert)
  - [`load`](#load)
  - [`local`](#local)
  - [`next`](#next)
  - [`prototype`](#prototype)
  - [`remove`](#remove)
  - [`unwind`](#unwind)
- [Grammar](#grammar)
  - [Transformations](#transformations)

# Introduction

A single open language for interactive use, scripting, and building small to large programs, that aims to be simple, powerful, and practical.

## Goals

Simple:

- Minimal syntax, but readable.
- Fun to use.
- Prototype-based object model.
- Flat over nested, helpers over wrappers.
- No undefined behavior, consistent, uniform.
- Everything is a value, never null.
- Right things easier than wrong things, encouraged, and the only way.
- Immutable data structures, no defensive copying.
- Principle of Least Surprise: *"The design should match the user's experience, expectations, and mental models."*
- *"Keep the language spec simple enough to hold in a programmer's head."*

Powerful:

- Homoiconic, code as data.
- No arbitrary limits: *"Zero-one-infinity rule."*
- Unified methods and functions via multiple dispatch.
- Controlled argument evaluation via fexprs.
- High-level: *"A programming language is low level when its programs require attention to the irrelevant."*
- Documentation available at run-time.
- Embeddable.

Practical:

- Unified REPL and command-line interpreter.
- Shell scripting (`#!`, hash-bang syntax naturally supported).
- Fast enough (zero-copy; quick feedback, low latency; maximum resource usage when appropriate).
- Easy data type literals: lists, maps, sets, functions, text (strings), numbers.
- Multi-platform: *"Write once, run everywhere."*
- Native code interoperability (FFI, Foreign Function Interface).
- Permissive license.
- Low cognitive load and typing effort (US QWERTY keyboard layout, favor home row keys).
- Standard tooling: single-style source code formatter/linter, testing framework, profiler, local/remote debugger, package manager, command-line documentation viewer.

## Inspiration

- Lisp
- Python
- Unix shell
- JavaScript
- Perl

# Coding Style

English is the official language used throughout code and documentation.

Line length should be 80 characters maximum, since going over that limit can often indicate it needs to be refactored for readability.

## Documentation

Documentation is written in the [CommonMark](http://commonmark.org) format. In general, verbs that are also nouns are avoided to prevent ambiguity.

## Naming

All names use hyphens as the word delimiter.

- **Function:** verb as the first word; predicate functions end in `?`, while accessor functions start with a noun instead and end in `-of`.
- **Module**: noun, in lower-case.
- **Prototype:** noun, capitalized.

# Structure

## Syntax

Source code is represented as s-expressions with significant indentation. This follows a simple set of rules:

1. A [Function](#function) call enclosed in parenthesis, as well as a literal [map](#map), [list](#list), and [set](#set), disables significant indentation inside the entire [expression](#grammar).
2. Otherwise, each line is an implicit [function](#function) call.
  - Same-line arguments are passed as-is.
  - Indented lines that follow it are passed as function calls, as described above recursively.

Note that all [non-function data types are callable](#prototypes) as functions, and return the same value itself.

Refer to the [grammar](#grammar) for the precise definition.

## Module

A module is a [named](#symbol) implicit [function](#function) call to [`do`](#do), represented as Unicode text encoded in UTF-8 without a Byte Order Mark.

Note that since `do` accepts multiple arguments then a module can also have multiple expressions, and the result of calling it is the result returned by the last expression.

# Prototypes

A [prototype](#prototype) is the original value used to create another one from.

Not all values can be literally represented in source code, since not all have an associated [grammar](#grammar) production. They can however be assigned names, by using [symbols](#symbol) stored in the [bindings](#bindings) map.

All data types are callable as zero-parameter functions that return the same value itself, except for [functions](#function) that are handled as regular function calls.

## Boolean

A boolean is a binary logical value that can only be either true or false. It does not have a literal source code representation.

- **Prototype:** true
- **Base Prototype:** (itself)

### Conditions

- *Called with one or more arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`

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

A function is an immutable sequence composed of a function (body) followed by zero or more values as the arguments. This sequence associates consecutive positive integer keys in ascending order with positional arguments, including any keyword arguments as well.

Calling a function creates a new [bindings](#bindings) map from the [deferred](#defer) function call itself, [prototypically](#prototype) inherited from the current bindings in scope, and then [evaluates](#evaluate) the function body using the new bindings returning the result. Calling an empty function returns itself.

Tail calls are guaranteed to be efficient and use a similar amount of memory as an iterative loop. A tail call is a self-recursive function call when it calls itself, a tail function call when it's the last expression in the calling function, or a self-tail function call when it calls itself as the last expression.

- **Prototype:** empty [function](#function), `()`
- **Base Prototype:** empty [map](#map), `{:}`

### Conditions

- *Empty function called with one or more arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`

### Examples

```
()
# ()

(* 4 5)
# 20

(* multiplicand: 4 multiplier: 5)
# 20

\()
# ()

\(* 4 5)
# (* 4 5)

(\(* 4 5))
# 20

(prototype -)
# ()

(prototype prototype)
# ()

(prototype \(* 4 5))
# ()

(prototype ())
# {:}
```

## List

A list is an immutable sequence of elements, that associates consecutive positive integer keys in ascending order with values.

- **Prototype:** empty [list](#list), `[]`
- **Base Prototype:** empty [map](#map), `{:}`

### Conditions

- *Called with one or more arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`

### Examples

```
[]
# []

['x' 'y']
# ['x' 'y']

[8 2 2 \abc]
# [8 2 2 abc]

(prototype ['x'])
# []

(prototype [])
# {:}
```

## Map

A map is an immutable insertion ordered collection, that associates unique keys with values.

If the same key appears multiple times, the last associated value takes precedence over all previous ones.

- **Prototype:** empty [map](#map), `{:}`
- **Base Prototype:** (itself)

### Conditions

- *Called with one or more arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`

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
- **Base Prototype:** (itself)

### Conditions

- *Called with one or more arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`

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

4,294,967,296
# 4,294,967,296

(/ 1 0.(0)1)
# infinity

3Km
# (Km 3)

(prototype 3)
# 0

(prototype 0)
# 0
```

## Set

A set is an immutable collection of unique elements, that associates keys to be the same as values.

- **Prototype:** empty [set](#set), `{}`
- **Base Prototype:** empty [map](#map), `{:}`

### Conditions

- *Called with one or more arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`

### Examples

```
{}
# {}

{'x' 'y'}
# {'x' 'y'}

{8 2 2 \abc}
# {8 2 abc}

(prototype {'x'})
# {}

(prototype {})
# {:}
```

## Symbol

A symbol is an immutable case-sensitive name, that restricts the character set used according to the [grammar](#grammar). The empty symbol does not have a literal source code representation.

- **Prototype:** empty symbol
- **Base Prototype:** empty [text](#text), `''`

### Conditions

- *Called with one or more arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`

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

A text is an immutable sequence of Unicode characters, each one identified by a numeric code-point. Also known as a string.

- **Prototype:** empty [text](#text), `''`
- **Base Prototype:** empty [list](#list), `[]`

### Conditions

- *Called with one or more arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`

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

re'\d+'g
# (re '\d+' \g)

(prototype 'Bob')
# ''

(prototype '')
# []
```

# Built-ins

## `=` (equal)

```
(= x y ...): Boolean
```

A [function](#function) that compares two or more values (with short-circuit evaluation) and returns true if they are all equal, or false otherwise.

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Called with less than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`

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

## `<` (less than)

```
(< x:Number y:Number ...:Number): Boolean
```

A [function](#function) that compares two or more [numbers](#number) (with short-circuit evaluation) and returns true if each one is less than the next, or false otherwise.

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Called with less than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *Argument isn't a prototype of nor a number:* [unwinds](#unwind) global scope with `\prototype-mismatch`

## `>` (greater than)

```
(> x:Number y:Number ...:Number): Boolean
```

A [function](#function) that compares two or more [numbers](#number) (with short-circuit evaluation) and returns true if each one is greater than the next, or false otherwise.

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Called with less than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *Argument isn't a prototype of nor a number:* [unwinds](#unwind) global scope with `\prototype-mismatch`

## `+` (add)

```
(+ x:Number ...:Number): Number
```

A [function](#function) that adds one or more [numbers](#number).

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Called with no arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *Argument isn't a prototype of nor a number:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *Adding negative and positive infinity:* [unwinds](#unwind) global scope with `\undefined-result`

## `-` (subtract)

```
(- x:Number ...:Number): Number
```

A [function](#function) that subtracts one or more [numbers](#number).

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Called with no arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *Argument isn't a prototype of nor a number:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *Subtracting infinity from infinity:* [unwinds](#unwind) global scope with `\undefined-result`

## `*` (multiply)

```
(* multiplicand:Number multiplier:Number ...:Number): Number
```

A [function](#function) that multiplies two or more [numbers](#number).

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Called with less than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *Argument isn't a prototype of nor a number:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *Multiplying zero and infinity:* [unwinds](#unwind) global scope with `\undefined-result`

## `/` (divide)

```
(/ dividend:Number divisor:Number ...:Number): Number
```

A [function](#function) that divides two or more [numbers](#number).

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Called with less than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
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

A [function](#function) that returns the number of key/value pairs in a `map`. If `map` is a prototype of, or a [built-in](#built-in) or [foreign-loaded](#load) [function](#function) then it returns `0`.

### Complexity

- Time: `O(1)`
- Space: `O(1)`

### Conditions

- *Called with less or more than one argument:* [unwinds](#unwind) global scope with `\parameter-mismatch`
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

(count +)
# 0

(count \())
# 0

(count \xyz)
# 3
```

## `defer`

```
(defer expression)
(defer expression escape:Symbol)
```

A [function](#function) that creates a snapshot of an `expression` thereby preventing it from being [evaluated](#evaluate), optionally with an `escape` [symbol](#symbol) for re-enabling evaluation inside it.

### Complexity

- Time: `O(1+k)` where `k` is the number of `escape` calls
- Space: `O(1)`

### Conditions

- *Called with zero or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
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

## `do`

```
(do expression ...)
```

A [function](#function) that evaluates a sequence of expressions and returns the value of the last expression.

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Called with zero arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`

### Examples

```
(do 'abc')
# 'abc'

(do (* 4 5))
# 20

(do (* 4 5) (+ 8 2))
# 10
```

## `evaluate`

```
(evaluate expression)
(evaluate expression bindings:Map)
```

A [function](#function) that evaluates an `expression` and returns the result, optionally using different `bindings`.

### Complexity

- Time: `O(n)`
- Space: `O(1)`

### Conditions

- *Called with zero or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`bindings` argument isn't a prototype of nor a map:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *`expression` argument contains an unbound identifier:* [unwinds](#unwind) global scope with `\unbound-identifier`
- *`expression` argument contains a function call to a non-function value:* [unwinds](#unwind) global scope with `\prototype-mismatch`

### Examples

```
(evaluate 'Bob')
# 'Bob'

(let x: \(+ 8 2)

  x
  # (+ 8 2)

  (x)
  # 10

  (evaluate x)
  # 10

  (evaluate \x)
  # (+ 8 2)

  (evaluate \(x)))
  # 10

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
(get map:Map key)
(get map:Map key default)
```

A [function](#function) that retrieves the value associated with a `key` in a `map`, optionally using a lazily [evaluated](#evaluate) `default` value if no such association exists.

Key lookup takes place in the given map, and in each of its base prototypes until it's found, if it exists.

### Complexity

- Time: `O(1)`
- Space: `O(1)`

### Conditions

- *Called with less than two or more than three arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
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

  users::1::name
  # 'Bob')
```

## `insert`

```
(insert set:Set value): Set
```

A [function](#function) that adds a `value` to a `set`, and returns the new [set](#set). If `value` is already present, then `set` is returned unchanged.

```
(insert list:List value): List
(insert function:Function value): Function
```

A [function](#function) that associates a `value` with the next highest positive integer key in a `list` or `function`, and returns the new [list](#list) or [function](#function) respectively.

```
(insert map:Map key value): Map
```

A [function](#function) that associates a `key` with a `value` in a `map`, and returns the new [map](#map). If `key` already exists, then its associated value becomes `value`.

```
(insert list:List key:Number value): List
(insert function:Function key value): Function
```

A [function](#function) that associates a `key` with a `value` in a `list` or `function`, and returns the new [list](#list) or [function](#function) respectively. If `key` already exists and isn't a positive integer, then its associated value becomes `value`. If `key` already exists and is a positive integer, then it displaces instead the existing key and all following integer keys, if any, incrementing each by one.

### Complexity

Map:

- Time: `O(1)`
- Space: `O(1)`

Set:

- Time: `O(1)`
- Space: `O(1)`

List / Function:

- Time: `O(n)` for number keys, otherwise `O(1)`
- Space: `O(1)`

### Conditions

- *Called with less than two or more than three arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`map` argument isn't a prototype of nor a map:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *`map` argument is a prototype of or a set and `key` isn't equal to `value`:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`set` argument isn't a prototype of nor a set:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *`list` argument is a prototype of or a list and `key` isn't a positive integer less than or equal to its length plus one:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`function` argument is a prototype of or a function and when `key` is a number it isn't a positive integer less than or equal to its highest positive integer key plus one:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`function` argument is a prototype of or a built-in or foreign function:* [unwinds](#unwind) global scope with `\prototype-mismatch`

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
(load path:List)
```

A [function](#function) that loads a [module](#module) by `path`, and returns the value of the single [expression](#grammar) contained within. No other evaluation is done. A `path` is a list of zero or more names, ending with the [module](#module) name.

### Complexity

- Time: `O(n)`
- Space: `O(n)`

### Conditions

- *Called with less than one argument:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`path` argument isn't a prototype of nor a non-empty list of symbols:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *Module can't be found:* [unwinds](#unwind) global scope with `\unknown-module`
- *Module is invalid:* [unwinds](#unwind) global scope with `\undefined-result`

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

- *Called with less or more than one argument:* [unwinds](#unwind) global scope with `\parameter-mismatch`
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
(next map:Map)
(next map:Map key)
```

A [function](#function) that returns the first key or the key following `key` in a `map`.

### Complexity

- Time: `O(1)`
- Space: `O(1)`

### Conditions

- *Called with zero or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
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
(prototype value)
```

A [function](#function) that retrieves the [prototype](#prototypes) of `value`.

```
(prototype value base)
```

A [function](#function) that extends the prototype hierarchy using `base` thereby creating a new [prototype](#prototypes).

### Complexity

- Time: `O(1)`
- Space: `O(1)`

### Conditions

- *Called with zero or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
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
(remove map:Map key): Map
```

A [function](#function) that disassociates a `key` from a value in a `map`, and returns the new [map](#map). If `key` isn't present, then `map` is returned unchanged.

Key lookup takes place in the given map, and in each of its base prototypes until it's found, if it exists.

```
(remove list:List key:Number): List
(remove function:Function key): Function
```

A [function](#function) that disassociates a `key` from a value in a `list` or `function`, and returns the new [list](#list) or [function](#function) respectively. If `key` isn't present, then `list` or `function` is returned unchanged. If `key` is present and is a positive integer, then it displaces instead all following integer keys, if any, decrementing each by one.

Key lookup takes place in the given list or function, and in each of its base prototypes until it's found, if it exists.

### Complexity

Map:

- Time: `O(1)`
- Space: `O(1)`

Set:

- Time: `O(1)`
- Space: `O(1)`

List / Function:

- Time: `O(n)` for number keys, otherwise `O(1)`
- Space: `O(1)`

### Conditions

- *Called with less or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`map` argument isn't a prototype of nor a map:* [unwinds](#unwind) global scope with `\prototype-mismatch`
- *`list` argument is a prototype of or a list and `key` isn't a positive integer:* [unwinds](#unwind) global scope with `\parameter-mismatch`
- *`function` argument is a prototype of or a function and when `key` is a number it isn't a positive integer:* [unwinds](#unwind) global scope with `\parameter-mismatch`

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
(unwind value)
(unwind value bindings:Map)
```

A [function](#function) that aborts the current scope or the scope associated with the given `bindings`, and returns `value` as the result.

Unwinding is a non-local early exit of a given scope. Unwinding the [module](#module) (or global) scope exits the currently executing module.

### Complexity

- Time: `O(1)`
- Space: `O(1)`

### Conditions

- *Called with zero or more than two arguments:* [unwinds](#unwind) global scope with `\parameter-mismatch`
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
Expression ::= White-Space* Defer* (Number | Symbol | Text | Map | Set | List | Function) White-Space*
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
Digits ::= Digit+ ("," <U+2C>? Digit+)*
Digit ::= "0" <U+30> | "1" <U+31> | "2" <U+32> | "3" <U+33> | "4" <U+34> | "5" <U+35> | "6" <U+36> | "7" <U+37> | "8" <U+38> | "9" <U+39>
```

Symbol:

```
Symbol ::= not(Reserved-Character, White-Space, Sign, Digit) not(Reserved-Character, White-Space)*
Reserved-Character ::= List-Begin | List-End | Function-Begin | Function-End | Map-Begin | Map-End | Comment-Quote | Text-Quote | Defer | Pair-Separator
```

Text:

```
Text ::= Simple-Text | Tagged-Text
Simple-Text ::= Text-Quote (not(Text-Quote) | Text-Quote{2})* Text-Quote
Tagged-Text ::= Symbol Simple-Text Symbol?
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
Function ::= (Function-Begin White-Space* (Function-Value (White-Space+ Function-Value)* White-Space*)? Function-End) | Get-Chain
Get-Chain ::= Symbol (Pair-Separator{2} (Symbol | Number))+
Function-Value ::= Expression | Pair
Function-Begin ::= "(" <U+28>
Function-End ::= ")" <U+28>
```

## Transformations

These are the syntactic transformations that occur for each associated non-terminal. Each letter represents a matching element of a grammar production.

|Non-Terminal       |Syntax|Transformation|Example       |Notes         |
|-------------------|------|--------------|--------------|--------------|
|*Get-Chain*        |`x::y`|`(get x \y)`  |`user::name`  |Left to right.|
|*Tagged-Text*      |`xyz` |`(x y z)`     |`base'1F'16`  |              |
|*Function-Value*   |`x`   |`N:x`         |`(f)`         |Position `N`. |
|*Number*           |`xy`  |`(y x)`       |`2Km`         |              |
|*Defer*            |`\x`  |`(defer x)`   |`\length`     |              |
