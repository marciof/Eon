- Don't make a copy of video/rows/columns in the VGA text mode module
- unit testing
- profiling
- coverage
- code check (memory leaks, lint tools)
- Use exceptions to reduce dependency coupling between System components (e.g. Memory, Log).
- So that they don't need to call System::stop() directly, for example (e.g. calls to Log::error will be converted to an exception throw).
- Remove calls to System::get_instance() and make everything an object/class to remove globals and reduce dependencies?
- Private constructor for singletons?
- Resolve non-source code related TODO's.
- Document only what's need. Document log's format string grammar. Also check for string end whenever ++format.
- Is the same dtor/obj registered twice for at-exit?
- Check and write down the difference between *(.rodata*) and *(.rodata).
- Implement a (physical) memory manager.
- http://www.osdever.net/bkerndev/Docs/gdt.htm
- http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
- http://stakface.com/nuggets/index.php?id=11&replyTo=0
- http://www.osdever.net/tutorials/view/memory-management-1
- Operating Systems / Kernels:
- https://github.com/runtimejs/runtime
- http://www.minix3.org/
- http://sourceforge.net/projects/viridis/
- http://github.com/giannitedesco/scaraOS
- http://www.whitix.org/
- http://sites.google.com/site/scorchopsys/
- http://common-lisp.net/project/movitz/
- http://sourceforge.net/projects/theosperiment/
- http://en.wikipedia.org/wiki/Plan_9_from_Bell_Labs#Design_concepts
- https://github.com/google/sanitizers

```
# TODO: Document.
# TODO: Function definition helper (named arguments, etc).
# TODO: Enforce types, values and number of parameters.
# TODO: Document that boolean operators short-circuit.
# TODO: Accept a variable number of arguments for some boolean operators.

# TODO: Accept an optional scope parameter?
# TODO: Evaluate arguments?
(put (get scopes 1)
    'get-argument
    '(get (get scopes 2)
        (- (get (get scopes 1) 2) 1)))

(put (get scopes 1)
    'evaluate
    '((get-argument 1)))

# TODO: Enforce it's not re-declared.
(put (get scopes 1)
    'var
    '(put (get scopes 1)
        (get-argument 1)
        (evaluate (get-argument 2))))

(var Boolean (identify (= 0 0)))
(var List (identify '()))
(var Map (identify []))
(var Number (identify 0))
(var Object (identify ...))
(var Set (identify {}))
(var Symbol (identify 'symbol))
(var Text (identify ""))

(var true (= 0 0))
(var false (= -1 1))
(var infinity (/ 1 0.(0)1))

(var count '(traverse (evaluate (get-argument 1))))

(var call
    '(evaluate (List
        (defer ((escape (evaluate (get-argument 1)))) 'escape)
        (evaluate (get-argument 2)))))

# (stmt-1 ... stmt-N)
var do
    (evaluate
        (get
            [true: ... false: '(get (List (delete arguments 1) (call do arguments)) 2)]
            (= (count arguments) 0)))

def if (condition then else)
    evaluate (get [true: then false: else] (evaluate condition))

def and (x y)
    evaluate (get [true: y false: false] (evaluate x))

def not (x):
    get [true: false false: true] (evaluate x)

def or (x 'y)
    evaluate (get [\true: true \false: y] x)

def <> (x y)
    not (= x y)

def < (x y)
    and
        <> x y
        = (* (- x y) infinity) (- infinity)

def <= (x y)
    or
        = x y
        = (* (- x y) infinity) (- infinity)

def > (x y)
    and
        <> x y
        = (* (- x y) infinity) infinity

def >= (x y)
    or
        = x y
        = (* (- x y) infinity) infinity
```
