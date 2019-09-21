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

pipe in: A
     to: cat to: sort to: uniq
     out: B

# `|` as a (currying?) function
$ | cat records | sort | uniq
$ | date > now

# as a delimiter?
io::print |cat records|uniq|sort|

# how type hints?
# how type generics?
# deal in terms of prototypes?

# generify a set's "such that"? |
# can reuse pipes/currying
# can add typing to vars via bindings

# equals sign would be easier to type
# and more familiar
# but would make it reserved?
# and code blocks look weird?
# can't reuse for pipes?

# ambiguous with piping?
# not if pipes can't be used inside
{\age: 0}
{\age|Number: 0}
{\age: 0 | Symbol: Number}

{\age = 0}
{\age := 0}
{\age: Number = 0}

# empty list of numbers only
[| Number]

# empty set of numbers
{| Number}

# empty map of texts to numbers
{| Text: Number}

# generics?
# for parameters and collections
function f (x)
  {\key: x | Symbol: (prototype x)}

# can prototypes change the type?
# vars can break unrelated function
# bindings behave differently?
# ok to differ since it's special?

# math
{x | x > 0}

# Elm
-- update a field
{ point | x = 6 } == { x = 6, y = 4 }

---

{\age|Number: 20}

fn greet (name|Text age|Number)
  ...

# Only supports math notation built-in
# Stdlib adds helpers for type info

# Empty collections only
# Non-ambiguous with piping
# Can start with prototypes only first
[| Number]
[| \(= (prototype (arg 1)) Number)]

# Infinite set of even numbers
# When to quote or not?
# How to introspect?
{(* 2 n) | (is? Number n)}

# Empty set of only even numbers
...

# Typed function
add := ((+ x y) | (is? Number x y))

# Modify `prototype` to use types?
# Switch parameter order? base value
# How to introspect types?

# Create a new constraint
# new type? new prototype?
(restrict List \(Number? (arg 1)))

# list is a constraint on top of map
# it just happens to have syntax
[]
{\x: \y | \(and (Integer? x) (>= x 1))}

# Don't like param count isn't enforced
# Don't like `do` as a built-in
# Don't like `local` as a built-in
# Don't like separate map syntax

# There will always be metadata
# line, column, file, type
# Remove `prototype`
# Remove `local`

(metadata value)
(metadata value map)

# calling a map as function
# vs getting the value for a key
{{\x:Number \y}: \(+ x y)}

# typed struct
# - creates a new type
# - defines typing and form
# - makes typing first-class
# - if in a function, then generics
# - where are the default values?
(prototype {} {\name: Text})

# typed function
# - where's the body?
(prototype () (\x: Number \y: Number))

# int type?

# make `insert` allow multiple values?

---

# there's no function concept
# there's no set concept 
# it's all expressed through maps
# and constraints

# defining a map
let person: {\name: 'John'}

# calling it as if it was a function?


# defining a function
let inc: {\[x]: \(+ x 1)}
(inc 2) # = 3
(get inc \[x]) # = function body

# overload with defaults
# explicit types and inferred
let inc: {
  \[value:Number]: \(inc value 1)
  \[value x:Number]: \(+ value x)
}

# varargs?

---

io.print 'Hello'

123.45

{\name: 'Bob' \age: 20}

if (logged-in? user)
  io.print 'Hi'

if (logged-in? user)
  then: io.print 'Hi'

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

# function?

# types?

# currying
let
  phonebook: {'Bob': 1234567890}
  lookup: (get phonebook key:)
  (lookup 'Bob')

# shell pipe operator?
cat | sort | uniq | wc
