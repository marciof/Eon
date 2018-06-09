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

  \...: \...
  \global-bindings: bindings

  \if: \((get
    {
      \argument-mismatch: \(unwind \parameter-mismatch global-bindings)
      4: \(get
        {
          true: \(evaluate bindings::3)
          false: \(evaluate bindings::4)
          \non-boolean: \(unwind \prototype-mismatch global-bindings)
        }
        (evaluate bindings::2)
        \non-boolean)
    }
    (count (local bindings))
    \argument-mismatch))

  \do: \...

  \and: \(evaluate (get
    {
      true: bindings::3
      false: false
    }
    (evaluate bindings::2)))

  \not: \(get
    {true: false false: true}
    (evaluate bindings::2))

  \or: \(evaluate (get
    {
      true: true
      false: bindings::3
    }
    (evaluate bindings::2)))

  \<>: \(not (=
    (evaluate bindings::2)
    (evaluate bindings::3)))

  \<=: \(not (>
    (evaluate bindings::2)
    (evaluate bindings::3)))

  \>=: \(not (<
    (evaluate bindings::2)
    (evaluate bindings::3)))

  # Helper for named arguments.
  # Helper to have lexical binding by closing open bindings at creation.
  \function: \...
}
