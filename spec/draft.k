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

if (logged-in? user) then:
  this-first
  this-second

---

$ date > now
pipe date to: \now
date to: \now

$ cat A | sort | uniq | file B

# don't need separate syntax for input?
# values are zero parameter functions

(uniq (sort (cat records)))

---

# generify a set's "such that"? |
# can reuse pipes/currying
# can add typing to vars via bindings

# ambiguous with piping?
# not if pipes can't be used inside

# math
{x | x > 0}

# Elm
-- update a field
{ point | x = 6 } == { x = 6, y = 4 }

# Only supports math notation built-in
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

io.print 'Hello'

1,234.56

{\name: 'Bob' \age: 20}

if (logged-in? user)
  io.print 'Hi'

if (logged-in? user)
  then: io.print 'Hi'

if (logged-in? user) then:
  io.print 'Hi'

# readable configs
configure
  size: 123
  name: 'blah'

# REPL var top level
name: 'Bob'

# non top level requires `let`
# otherwise it means keyword arg
let name: 'Bob'
  io.print name

let
  name: 'Bob'
  age: 20
  
  io.print name
  io.print age

# function, dynamic binding
\(+ x 1)

# function, currying can fix bindings
(\(+ x 1) x:)

# what does inspecting see?
# note it shouldn't be relied on
\(\(+ x 1)
  x: (evaluate
    (get
      (get bindings)
      \x
      (get
        (get bindings)
        2))))

# types? casts?
# how to inspect types? protos?
# combine `prototype` and `local`?
# use `next` to go up the proto chain?
# use `get` to inspect?
# orthogonal, do only one thing well

# new prototype with no constraint
(prototype {\name: 'Bob'})

# auto infer constraint?

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
(type value)
(constraint value)

# get prototype?
(type value prototype)
(constraint value prototype)

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

# not necessarily that many conflicts
# it uses symbols, not strings
# they're just interpreted differently

(get map \value meta?: true)

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

# built-in imaginary function
(i 2)
2i

# metadata on numbers?
{
  \numerator: 1
  \denominator: 2
}

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
.name

person.name
.name person

# shell pipe operator?
cat | sort | uniq | wc
