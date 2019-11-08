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

# Pipeline support?
# need currying for ease of use?

$ date > now

(file \now (date))
date | file \now

$ < A | cat | sort | uniq > B

(file \B (uniq (sort (cat (file \A)))))
file \A | cat | sort | uniq | file \B

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
# Don't like `local` as a built-in
# Don't like separate map syntax

# get, set/put, unset/remove, has?
# insert/merge

# There will always be metadata
# line, column, file, type
# debugger, test frameworks, etc
# Remove `prototype`
# Remove `local` (arg = local binding)

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

# function list/code
# dynamic binding by default
# unevaluated by default

\(+ x 1)

# lexical binding

(insert
  \(+ x 1)
  \bindings
  bindings)

# eval doesn’t need bindings param
# fn lists can have one already
# when they don’t it’s dynamic

(insert
  \(+ (evaluate bindings::x) 1)
  \bindings
  bindings)

# module is an implicit fn call
# has `bindings` param w/ built ins
# unquoted symbols lookup bindings

(= get bindings::get)

# naming functions

\(inc: ...)
???

# fn call becomes deferred bindings
# has `bindings`?
# - it becomes the parent bindings
# - otherwise use current bindings

???

---

# currying

\(+ x 1 x:)

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

---

# types? casts?
# how to inspect types? protos?
# combine `prototype` and `local`?
# use `next` to go up the proto chain?
# use `get` to inspect?
# orthogonal, do only one thing well

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

---

(proto value [base])
(proto? value [base ...])

---

# eval doesn’t need bindings?
# it’s part of a fn list

---

# remove all barriers, simplify
# - no such thing as a prototype
# - classes, types are just values
# - no inheritance (but can simulate)
# - just "structural typing"
# - no need for `local`
# - special `constraint` in functions

# each bindings has a `bindings` sym
# - used to go up the call stack
# - no need for `prototype`
# - default lookup unquoted symbols
# - can create fake eval bindings
# - can create fake call stacks

function who-called-me ()
  io::print bindings::bindings

# match a value against protos
# - returns key where match is found
# - returns value if no match
# - returns first match, not closest
# - delete key breaks struct compat
# - new key preserves struct compat
# - set compat value preserves compat
# - compatibility is based on struct

Map: List: Text: Symbol
Map: Set
Boolean
Number: Decimal: Integer: ...

(proto? val base ...)
(instance? val base ...)

# which of base is a proto of value?
# which one is an instance of?
# which one is struct‘lly compatible?

(proto? List Map) # true
(proto? Map List) # false
(proto? Symbol Map Text) # Map

Person: {\name: ''}
bob: (insert Person \name 'Bob')

value: (insert
  (insert Person \age 20)
  \weight
  20)

(proto? bob Person) # true
(proto? value Person) # true
(proto? 'Bob' Map) # true
(proto? 123 Map) # false

R1: {}
R2: {\name: '' \age: 0}

C1: (insert R1 \name '')
C2: (remove R2 \age)

(= C1 C2) # true

(proto? C1 R1 R2) # R2
(proto? C2 R1 R2) # R2

---

# simple fn lists as before
# no prototypes, have `proto?`
# spec when it has `bindings`
# spec for questions below
# specify built-ins are just args

# non concurrency friendly?
bindings

---

# pairs as the basis for all?
name: 'Bob'
name: Text = 'Bob'

---

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

# replace bindings with `proto` key
# - specifies call proto min reqs
# - allow non-map proto custom logic?
# - always default to have reqs
# - no env == 
# - empty env == no
# - env == param reqs
# - no parent env == dynamic bindings
# - parent env == lexical bindings

(insert
  \(inc: + x 1)
  \proto
  (insert () \x Number))

(defer escape: \_
  (inc: + x 1
    proto: (x: (_ Number))))

(inc: + x 1 proto: {\x: Number})

# before call is added to `proto`
# - does `inc` have a `proto`?
# - is it a proto of the call?

# env::env points to self?

# confusing with default arg values?
# no b/c it’s an env spec?
# types checked with `proto?`
# no env key == no checking, dynamic
# default == env == lexical

(inc: + x y environment: (
  y: 1
))

# call site must match env
# - \x level are parameters
# - \environment level is caller env

(inc: + x 1
  environment: (
    \environment: environment
    \x: Number
  ))

(cat: + x y
  environment: {
    \environment: environment
    \x: {Number Text}
    \y: {Number Text}
  })

# bidirectional map? [:] ?
# decompose map into list and set?

type-registry: {
  \Person: {\name: ''}
}

(typeof: x environment: {
  \environment: environment
  \x: type-registry
})

# explicit disable type checking

environment: {
  \environment: environment
  \x: []
)

# explicit disable param checking

environment: {
  \environment: environment
}

