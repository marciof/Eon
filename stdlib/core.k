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
  
  \global-bindings: bindings

  \if: \(evaluate (get
    {
      true: (get bindings 3)
      false: (get bindings 4)
      \non-boolean: (unwind \parameter-mismatch global-bindings)
    }
    (evaluate (get bindings 2))
    \non-boolean))

  \and: \(evaluate (get
    {
      true: (get bindings 3)
      false: false
    }
    (evaluate (get bindings 2))))

  \not: \(get
    {true: false false: true}
    (evaluate (get bindings 2)))

  \or: \(evaluate (get
    {
      true: true
      false: (get bindings 3)
    }
    (evaluate (get bindings 2))))

  \<>: \(not (=
    (evaluate (get bindings 2))
    (evaluate (get bindings 3))))

  \<=: \(not (>
    (evaluate (get bindings 2))
    (evaluate (get bindings 3))))

  \>=: \(not (<
    (evaluate (get bindings 2))
    (evaluate (get bindings 3))))

  \do: \...

  # Helper for named arguments.
  # Helper to have lexical binding by closing open bindings at creation.
  \function: \...
}
