{
  \Boolean: (= 0 0)
  \Function: \()
  \List: []
  \Map: {:}
  \Number: 0
  \Set: {}
  \Symbol: (prototype \x)
  \Text: ''

  \true: (= 0 0)
  \false: (= 0 1)
  
  # Creates a function list from arguments.
  \lambda: \...

  \if: (lambda evaluate (get
    {
      true: (get bindings 3)
      false: (get bindings 4)
    }
    (evaluate (get bindings 2)))

  \and: (lambda evaluate (get
    {
      true: (get bindings 3)
      false: false
    }
    (evaluate (get bindings 2))))

  \not: (lambda get
    {true: false false: true}
    (evaluate (get bindings 2)))

  \or: (lambda evaluate (get
    {
      true: true
      false: (get bindings 3)
    }
    (evaluate (get bindings 2))))

  \<>: (lambda not (=
    (evaluate (get bindings 2))
    (evaluate (get bindings 3))))

  \<=: (lambda not (>
    (evaluate (get bindings 2))
    (evaluate (get bindings 3))))

  \>=: (lambda not (<
    (evaluate (get bindings 2))
    (evaluate (get bindings 3))))

  \do: \...

  # Helper to have lexical binding by closing open bindings at creation.
  \function: \...
}
