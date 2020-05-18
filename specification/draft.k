# spec example of lexical binding
# and naming fns, \(incr: + x 1)

# are triple quotes needed?
# are alternative quotes needed?

# quote quasi-quote unquote?
`symbol
`(,fn)

# make list extend fn?
# to easily merge arg lists into fns?

# Maybe/Option instead of exceptions?

# macros instead of fexprs?
# - allows early returns
# - could replace exceptions
# - potentially more performant

---

# Pipeline support? shell pipe?

# goals:
# - minimum syntax, where possible
# - concise, easy to type, familiar

# rules:
# - follows shell syntax closely
# - each pipe part is partial fn call
# - parens are replaced by pipes
# - can still have args
# - pipeline will invoke all fns
# - may be sequential or parallel
# - fn return value is output
# - last param is input
# - currying to fix/rearrange params

# original form
(print (count re'\d' (split val)))

# just pass input as last arg?
# too implicit?
# problem is it can break easily?
# use a pre-determined keyword arg?
# it'd be the same as orig form?
split val | count re'\d' | print

# or currying indicates input param?
# too verbose?
# used only to rearrange params?
# or to fix params?
# force fn exprs for safety?
# force keyword params same as orig
split val | count re'\d' txt: | print

# file I/O (more verbose, but clear)
date | file 'blah'

date :: file 'blah'

# pipeline quoted as fn call?
# no new syntax, optional parens
\(date | file 'blah')

---

# `:` less syntax, "prettier", no w/s

# (constraint value key value)
# creates new constraint

# (constraint value)
# gets constraint

# how constraint heterogeneous value?
(constraint {:} shape: {\name: ''})

[] # NaturalNumber: Any
{} # Any: Any
'' #
Symbol #

# avoid word proto/prototype in spec?

# dynamic binding by default?
# - code is just code
# dynamic typing by default?
# - can force static, eg. (List val)

# fn as value constraint
# prob more flexible and less syntax
# splice = insert + merge + delete
# no need for Any as Map is the root?
# Number is Map/List of digit Symbols
Map: (splice {:} map:)
Text: (splice '' map:) 
List: (splice [] map:)

# value inference, default
# can be used on both keys and values
name: 'Bob'

# value assertion, explicit
name: Text 'Bob'

# value up-cast, safe
chars: List 'Bob'

...

# homogenous type
Numbers: \(splice [0] map: | unshift)
[0]

# heterogeneous type
Set: (splice {} map:)
[]
[0 'a']

# type is a value/fn ctor?
# Python class name is type and ctor

Person: {\name: ''}
bob: (set Person \name 'Bob')
bob: Person \name: 'Bob'

Person: (proto {\name: ''} ctor-fn)

Names: []
friends: Names 'Bob'

# [] is both value and ctor
# when used as ctor creates new proto

# spec has type syntax in fn headers
# should follow the same or change
# implemented in the stdlib?

# - as shell "call" values = values
# - nicer to converge () [] {} ?
#   - fn is a list that gets eval?
#   - make list and fn share a proto?
# - no extra syntax for static types
# - type generics
# - type inference
# - up/down type cast
# - dynamic typing
# - new types (flexibility of impl)

# type down-cast (unsafe)
# - type system would complain?
# - must use separate fn to convert?
text: Text [65]

# dynamic typing, via args
\(
  (if (= (proto scope.arg) [])
    then: (io.print
      'list' (count scope.arg))
    else: (io.print 'non list')))

# static typing, via args
\(+ 1 scope.arg)

# generics
...

# disable static typing from value
...

# get type/ctor/? of a value
proto value

# new constraint/ctor/type
Names: ...

Person: (proto {:} {\name: ''})
bob: Person \name: 'Bob'

value: (proto bob)
value \name: 123

Names ['Bob']

# what’s List? And Text?
# - weird to be values? ([] 'Bob')
# - too implicit?
# - not always very readable
# - merge becomes "built-in"
# - prior art for concatenation?
# - hard to denote generics?
# - not all values can be concat?
'x' 'y' # = 'xy'
[1] [2] # = [1 2]
1 2 # = 3
chars: [] 'Bob'
function: () +
countdown [1]

# fns have implicit bindings?
# lexical scope by default?
\(+ x 1)
(: + x 1)
(x: . + x 1)
(x :: + x 1)
(x: : + x 1)
\(+ x 1 scope:)

[x | + x 1]

