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

  \if: \(evaluate (get
    {
      true: (get bindings 2)
      false: (get bindings 3)
    }
    (evaluate (get bindings 1))))

  \and: \(evaluate (get
    {
      true: (get bindings 2)
      false: false
    }
    (evaluate (get bindings 1))))

  \not: \(get
    {true: false false: true}
    (evaluate (get bindings 1)))

  \or: \(evaluate (get
    {
      true: true
      false: (get bindings 2)
    }
    (evaluate (get bindings 1))))

  \<>: \(not (=
    (evaluate (get bindings 1))
    (evaluate (get bindings 2))))

  \<=: \(not (>
    (evaluate (get bindings 1))
    (evaluate (get bindings 2))))

  \>=: \(not (<
    (evaluate (get bindings 1))
    (evaluate (get bindings 2))))

  \do: \(reduce
    (splice bindings {1} [])
    (evaluate (get bindings 1))
    \(evaluate (get bindings 2)))

  # Helper to have lexical binding by closing open bindings at creation.
  \function: \()
}
