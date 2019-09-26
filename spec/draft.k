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

# There will always be metadata
# line, column, file, type
# Remove `prototype`
# Remove `local`

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

# function, currying fixes bindings
# what does inspecting see?
(\(+ x 1) x:)

# types? casts?
# how to inspect types? protos?
# combine `prototype` and `local`?
# use `next` to go up the proto chain?
# use `get` to inspect?
# orthogonal, do only one thing well

# every map has a prototype key?
# every map has a type key?
# every binding has line, column?
# can reuse get/set, it's composable
# will interfere with count and next
# can cause key conflicts
# no proto for numbers and booleans?

# new prototype with no constraint
(prototype {\name: 'Bob'} {})

# get prototype of a value?
(prototype value)

# numerical tower
(prototype 0) # non-negative integer
(prototype 1) # positive integer
(prototype -1) # integer
(prototype 0.0) # non-negative decimal
(prototype 1.0) # positive decimal
(prototype -1.0) # decimal

# list of numbers
(prototype [] Number)

# heterogeneous?
{\name: '' \age: 0}

(prototype {\name: '' \age: 0}
  key: {Symbol}
  value: {\name: Text \age: Number}

# generics?
(function list-of (type)
  (prototype [] type))

# get constraint of a value or proto
(constraint value)

# query inferred constraint?

# currying? too implicit?
let
  phonebook: {'Bob': 12345}
  lookup: (get phonebook key:)
  (lookup 'Bob')

# currying?
(get map: key: \name)
.name

person.name
.name person

# shell pipe operator?
cat | sort | uniq | wc