# avoid the word "type" in the spec?
# - less syntax, frees up `.` and `=`
# - still easy to read

---

# constraint fn? Or struct compat?
# consistent with how `proto` works?
# why stop at types for validation?
# because can be made compile time?

# there are already constraints
# symbol has constraints
# text has constraints
# having a built-in only exposes them

# not necessarily 
# could be impl within builtin fns

# define new constraint
# - what about booleans and numbers?
# - allow arbitrary fns?
#   - could allow too much logic?
#   - number tower doesn’t need fns?

(constraint base key value)
(constraint base key value formula)

# retrieve constraint

(constraint value)

# built in types

(constraint []) # (() Natural Any)
(constraint ()) # ({:} Any Any)
(constraint {}) #

# List of Numbers

Numbers: (constraint [] Number?)
Numbers: (constraint [] Number)
Countdown: (constraint 3 \(- 1))

# syntax sugar?
# Math like for familiarity?

Numbers: [n | Number?]

# not proto value or type hierarchy:
# value hierarchy from constraints

(constraint {})
# any type, unrestricted, same as map
# `=` so that key equals value

# checks if values are struct compat
# ML pattern matching?
# no need to inspect types
(proto base value ...)

if (proto [] input) then:
  io.print 'list or list-like'

---

# proper interface design (?) in fns
# fns have the logic and constraints

Person: {\name: '' \age: 0}
Text!: (splice '' map:) 
set-name: (set key: \name
  map: (Text! value:))
set-name Person 'Bob'

# typeof:
# - remove all key value pairs
# - index into "type" map

(function proto (value)
  (get
    {
      []: []
      {}: {}
      (): ()
      '': ''
      {:}: {:}
      # numbers?
      # booleans?
      # empty symbol?
    }
    (splice value
      to: (count value))))

---

# cast with default
name: (cast '' 'Bob')
chars: (cast [] 'Bob')
panic: (cast 0 'Bob')
safe: (cast 0 'Bob' -1)
homogenous: (cast [] [] value: Num)

---

# more like math?
# too much syntax?
# need strike right balance between:
# simple and expressive

# set of numbers
# insertion ordered
Countdown: {3 2 1}
(Countdown 3)

Text: (proto '')

