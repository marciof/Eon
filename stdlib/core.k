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
  
  \function: \((get
    {
      1: \(unwind \parameter-mismatch global-bindings)
      3: \()
    }
    (count (local bindings))
    1))

  \if: \((get
    {
      1: \(unwind \parameter-mismatch global-bindings)
      4: \(get
        {
          true: \(evaluate (get bindings 3))
          false: \(evaluate (get bindings 4))
          \unknown: \(unwind \prototype-mismatch global-bindings)
        }
        (evaluate (get bindings 2))
        \unknown)
    }
    (count (local bindings))
    1))

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
