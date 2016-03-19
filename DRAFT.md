- www.infoq.com/presentations/Value-Values
- http://www-formal.stanford.edu/jmc/recursive/recursive.html
- www.wired.com/2012/06/berkeley-programming-languages/
- http://tagide.com/blog/2012/03/research-in-programming-languages/
- www.javaworld.com/javaworld/jw-03-2012/120315-fatal-exception.html
- http://steve-yegge.blogspot.com/2007/02/next-big-language.html 
- http://steve.yegge.googlepages.com/tour-de-babel
- Try to remove more built-ins? Unify, orthogonal. Improve names, more intuitive, more familiar. Add counterpart to parse?
- Try to remove more syntax without making it harder to read and use. Clean the grammar.
- Build = upon is?, or does that not work well with hashing? It doesn't, probably okay to not have identity comparison, not often used nor needed?
- Whenever the specification of a built-in procedure indicates a core process is used, should that be internally implemented or use built-ins to give a change for hooks? For example, function calling creates a new scope, should it be added through the put built-in?
- What more can the language take care of by itself, without putting the burden on the programmer?
- Python's yield as co-routine?
- Allow explicit memory management? Deterministic? With reference counting?
- Taint checking for external input data? E.g. command line arguments, stdin, etc.
- Add something like Python's __future__ to adapt to future incompatible changes?
- Built-in syntax support for graphs? DAG's, etc.
- Ensure that easy error-prone name clashing with standard library modules does not happen. E.g. in Python when writing a script with the same name as a standard module.
- Focus on design/programming patterns as areas where to improve the language.
- http://blog.plover.com/prog/design-patterns.html
- http://perl.plover.com/yak/design/
- Built-in XPath-like syntax for traversing data structures?
- Try to reuse already available syntax (i.e. list) as the mini-DSL? Must be compact/readable.
- Generalize regular expressions to allow them to be applied to both data structures and strings? And also to apply transformations (Ex: remove a specific item from a specific position in a list).
- Unify strings with regular expressions? A string is a subset of a regex:
- (match string input) # string = start/end anchored quoted regex
- (match regex input)
- http://effbot.org/zone/element-xpath.htm
- http://plasmasturm.org/log/xpath101/
- Collections:
- Lazy by default? Or with some construct to easily create lazy streams?
- Python's generator expressions, and yield? Built on continuations?
- 0.(9) = 0.999(9) = 1? Use a hyperreal number system? Update grammar production names if so.
- http://en.wikipedia.org/wiki/0.999 
- http://plasmasturm.org/log/0.999
- Reactive programming?
- http://www.felienne.com/archives/3724
- http://elm-lang.org/learn/What-is-FRP.elm
- http://en.wikipedia.org/wiki/Function-level_programming
- Assess the usability, cognitive load, typing difficulty and familiarity of the syntax and built-in identifiers.
- Optimize for UK (US?) layout.
- Use short unnabbreviated unambiguous names, preferably with letters from the home row.
- http://rigaux.org/language-study/syntax-across-languages.html
- http://ecs.victoria.ac.nz/Events/PLATEAU/WebHome
- Critics: Steve Yegge, Paul Graham
- www.wikihow.com/Avoid-Colloquial-(Informal)-Writing
- The Zen of Python: import this
- Look for pitfalls in orther programming languages as areas to avoid and improve.
- "Zero one infinity rule" - no arbitrary limits
- Postel's law - "flexible input, strict output"
- For every little thing, ask "is it really necessary?".
- Make a clear distinction between "parameter" and "argument".
- Don't leave anything as "undefined behavior".
- Don't use: "syntactic sugar", "first class object", "bug" (use "issue"), "debug".
- Don't mix collection (unordered) with sequence (implies ordering).
- Lists have positions that start at 1, instead of 0.
- Literals (such as strings or lists) are mutable.
- String length is the number of logical characters, unlike JavaScript.
- Logical values can only be "true" or "false"; no implicit conversions of zero, empty collections, etc.
- "+" and others accept only one or more arguments (no non-sense like "(+)" as "0").
- Loops do not mutate the loop variable, but create a new one at each iteration instead.
- Specify O(n) time complexity for everything (like Redis).
- Do not introduce nor allow null values.
- «"Patterns" that are used recurringly in one language may be invisible or trivial in a different language.»
- Add support for x86-64.
- Remove '/MANIFEST:NO'?
- Clean up:
- don't make a copy of video/rows/columns in the VGA text mode module
- unit testing
- continuous integration
- profiling
- coverage
- packaging (Vagrant for x86?)
- code check (memory leaks, lint tools)
- Use exceptions to reduce dependency coupling between System components (e.g. Memory, Log).
- So that they don't need to call System::stop() directly, for example (e.g. calls to Log::error will be converted to an exception throw).
- Remove calls to System::get_instance() and make everything an object/class to remove globals and reduce dependencies?
- Private constructor for singletons?
- Note down dependencies: run-time, build, test.
- Set up http://travis-ci.org
- Resolve non-source code related TODO's.
- Document log's format string grammar. Also check for string end whenever ++format.
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