Names: {l: List t: Text
  | or (empty? l)

Text: (proto ...)
Text: (formula ...)
Text: (domain ...)
Text: {t | = (proto t) ''} # bool?

# can be used as a type/constraint
# denotes set of possible values
# if enumerable, can be iterated
# formula? pred or value gen?
...

# introspection: domain, formula
...

# function definition
# a fn is a set of values
# if it has param(s), can be called
# params are symbols by default
# lexical scope by default
incr: {x | + x 1}

# fn w/o params
talk: {| print 'Hello'}

# fn w/ default arg
greet: {name: 'human' | print name}

# how to denote code? AST?
# syntax sugar for deferred fn list
# otherwise inconsistent with \() ?
# too magic? too confusing?
...

---

# `=` is clearer and easier to type?
# `=` reserved, what about equality?
# conflate type concept with value?
# - eg. List isn’t a type, it’s `[]`
# - not types, rather constraint fns

# type inference, by default
name = 'Bob'

# types can be explicit
# "type assertion"
# uses proto for type checking
# avoid the word "type" in the spec
name = Text: 'Bob'

# explicit type can be used for cast?
chars = List: 'Bob'

# allow `:` by itself?
# it is casting the symbol key?
# or the text value?
# use it as a prefix/tag?
List: 'Bob'

# homogeneous types
# no separate syntax for empty map?
# Symbol is already a precedent
{=}
Map = (proto [])
names = List Text: ['Bob']
names = List (List Text): [['Bob']]
PhoneBook = Map Text Number: {}

# constraint builders
((Map) 123) # = false
((List Text) ['abc'] # = true

# heteregenous types
# initial keys can’t be removed
# otherwise their type would change
person = {\name = 'Bob' \age = 20}
Person = ???
alice: person = {\name = 'Alice'}

# disable type checking
value := 'Bob'
Any = (proto)
Any = (proto Map) # == (proto Number)
list: Any = []

# type introspection
(List) # List
proto name # Text
proto names # (List Text)
proto (List Text) # List
proto List # (Map PositiveInt Any)

# name/new type/proto
(PhoneBook = Map Text Number)
(Name = Text)
Names = (Names = List Text)
names = Names: ['Bob']

# more examples
# if `=` in symbols: w-spc mandatory
# not very flexible, but readable?

if (logged-in? user) then =
  do-this-first
  do-this-second

let
  name = 'Bob'
  age = Number: 20
  equal = ==
  
  io.print name age
  ip::print name age

range from = 1 to = 9

{\age = Integer: 20 \name = 'Bob'}

(== x y)

# functions
# how to specify arg order?
# vararg types?
# broken: symbols aren’t callable
# - symbols aren’t but fn lists are
# - allow [=] as fn list w/o calling?

\(incr = + x 1)
\(+ bindings.x 1)

\(incr = + Number: x 1)
(proto incr.x) # Number

# currying/piping parameters?
# what does inspecting see?

(x = y = | + x y)
Number: x Number: y | + x y
Number: x = Number: y = | + x y

# something like this?
# too needlessly complex and slow?
# just use domain+formula?

(evaluate
  \(+ x y)
  (merge bindings
    {\x = Number: arg.1
     \y = Number: arg.2}))

# ensure not ambiguous with pipes
# needed? Math-like, use for sets?
# can also be syntactic sugar
# too much syntax?

(x = | + x 1)
(Number: x = | + x 1)
(Number: x = | incr = + x 1)

(domain incr)
(formula incr)

# domain + formula = ?
# free up type "ctors"?
# harder to read?

# syntax sugar with params?
# ambiguous with keyword params?

f x = + x 1
f Text: x = append x 1

[Text:] # list of texts
{Number:} # set of numbers
{Text: = Number:} # map text to num

{Number: x = | > x 0}
(Set domain formula)

# what to do with reserving `.`?
# what about ellipsis?
# generalize what’s used for numbers?
# numbers are symbols eval themselves

x.y.x # (get (get x \y) \z)
1.2 # (get 1 \2)
1.2.3 # (get (get 1 \2) \3)
... # (Symbol Symbol Symbol)
1..2 # (1 Symbol 2)

io.print person.name
bindings.1

---

# a map is a set of pairs?

---

# values as fns to make constraints?

Number: 0
Text: ''
Map: {:}
List: []

PhoneBook: {:} Text Number
PhoneBook: Map Text Number

Names: [] Text
Names: List Text

users: Names ['Bob' 'Alice']

proto Names
>>> [] Text

# - should leave them as type casts?
#   - use merge? values aren’t types?
# - no need for more syntax
# - no need for more built ins
# - consistent as fn returning itself
# - no params = no constraints
# - can be named readability/inspect
# - ambiguous w/type conversion?
#   - not if thought as a ctor?
#   - unified type/value/ctor?
# how to query the constraints?
# how to query param types for fns?
# ambiguous to call Function?
# - not if using the empty function?
# - non-empty fns restrict empty fn
# heterogenous types?
# type inference is the default?
# type conversion/cast?
# - via `merge` builtin?
# - makes more sense than ([] value)?
# type root?
# goals/rules:
# - types = values
# - some types have enumerable values
# - type/value comes after `:`

# restricts number as a whole
# why different than lists?
# - lists have more than one param
# - each restricts different parts?
# - composite vals have multiple part
Positive: Number (>= x 0 x:)
Positive: 0 (>= x 0 x:)

Tuple: [\x \y \z] (= (count l) 2 l:)

List: []
Text: ''

Texts: (List Text)
Texts: List of: Text
Texts: ([] Text)
Texts: [] Text

Names: (Names: List Text)
let names: [] Text
Texts <> Names

(proto Texts)
>>> (List Text)

(proto List)
>>> (List: Map of: Integer)

Map: {:}

# homogenous map
PhoneBook: (Map of: Text to: Number)
PhoneBook: Map Text to: Number
PhoneBook: {:} Text to: Number
PhoneBook: {:} Text Number

# heterogenous map
Person: {\name: ''} {\name: Text}

# type cast?
name: List 'Bob'
name: [] 'Bob'
name: ['Bob'] List

# can always add and remove keys
# but removing downgrades proto?
# to disable typing use the proto?

# return type for fns?
# inspecting returns the orig call?
# - how to inspect other than `get`?
# - doesn’t work for fns?

Function: ()

incr-proto: (incr: Fn x: Num)
incr: (set incr-proto \incr \(+ x 1))

(proto incr)
>>> 

---

# streaming support? Define that
# useful for pipelines
# iterator protocol?
# for lazy values?
# `next` is an iterator?
# how to detect a value as iterator?

# generator expressions? JS yield?

---

# currying
# it’s syntax for creating functions
# can also rearrange params?

\(+ x 1 x:)

# or?

(+ x 1 x:)

# what inspecting sees
# note it shouldn't be relied on
# should it be auto evaluated?

\(\(+ x 1)
  x: (evaluate
    (get
      (get bindings)
      \x
      default: (get
        (get bindings)
        2))))

\(\(+ x 1)
  x:

# currying? too implicit?
# how to curry varargs?
let
  phonebook: {'Bob': 12345}
  lookup: (get phonebook key:)
  (lookup 'Bob')

# multiple currying?
(insert list: key:)

# renaming curried params
(\(get phonebook key: name) name:)
(lookup name: 'Bob')

# currying keys? too weird/implicit?
(get map: key: \name)
::name

person::name
::name person

unshift: \(insert key: 1 list:)

push: \(
  count
  | (+ 1 x:)
  | (insert key: bindings::1 list:)
)

\(
  (insert
    list
    key: (+ 1 (count list))
    value: value)
  list:
  value:)

---

# how easy convert map to fn list?

(merge value-1 ... value-n)
(merge \() map)

# can merge replace insert/remv/get?

# union, intersection
# changing types (down/up cast)
# allow multiple values?
# merge?

(merge map ... reducer)

# concat
(merge [1 2] [3]) # [1 2 3]

# insert
(merge [1 3] [2] reducer: 2) #[1 2 3]

# remove
(merge [1 2 3] reducer: 2) # [1 3]

(insert map ...)
(remove map ...)

# fold
# - how keyword param resolver?
# - resolver called for matches?

(fold resolver value-1 ... value-n1)

# count

# merge

# reduce

# get = intersection by key

# remove = symmetric difference

---

# make insert accept where before at?

(insert set value)
(insert list value)
(insert function value)

(insert map key value [before])
(insert list key value)
(insert function key value)

---

# Force named arguments?
if (logged-in? user)
  then: do
    this-first
    this-second
  else: do
    another-thing

if (logged-in? user)
  then:
    this-first
    this-second
  else:
    another-thing

if (logged-in? user)
  do
    this-first
    this-second

# Implicit `do`?
# no, it should pass a list of exprs?
# more flexibility for each fn?
# ambiguous?

if (logged-in? user) then:
  this-first
  this-second

---

# generify a set's "such that"? |
# can reuse pipes/currying
# can add typing to vars via bindings

# ambiguous with piping?
# no because it requires parens?
# when outside significant indent?
# only when creating math?

# math
{x | x > 0}

# like the idea of maps as fns

{\value | (> value 0)}
{\key: \value | (Text value)}

# Elm
-- update a field
{ point | x = 6 } == { x = 6, y = 4 }

# Only math notation built-in
# Stdlib adds helpers for type info

# Don't like param count not enforced
# Don't like `do` as a built-in
# Don't like separate map syntax

# get, set/put, unset/remove, has?
# insert/merge

# There will always be metadata
# line, column, file, type
# debugger, test frameworks, etc

# constraint parameter types only?

(slice start: 0 end |
  start: number
  end: number)

(start end | start: 0 ...

# create empty data type w/constraint
# add to bindings to restrict
(index: value |
  (and
    (in? index {\start \end})
    (is? start Number)
    (is? end Number)))

\(* x 2 | (is? x Number))

---

# currying for easy lambdas?
# dynamic binding still default?
(+ x 1 x:)
(x: | + x 1)

# default is to evaluate arguments?
# quote to force deferring?
(io::print arg \arg:)

---

# maybe goals:
# - easy non-indent bindings
# - easy code generation for binds 
# - easy optional static typing
# - easy type introspection

# syntax sugar for constraint?
# or just in library?

# typed bindings in a map
{\name: 'Bob'}
{\name:Text: 'Bob'}

# how typed bindings for any key?
# - override setters?
# - restrict mutator fns?

# how to introspect types?
# - make : a chain/tuple?

# pairs as the basis for all?
# could add static typing?
# easier global vars?
# makes `=` reserved?
# - not if a pair has rigid syntax
# - `=` easier to type than `:`
# how to define new types?
# non-ambiguous in fns, kwargs last
# - not good arbitrary rules?

# type inference
name = 'Bob'

# explicit type
# can be used for casting?
name: Text = 'Bob'

# dynamic typing
name := 'Bob'

# generalized pair syntax?
# linked list-like syntax?
# - too much syntax?
# opposite syntax to get-chaining
# - quotes left side
# - associates on right side
# ambiguous with currying?
# - no, kwarg is always a 1-tuple
# map uses 2-element lists as pairs?
a:b:c:d
[a [b [c d]]]
[\a [\b [\c d]]]

# MAC address
01:23:45:67:89:AB

# time
12:45:00

# Windows path
C:\file.txt
[\C \file.txt]

# not ambiguous if uniform?
# automatic quote? easy unquoted list

(range list from: 1 to: 9)
(1: range 2: list from: 1 to: 9)
([1 range] [2 list] [from 1] [to 9])

# by convention, type is 2nd element?
# typing as hints only?
# more flexibility if impl in stdlib?

name: Text: 'Bob'
[name [Text 'Bob']]

person: {\name: '' \age:Number: 0}

# homogenous types?

[\name ['']]
[\age [Number [0]]]

(get person \name)
>>> ''

(get person \age)
>>> Number:0

let
  Number: (proto? 0 value:)
  name: 'Bob'
  age:Number: 20

# disable type
name:: 'Bob'

# type inference 
name: 'Bob'

# explicit type
name:Text: 'Bob'

# type cast
# - list of what?
name:List: 'Bob'

# builtin instead of operator?
# - less syntax
# - still introspective
# returns strongly bound map
# can use fns 4 arbitrary constraints
# how to query constraints?
# how to constraint arbitrary keys?
# try to make it less "magic"?
# - functions accept `bindings`
# - accept `constraints` as well?

(constraint {\name: Text})
(\name: | (Text name))

\(+ x y \constraints: {
  x: Number
  y: Number
})

add-name: (get key: constraints: {
  key: Text
})

# get prototype and constraint
# return type? Original call?
(proto value)
\(proto base constraint)

# exposes builtin types
# and their constraints, if any
(proto [])
{
  \base: {}
  \key: (and (is? Number) (>= 1))
}

# new prototype w/optional constraint
# empty constraint for no constraints
(proto value constraint)

# constraint format?
# try to be consistent across types
{
  \value: prototype|function
  \key: ditto
  \rest: {
    \some-specific-key: xyz
  }
}

# bad to couple prototype with types?
# every let could create a new proto
# - remove proto & add constraint
# - builtin types are constraints

# query constraint of a value
(constraint [])
{
  \base: {}
  \key: (and (is? Number) (>= 1))
  \next: {
    \key: +
  }
}

# create a new constrained value
# create a list of Text values only
(constraint [] {\value: Text})

(constraint {name: ''} ...)

# syntactic sugar for constraints?

# inferred type
Person: {\name: ''}

# cast to force type change?
# good to not need extra syntax
# - heterogeneous types?
# - homogeneous types?
Person: {\name: (List '')}

# merging/casting/converting
[] [1 2 3]
>>> [1 2 3]
'' \xyz
>>> 'xyz'
'Bob' \xyz
>>> 'Bobxyz'

# no enforced types
{}

# remove enforced types?
# - (up-)casting types?
# - how remove only one field type?
(Map Person)

# homogeneous types for keys
{Symbol:}

# homogeneous types for values
{:Text}
[:Number]

# homogeneous types for keys & values
{Symbol: :Text}

# mixing homogenous with heterogenous
{\name: '' Symbol: :Text}

# for functions?

# heterogeneous types
# - is `x` a placeholder or a symbol?
(x: Positive | incr: + x 1)

# homogenous types
[] Text
[x: Text|]
[:Text|]

# homogenous function
???

# would have to repurpose `.`?
# it’s already reserved for numbers?
# what about `...`? `..`?

# `.` and `:` creates an association?
# - what kind of association?

1.5

127.0.0.1

io.print
[io \print]

C:hello.txt
[C \hello \txt]

01:23:45:67:89:ab

12:45

(io.print 'hi')

# REPL var top level?
# why only REPL?

# add to bindings, essentially a var
# grammar evaluate value, assign name
name: 'Bob'

# same as a fn call, but has no name
# can still get value from bindings?
# too inefficient to name everything?
# not in practice, useful for REPL?
+ 1 2
1: (+ 1 2)

# no need to force disambiguation?
# it’s more uniform, and still works

# value “fn call”
name: 'Bob'

# implicit call (bad?)
# instead of storing a ref, calls it
fn: exit
fn: exit 1
fn: exit code: 1
fn: (exit)
fn: (exit 1)
fn: (exit code: 1)

# enforce kwargs to come last?

# fn arg evaluation order?
# spec that it may be in parallel?
# just like for all collection types?
# pure functions only?

# a file is a list of expressions
# an empty file is an empty list
# stdin is also a list of expressions
# REPL is just stdin as a “file”
# REPL can also use a file as input

# file should be the same as a REPL?
# REPL uses a custom evaluator
# like `let*` per expression
# with custom commands? Eg. help
# make it public/embeddable

# `import` can evaluate list items
# just like a file-wide `let*`

# wouldn’t they be kwargs for `do`?
# - `do` call will be deferred
# - and will become the new bindings
# - kwargs will be bindings already?
# - if not a fexpr then evaluated
# - and dynamic scope by default
# - `do` could work as a let?
#   - doesn’t need to
#   - can use parent bindings
#   - too magic?
#   - won’t be like let* ?
#     - it will? it’s in bindings
#     - but it’s all evaluated first?
#     - `do` must be lazy, not eager
#     - has to modify bindings?
#     - for each evaluated kwarg
#     - not if each var new fn call
#   - introduce macros for code gen?
# - don’t like that it isn’t stdlib

name: 'Bob'
age: 20

io::print name
io::print age

# grammar kwargs also on indent line?
# use parens to force a function call
# not very uniform
# - grammar doesn’t change
# - it’s up to each fn to decide?
# - can be thought of as a "tag"
# - it’s in scope via bindings
# - `let*` by default?
# - each var creates a new fn call?
# - ambiguous? force disambiguation?

let
  name: 'Bob'
  age: 20
  io::print name
  io::print age

# lazy instead of deferring fn calls?
# to force evaluation:
(get value)

do
  name: 'Bob'
  io::print name
  age: 20
  io::print age

---

# function notation
(f x) = (+ x 1)
f x = + x 1
f x: Number = + x 1

# syntax sugar for
= \f \x: Number \(+ x 1)

# rules:
# - all types are values
# - all values are types
# - some types have enumerable values
# - type/value comes after `:`
# - infix assignment operator?

# general way define types via sets?

# type of single value is an enum

# list of all possible texts
# which just means: list of text
Names: [t: Text | true]
Names: [:Text]

(domain Names)
>>> PositiveInt -> Text

(formula Names)
>>> (key: value: | true)

# set/type builder notation
# set of all positive numbers
# is result a set? Or number type?
# both? A number type can be iterated
# if type enumerable, then has values
Positive: {x: Number | >= x 1}

(domain Positive)
>>> {\x: Number}

(formula Positive)
>>>

(domain (formula Positive))
>>> 

(formula (formula Positive))
>>> 

Int: {x: Positive | = (floor x) 0}

(next UInt)
>>> 0

(next UInt 0)
>>> 1

# interval/type notation? (equiv.)
# ditto wrt to being enumerable
Positive: (0: Int, infinity)
Positive: (0: Int .. infinity)

[-2, 2]

# fn notation (w/name, lexical scope)
# ambiguous with piping?
# x or its proto must be Number
# "a fn w/params such that"
(x: Number | f: + x 1)

# type inference
(x | + x 1)
(+ x 1 x:)
(x: f: + x 1)
(+ 1 x:)

# dynamic typing
(x: | + x 1)

# unnamed param
(:Positive | ...)

# dynamic scope?
(+ x 1 x: bindings:)

# a set w/homogenous types such that
# is the formula the actual content?
# or a predicate like math?
# no easy way for composite types?
# eg. List of Text
Texts: [x: Text | true]
Texts: [:Text]

(proto [1 2 3])
>>> list-builder notation value
>>> not the empty list

(formula [])
>>> {key: value}

# if a predicate then is it not a fn?
Texts 123
>>> false

# also a list of all possible Texts?
(next Texts)
>>> ''

# predicates allowed as constraints?
# it’s more like, no types, only pred
(names: Texts | ...)

# heterogeneous types?
???

---

# builtin fns have constraints
# reuse maps as fns w/type info?

# maps map one value to another
# no params = value
# can be a lazily evaluated value

phonebook: {'Bob': 123}
phonebook 'Bob'
>>> 123

f: {{Num Num}: \(+ arg.1 arg.2)}
f 2 3
>>> 5

---

# math function notation

# no types
# default fallback or type inference?
(f x y) = (+ x y)
f x y = + x y

# supports overloads
f x:Number y:Number = + x y
f x:Text y:Text = concat x y

# bindings
name = 'Bob'
name: Text = 'Bob'

phonebook: (Map Text Number): {}

---

# ambiguity: quote vs defer vs lazy

---

# no dynamic binding? Only lexical?

---

# rename prototype to proto-value?

---

# insert shouldn’t couple:
# - setting
# - displacing

---

# need unquote operator?

---

# scope "bleeding"?
# eg. let implemented as a fn
# depends if it fixes bindings or not

let
  x: 1
  let
    y: x

---

# bidirectional map? [:]
# ordered map? (:)
# compose map from list and set?

---

# types? casts?
# how to inspect types? protos?
# Don't mix set/get on same function?

# get proto-value/type
(proto person)

# create prototype w/o constraints
(proto {\name: 'Bob'} {})

# auto infer constraint?
(proto {\name: 'Bob'} constraint)

# heterogeneous?
(prototype {\name: '' \age: 0}
  {Symbol}: {\name: Text \age: Number})

# list of numbers
(prototype [] Number)

# generics
(function list-of (type)
  (prototype [] type))

# get local from prototype?
(get value)

# get type constraint?
(constraint value)

# get prototype?
(constraint value kind: prototype)

---

# spec for questions below

# ok to have rules, Symbols have too
# fn list 1st key is its name
# fn list 1st value is its body/a fn
# quoting creates a closure
# closure = symbols list + bindings
# currying creates new fn body

# why quoting lists no closure?
# do fn non-num keys alias num keys?
# assume fn list keys are symbols?
# lexical binding by default?
# fn lists always have `bindings`?
# error on non-existing free symbols?
# it’s the same req when calling
# for arbitrary symbols put in env
# `bindings` must have them?
# unquoted params (default) = eval?
# quoted params = un-eval?

\(inc: + x 1)

\(count-locals: count bindings)

\(inc: + x 1 x:)

(insert
  \(inc: (+ bindings::x 1)
    x: (evaluate bindings::x))
  \bindings
  bindings)

# still lexical binding, not dynamic

\(inc: + x 1)

(insert
  \(inc: ...)
  \bindings
  bindings)

# varargs

# macro args

\(inc: + x 1 \x:)

---

# `merge` to change "types"?

# "upcast"
(merge [1] {\x: \y}) # {1: 1 \x: \y}

# "downcast"
(merge {\x: \y} [1]) # ditto?

---

# can escape accept multiple args?
# splice?

---

# new built-in prototype
# Metadata extends Symbol
# syntax is too weird?
# feels like a shortcut
# it's very orthogonal though
# read-only?

map::^count
value::^prototype

^line
^count

(get map ^count)
(set [1 2 3] ^count 2)

---

# only function lists/calls
# have prototypes and constraints?
# and line and column?
# the bindings key is already special
# orthogonal, can set count to trim

# feels a shortcut, prefer functions

# every value has two parts?
# - data
# - meta-data

# no metadata function, special keys?
# if as keys, themselves prototypical
# avoids key conflicts
(get map :prototype)
(get map :constraint)
(get map :count)

map.:prototype
map.|prototype|
map.^prototype
map.`prototype
map.^size

(get map 'Bob')
map.['Bob']

(get (metadata map) \prototype)
(get map \^prototype)
(get map \prototype meta?: true)
(get map \proto metadata)

let count: (get
  map:
  key: \prototype
  meta?: true)

# bad to need to skip when iterating
{\name: 'Bob' \prototype: Map}

# not necessarily that many conflicts
# it uses symbols, not strings
# just interpreted differently

# metadata is read-only
# works well for line, column, length
(metadata value)

# get prototype of a value
(metadata value \prototype)

# bindings has `line` and `column`?
(metadata value \line)

(metadata text \count)

# metadata about the language
(metadata)

# numerical tower
# can't create prototypes of primitives
# so it just returns itself
(prototype 0) # non-negative integer
(prototype 1) # positive integer
(prototype -1) # integer
(prototype 0.0) # non-negative decimal
(prototype 1.0) # positive decimal
(prototype -1.0) # decimal
(prototype 1.(3)) # real
(prototype 1+2i) # imaginary?

# built-in (?) imaginary function
(i 2)
2i

# metadata on numbers?
{
  \numerator: 1
  \denominator: 2
}
