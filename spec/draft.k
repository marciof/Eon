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

{\age | Number: 0}

{\age: Number = 0}

# empty list of numbers only
[| Number]
[x | Number]
[x | (= (prototype x) Number)]

# empty set for even numbers only
{x | even? x}

# empty map of texts to numbers
{name: age | (and (String name) ...}

# generics?
# for parameters and collections

# math
{x | x > 0}

# Elm
-- update a field
{ point | x = 6 } == { x = 6, y = 4 }