# - actual call proto has the "type"?
#   needs list of structs
# - can’t type ID?
# - `proto?` builtin? orthogonal?
# - macro args? double quote `proto`?
# - keyword quoting? when needed?
# - dynamic or fixed binding?

(inc 5)
(inc 'Hi')

---

# free to define type ID in stdlib
# can register system-wide for ID

(register \Person Person)

# questions:
# - returns first match is confusing?
# - perf issues with struct matching?
# - how to optional static typing?
# - line/column metadata?
# - could use a `merge`?
# - no default dynamic binding?

# varargs?
# macro params?
# no params?
# generic params?
# generics?
# argument names?
# body lexical binding?
# fixed param order an issue?
# inspect? builtins?
# naming functions?
# how to detect types?
# how do bindings access the parent?
# constraints?

# named: 1st keyword parameter
# lexical binding vars: currying
# parameter names: currying
# param presence constraint: currying
# lexical binding params: currying

#
# constraints have less flexibility
# Eg changing multi method resolution
#

# ambiguous? used like placeholders?
# need to quote or not? and pipes?
# unquoted powerful runtime create
\(add: + x: y:)

# always add constraints by default?
\(+ 1 2)

# opt out of constraints
\(+ 1 2 |)

# constraint syntactic sugar?
(add:+ x: y: | x: Number y: Number)

# varargs?
(add:+ nums: | nums: (Number ...))

# if body has multiple bodies
# then it’s a multi method?

# auto constraint for presence?
# where’s the auto arg eval?
(insert
  \(add: + bindings::x bindings::y)
  \bindings: bindings
  \constraints: \[x y])

# allow decouple def from usage?
f: (add: + x y x: y:)

(f 1 2)

# macro args: quoted keyword param
(if:
  ((get
    {
      true: \(evaluate ...)
      false: \(evaluate ...)
    )
    condition))
  condition: \then: \else:)

# no parameters?
(io::print 'Hi' bindings:)

---

# function body can also be a map
# () calling and simple fns
# {:} multi methods
# adds strong structural typing
# simplifies a lot of things
# makes more things first class
# no custom multi method resolution
# no need for a `constraint` key
# no need for a `proto` built in
# no need for a `local` built in
# ok to fix bindings at creation
# values are immutable
# can redefine `bindings` as param

# maps are now callable???
# how does that impact ident syntax?
# how are params enforced?
# where are params declared?

{
  [Text]: (io::print 'text=' x:)
  [Number]: (io::print 'number=' x:)
}

# maps map exactly 1 value to 1 value
# for no args use \()

# simple fn has no constraints?

(inc: + 1 x:)

# syntax sugar for

(insert
  \((inc: + 1 bindings::x))
  \bindings
  bindings)

---

# expose struct/pattern matching fn
# - typing struct compat 1st class
# - allows maps to not be functions
# - still removes a lot of builtins
# - can be used for type ID
# - can be used for multi methods

# how is param count enforced?
# how is param presence enforced?
# how to have a default? not needed?
# how are args passed down to match?
# make `match` easy to curry?
# () matches struct and/or values?
# [] matches values?
# struct compat has value matching?

(match constraints value ...)
(match constraints value default)

what?: (match
  {
    [Text]: (print 'text' value:)
    [Number]: (print 'number' value:)
  }
  value:)

(what? 123)

if: (match
  {
    [Bool:true Fn Fn]: (eval then:)
    [Bool:false Fn Fn]: (eval else:)
  }
  condition:
  \then:
  \else:)

# use bindings to access matched val?
# bindings::bindings::condition

(match
  {
    true: (eval expression:)
    false: ...
  }
  condition:)

# explicit bindings enforce params?
# replace `match` with `constraints?
# no multi method otherwise

(match bindings constraints default)

inc: (inc: + 1 x:)

typed-inc: (match
  bindings:
  constraints: {
    [Number]
  })

---

# currying for creating functions?

---

# merge to change "types"?

# "upcast"
(merge [1] {\x: \y}) # {1: 1 \x: \y}

# "downcast"
(merge {\x: \y} [1]) # ditto?

---

# non ambiguous? no extra syntax?
# constraint on value, not function?

{\name:Text ''}

---

# iterator protocol for lazy values?
# `next` is an iterator?
# protocol for static "typing"?

---

# can escape accept multiple args?

---

(get (metadata value) \proto)

# equality comparison?

---

# new built-in prototype
# Metadata extends Symbol
# syntax is too weird?
# feels like a shortcut
# it's very orthogonal though

map::^count
value::^prototype

^line
^count

(get map ^count)
(set [1 2 3] ^count 2)

(insert Map ^prototype {\name: ''})

---

# only function lists/calls
# have prototypes and constraints?
# and line and column?
# the bindings key is already special
# othogonal, can set count to trim

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
# they're just interpreted differently

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

---

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

# shell pipe operator?
cat | sort | uniq | wc

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
