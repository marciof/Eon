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

# function, dynamic binding
\(+ x 1)

# function, currying can fix bindings
(\(+ x 1) x:)

# what does inspecting see?
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

# create a new prototype
(prototype value [constraint])

# get the proto
(proto value)

# get the constraint
(constraint value)

---

(get (metadata value) \proto)

# equality comparison?

---

# remove all barriers, simplify
# - no such thing as a prototype
# - no inheritance (but can simulate)
# - just structural typing?
# - numbers/boolean don't make protos
# - no prototype, can remove `local`

# questions:
# - same value with different protos?
# - how to optional static typing?
# - how to identify a value's type?
# - can create fake eval bindings?
# - delete key uses closest ancestor?
# - line/column metadata?
# - could use a `merge`?
# - delete key uses closest ancestor?
# - no default dynamic binding?

# gets the value that created value
# - only structural changes
# - changing values/types isn't
# - new key creates new sub proto
# - returns itself if at the root
# - can still go up bindings
# - default for unquoted symbols

(proto value)
(proto bindings)

Person: {\name: ''}
bob: (insert Person \name 'Bob')

(proto Person) # Map
(proto bob) # Person

(proto 'Bob') # List
(proto List) # Map

# checks if it's an ancestor proto

(proto? bob Person) # true
(proto? 'Bob' Map) # true
(proto? 123 Map) # false

# could use a `merge`?
# - which proto to use?
# - allow `insert` of many values?

(remove map key)
(remove map from:to) # ambiguous?

(insert map ...)
unshift: (insert list 0:)

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

(get map \^count)
(set [1 2 3] \^count 2)

(insert Map \^prototype {\name: ''})

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
let
  phonebook: {'Bob': 12345}
  lookup: (get phonebook key:)
  (lookup 'Bob')

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
