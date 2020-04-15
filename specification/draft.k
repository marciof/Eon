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

# pipeline quoted as fn call?
# no new syntax, optional parens
\(date | file 'blah')

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
# no, it should pass a list of exprs
# more flexibility for each fn 
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

# maybe goals:
# - easy non-indent bindings
# - easy code generation for binds 
# - easy optional static typing
# - easy type introspection

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
# how to define new types?
# non-ambiguous in fns, kwargs last
# - not good arbitrary rules

\name: 'Bob'
\name: Text = 'Bob'

# too much to type? Just for a var?
\name := 'Bob'

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
# ambiguous with list value?
name:Text: 'Bob'
[name [Text 'Bob']]

name: 'Bob':Text
name: Text:'Bob'

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

# rename prototype to proto-value?

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

# non ambiguous? no extra syntax?
# constraint values, not functions?

{\name:Text ''}

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
