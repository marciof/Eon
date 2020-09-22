# Pipeline support? shell pipe?

# - each pipe part is partial fn?
# - parens are replaced by pipes?
# - can still have args
# - pipeline will invoke all fns
# - may be sequential or parallel
# - fn return value is output
# - last param is input?

(reduce + 0
  (map to-int
    (match '\d+' txt)))

match '\d+' txt | to-int | reduce + 0

match '\d+' txt, to-int, reduce + 0

# comma conflicts with number sep?
# list vs scalar? use "iterables"?
# text isn’t an iterable by default?

(as List 'Bob')
(merge [] 'Bob')

# just pass input as last arg?
# too implicit?
# problem is it can break easily?
# use a pre-determined keyword arg?
# it'd be the same as orig form?

# or partial indicates input param?
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

# generics?

# disable static typing from value?

# get type/ctor/? of a value?

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

# partial for easy lambdas?
# dynamic binding still default?
(+ x 1 x:)
(x: | + x 1)

# default is to evaluate arguments?
# quote to force deferring?
(io::print arg \arg:)

# partial
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

# partial? too implicit?
# how to partial varargs?
let
  phonebook: {'Bob': 12345}
  lookup: (get phonebook key:)
  (lookup 'Bob')

# multiple partial?
(insert list: key:)

# renaming curried params
(\(get phonebook key: name) name:)
(lookup name: 'Bob')

# partial keys? too weird/implicit?
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

# get, set/put, unset/remove, has?
# insert/merge

# There will always be metadata
# line, column, file, type
# debugger, test frameworks, etc

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
# - list length isn’t known a priori
# REPL is just stdin as a “file”
# REPL can also use a file as input

# file should be the same as a REPL?
# REPL uses a custom evaluator
# like `let*` per expression
# with custom commands? Eg. help
# (make it’s API public/embeddable)

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

---

# fn extends map: ordered, so typed?
# bad to overload meaning of `|`?

incr: \[+ x 1] # dynamic or list?
pipe: [ls | count]
incr: (x | + x 1) # array untyped
incr: {x | + x 1) # set untyped
incr: {x: Number | + x 1} # map typed

# "piping" params? Still untyped
# and weird to overload piping?
# clashes with piping and partial?
# could be a generalization?
# a pipe with arguments
# use pipe+partial create a closure
# param name instead of bindings.1?
# - not an issue anymore
# - but what does inspecting see?

if (= user 'bob') then:
  range from: 1 to: 9

incr: (x: | + x 1)
greet: (| io.print 'Hi')

(incr 2)

var name: 'bob'

incr: [x: | + x 1]

greet = [| print 'Hi']
incr = [x= | + x 1]
incr = [x:Int= | + x 1]

let teen: [<= age 20]
let teen = [<~ age 20]
let teen = [< age 20]
let teen = [</ age 20]

var name='bob'

# cast vs type assertion
# list literal
# set literal
# map literal
# "such that" literal
# varargs

hist() {
  sort | uniq -c | sort -n -r
}

hist = [| sort | uniq | sort]

---

# alternative syntax?
# + easier scripting?
# + easier to enable static typing?
# - less familiar?
# - reserved `=` hurts readability?

if [is user 'bob'] then=
  range from=1 to=9

let pow = [x= y=, ^ x y]

# partial by default? good for pipes?

let pow-of-2 = [pow 2]

# vectorized by default w/ pipes?

(1 2 3), pow 2, print
(1 2 3), [pow 2], print
(1 2 3), pow 2 y=, print
