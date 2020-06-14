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

# what inspecting sees when quoted?

---

# can type annotations be added
# and handled in stdlib?
# with a sort of code loading hook?

# `:` less syntax, "prettier", no w/s

# avoid too much syntax
# be explicit and safe by default:
# - static typing
# - lexical scope (is defer WYSIWYG?)

# constraint fn? Or struct compat?
# consistent with how `proto` works?
# why stop at types for validation?
# because can be made compile time?
# then use hints?

# there are already constraints
# symbol has constraints
# text has constraints
# having a built-in only exposes them
# but not necessarily
# could be impl in some builtin fns

# not proto value or type hierarchy:
# value "hierarchy" from constraints

# new constraint
(restrict base values)
(restrict base keys values)

# homogenous types
Names: (restrict [] Text)
Phonebook: (restrict {:} Text Number}

# query constraint
(proto value)

# query built in constraints
(proto [])
# ({:} NaturalNumber)

# define errors, updates, adds, dels

# dynamic scope?
\(+ x 1)

# lexical scope? what'll inspect see?
(+ 1 x:)
(+ 1 x x:)
(x: | + x 1) # ambiguous w/piping?

let user: {\name: 'bob' \age: 20}
  if (= user.name 'bob') then:
    math.range from: 1 to: 3

names: [::Text]
phonebook: {Text::Number}

---

# values as fns for constraints
# - explicit type is documentation
# - can’t do generics with type inf?
# - creates a new prototype
# - can't constrain fns?
# - less explicit/readable?
# - can't constrain heterogeneous?

Text: ''
Number: 0

# homogenous, explicit
names: ['Bob'] Text
names: [] Text
phonebook: {:} Text Number

# heterogeneous, default
list: []
names: ['Bob']
person: {\name: ''}

# dynamic typing
Any: (prototype)
list: [] Any

# fn params
incr: [: + x 1] x: Number
incr: (| + x 1) x: Number
incr: \(+ x 1) x: Number
incr: \(+ x 1) x: Number scope:
incr: \(+ x 1 scope: {x: Number})
incr: (x: | + x 1) x: Number
incr: () x: Number ???
incr: () {\x: Number} ???
incr: (x: Number | + x 1)
incr: (x: Number :: + x 1)
incr: (x: Number; + x 1)
incr: (x; + x 1)

---

# proto as fn ctor?
# - no new syntax
# - explicit and readable
# - extensible since it uses fns
# - still doesn’t introduce types
# - can be used for type cast

Number: proto 0
age: Number 20

Person: proto {:} (lambda (map name)
  (insert map \name name))

bob: Person 'Bob'

---

# fn as a value constraint
# - more flexible
# - no new syntax
# - easy to understand
Map: (splice {:} map:)
Text: (splice '' map:) 
List: (splice [] map:)
Number: (+ 0 number:)

# doesn’t even need to "convert"
# can just proto check and `panic`
# `panic` can still be overwritten
# may work, but isn’t static typing

# value inference, default
name: 'Bob'

# value assertion, explicit
name: Text 'Bob'

# value up-cast, safe
chars: List 'Bob'

# homogenous type
# not homogenous for every value?
Numbers: \(map Number (List map:))
numbers: Numbers [1 2 3]
numbers: List of: Number [1 2 3]

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

# only associations can have type?
# it’s how it’s enforced?

name: Text: 'Bob'
names: [Text]: 'Bob'
phonebook: {Text: Number}: {:}

person: ???: {\name: '' \age: 0}

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

# math function notation?
# bindings allows symbols and lists?
# easier to type `=`, `[` and `]`?

f x y := + x y
[f x y] = [+ x y]

# "piping" arguments into a list
# ambiguous w/piping?
# aka. fn params
# where’s the return type?
# what does inspecting see?

names = ['Bob' 'Alice']
phonebook = {'Bob' = 123}
sqr = (base: Int | pow base exp = 2)
sqr: (base: Int | pow base exp: 2)
sqr: (base::Int | pow base exp: 2)

names 1
sqr 5

# up to the fn to how to interpret?
# list: call or array

# make it dead easy to have a list
# array and/or function?
# every map created captures scope
# [] is a list
# [:] is an associative list
# () is syntax to call a list as fn
# no ambiguity w/ "calling" symbols
# ambiguous w/piping?
# values can't be "called"
# then "calling" list is a fn call

# no difference? sym vs \sym
# anything unquoted is still deferred
# top-level is a deferred fn call
# just handled by the interpreter

# calling a symbol returns itself
# symbol can’t be constrained further

(sym) # \(sym)
(\sym) # \(\sym))

greet: [io.print 'Hi'] # lexical?
greet: [| io.print 'Hi']
incr: [x | + x 1]
incr: [x: Int | + x 1]
numbers: [Int | 1 2 3]

(domain greet) # scope
(formula greet) # quoted value
(domain incr) # {x: Int scope: ...}

incr: [x . + x 1]
incr: [x: Int . + x 1]
incr: [x, + x 1]
incr: [x; + x 1]

# fn extends map: ordered, so typed?
# bad to overload meaning of `|`?

incr: \[+ x 1] # dynamic or list?
pipe: [ls | count]
incr: (x | + x 1) # array untyped
incr: {x | + x 1) # set untyped
incr: {x: Number | + x 1} # map typed

# bad param last, fine for small fns
# use stdlib for more flexibility?
incr: [+ x 1 x:]

# no additional syntax
# easier to remember 
# more uniform
# easier to read (via using stdlib)
# common data types have syntax
# why not functions too?

incr: [function [x] + x 1]

# "piping" params? Still untyped
# and weird to overload piping?
# clashes with piping and currying?
# could be a generalization?
# a pipe with arguments
# use pipe+curry to create a closure
# param name instead of bindings.1?
# - not an issue anymore
# - but what does inspecting see?

incr: [x: | + x 1]

let names: ('Bob' 'Alice') Text
  if [= names.1 'Bob'] then:
    math.range from: 1 to: 3

let names = () Text: ('Bob' 'Alice')
  if [is names.1 'Bob'] then =
    math.range from = 1 to = 3

f x:Number y:Number := + x y
f x:Text y:Text := merge x y

range from 1, to 3
{\name 'bob', \age 20}

---

# pairs as the basis for all?
# could add static typing?
# easier global vars?
# makes `=` reserved?
# - not if a pair has rigid syntax?
# - `=` easier to type than `:`
# how to define new types?
# non-ambiguous in fns, kwargs last
# - not good arbitrary rules?

# type inference
name = 'Bob'

# explicit type
# can be used for casting?
name: Text = 'Bob'

Person: {name: Text age: Number}

# dynamic typing
name := 'Bob'

# function
incr := + x 1

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

if (is? user 'bob') then=
  range from=1 to=3

if (= user 'bob') then=
  range from=1 to=3

young = (lt age 20)
young = (<= age 20)

---

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

# insert decouple: set, displace

# bidirectional map?
# sorted map?

# fn list 1st key is its name
# fn list 1st value is its body/a fn

# do fn non-num keys alias num keys?
# assume fn list keys are symbols?
# lexical binding by default?
# fn lists always have `bindings`?
# error on non-existing free symbols?
# unquoted params (default) = eval?
# quoted params = un-eval?
