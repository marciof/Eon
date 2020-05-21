# spec example of lexical binding
# and naming fns, \(incr: + x 1)

# spec explain proto/prototype
# not prototypical inheritance
# but more like cloning and modifying

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

# splice = insert + merge + delete

---

# syntax sugar for setter?
# there’s already for getter
# careful with too much syntax

let user: {\name: 'Bob' \age: 20}
  user.name
  
  user \name
  user \name 'Alice'
  user \name: 'Alice'
  
  (set user \name 'Alice')
  (set user.name 'Alice')
  
  (io \print) (user \name)
  io.print user.name

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

# Number is Symbol evals to itself
# Boolean is Number restricted 0 or 1
# Map is the root
# want to merge [] and ()

---

# `:` less syntax, "prettier", no w/s

# avoid too much syntax
# be explicit
# be safe by default
# - static typing
# - lexical scope (defer is WYSIWYG?)

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

# not proto value or type hierarchy:
# value hierarchy from constraints

# new constraint
(proto base values)
(proto base keys values)

# homogenous types
Names: (proto [] Text)
Phonebook: (proto {:} Text Number}

# query constraint
(proto value)

# query built in constraints
(proto [])
# ({:} NaturalNumber)

# define errors, updates, adds, dels

---

# fn as a value constraint
# - more flexible
# - no new syntax
# - easy to understand
Map: (splice {:} map:)
Text: (splice '' map:) 
List: (splice [] map:)
Number: (+ 0 number:)

# value inference, default
name: 'Bob'

# value assertion, explicit
name: Text 'Bob'

# value up-cast, safe
chars: List 'Bob'

# homogenous type
Numbers: \(map Number (List map:))
numbers: Numbers [1 2 3]

...

# heterogeneous type
Set: (splice {} map:)
[]
[0 'a']

# how to get type "ctor" from value?

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
...

---

# cast with default
name: (cast '' 'Bob')
chars: (cast [] 'Bob')
panic: (cast 0 'Bob')
safe: (cast 0 'Bob' -1)
homogenous: (cast [] [] value: Num)

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

# Don't like param count not enforced
# Don't like `do` as a built-in
# Don't like separate map syntax

# get, set/put, unset/remove, has?
# insert/merge

# There will always be metadata
# line, column, file, type
# debugger, test frameworks, etc

---

# currying for easy lambdas?
# dynamic binding still default?
(+ x 1 x:)
(x: | + x 1)

# default is to evaluate arguments?
# quote to force deferring?
(io::print arg \arg:)

---

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

# math function notation?

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

phonebook: (Map Text Number) = {}

---

# ambiguity: quote vs defer vs lazy

---

# no dynamic binding? Only lexical?

---

# rename prototype to proto-value?

---

# insert shouldn’t couple?
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

# can escape accept multiple args?

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
