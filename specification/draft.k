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
if (logged-in? user) then:
  this-first
  this-second

---

# generify a set's "such that"? |
# can reuse pipes/currying
# can add typing to vars via bindings

# ambiguous with piping?

# math
{x | x > 0}

# Elm
-- update a field
{ point | x = 6 } == { x = 6, y = 4 }

# Only math notation built-in
# Stdlib adds helpers for type info

# Don't like param count isn't enforced
# Don't like `do` as a built-in
# Don't like separate map syntax

# get, set/put, unset/remove, has?
# insert/merge

# There will always be metadata
# line, column, file, type
# debugger, test frameworks, etc

---

# constraint parameter types only?

(slice start: 0 end |
  start: number
  end: number)

(start end | start: 0 ...

# create empty data type w/constraint
(index: value |
  (and
    (in? index {\start \end})
    (is? start Number)
    (is? end Number)))

---

# pairs as the basis for all?
# could add static typing?

name: 'Bob'
name: Text = 'Bob'

name := 'Bob'
name Text := 'Bob'

name:|Text 'Bob'

Text name: 'Bob'

---

# REPL var top level
name: 'Bob'

# non top level requires `let`
# otherwise it means keyword arg

# grammar indicate that keyword args can also be each one in a indented line?

let
  name: 'Bob'
  age: 20
  
  io::print name
  io::print age

---

# bidirectional map? [:] ?
# compose map from list and set?

---

# types? casts?
# how to inspect types? protos?
# Don't mix set/get on same function?

# new prototype with no constraint
(prototype {\name: 'Bob'})

# auto infer constraint?
(prototype {\name: 'Bob'} constraint)

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
