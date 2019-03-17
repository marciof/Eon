# Able to work as conditions.
# Decoupled from restarting conditions.
# replaces "debug" built-in.

# Aborts the current (or global?) or given scope and replaces with a value (non-local exit).
# "return" built on top exits the function, eg. not a "let". 

(unwind value)
(unwind value scope) 

(function greet [name]
  (io::print 'hello '
    (if (empty? name)
      (rescue 'empty-name)
      name)))

### How to indicate error conditions for each built-in?
# Unwind to global scope with the full error details.
# Built-ins are overridden to add exception support.
# Built-ins will be overridden anyway to make multi-methods.
# The scope list prototype is already the full function call:
# - deferred name or body if anonymous
# - deferred arguments
# "unwind" is not to be caught by multi-methods, orthogonal.
# "exception" module builds exceptions on top of "unwind".
# "exception.builtins" adds exception support to built-ins.

(+ 1 'a')
(unwind \prototype-mismatch global-scope)
(unwind {

### How to default to a provided optional restart?
# Via functions that give an alternative result.

(rescue
  (lambda [] (greet ''))
  get-default-name)

### How to trigger the debugger in interactive mode?
# Unwind to global scope.
# No, it should instead return a value from the process?

(unwind \abort (get-prototype-root (scope)))

### How to rethrow?

(rescue
  (lambda [] (greet ''))
  (lambda [condition next]
    (io::print 'error')
    (rescue condition)))

### How to have stack traces?
# Redefine "unwind" so it records call stacks.

### How to go to the next rescue handler?

### How to unwind protect, finally clause?
# Evaluate code in a new scope where "unwind" is redefined as wrapped (not really redefined, but more like dynamically scoped)

### How to do nested rescue handlers?

(rescue
  (lambda [] (greet ''))
  (lambda [condition next]
    (rescue \blah)))

# Make `rescue` calls very specific
# eg. `(rescue \illegal-arg function:get param:\map arg:123)` 
http://www.gigamonkeys.com/book/beyond-exception-handling-conditions-and-restarts.html 
http://matt.might.net/articles/implementing-exceptions/ 
http://www.lispworks.com/documentation/HyperSpec/Body/e_cnd.htm#condition 

(var rescue-handlers {})

# call function with a handler, return value as the replacement:
# condition = value of the signaled condition
# next = next handler (which may itself signal, return value, or next)
# no matcher, unwind: drop to debugger if interactive

(function-lazy rescue [function handler]
  (let outer-scope: (prototype (get scope))
         handler-fn: (evaluate handler outer-scope)
         function-scope: (put outer-scope
           \rescue-handlers
           (put rescue-handlers handler-fn))
    (evaluate
      (defer ((escape function)) \escape)
      function-scope)))

# signal a condition

(function-eager rescue [condition]
  (if (empty? rescue-handlers)
    (debugger)
    (for handler in rescue-handlers
      # FIXME: call handler in a scope w/o it in rescue-handlers, to avoid an infinite loop
      # FIXME: handle next
      # FIXME: handle when no handler activated
      (evaluate
        # ((put '() handler) condition)
        (defer ((escape handler) (escape condition)) \escape)
        # `(,handler ,escape)

# test nested rescue with no more handlers
1, fn rescue w/ handler changes lexical scope of fn greet to contain rescue-handlers with the lambda handler
2, calls fn greet
3, calls fn rescue w/ condition \empty-name
4, loops over rescue-handlers and calls the lambda handler
5, calls fn rescue w/ condition \blah
6, has no rescue-handlers now so unwind (trigger debugger?)

---

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

$ cat records | sort | uniq
(uniq (sort (cat records)))
pipe records cat sort uniq
