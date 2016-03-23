```
(var Boolean (identify (= 0 0)))
(var List (identify '()))
(var Map (identify []))
(var Number (identify 0))
(var Object (identify ...))
(var Set (identify {}))
(var Symbol (identify 'symbol))
(var Text (identify ""))

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
