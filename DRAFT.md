```
(var Boolean (identify (= 0 0)))
(var List (identify '()))
(var Map (identify []))
(var Number (identify 0))
(var Object (identify ...))
(var Set (identify {}))
(var Symbol (identify 'symbol))
(var Text (identify ""))

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
