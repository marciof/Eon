{
  \Boolean: (= 0 0)
  \Function: ()
  \List: []
  \Map: {:}
  \Number: 0
  \Set: {}
  \Symbol: (prototype \x)
  \Text: ''

  \true: (= 0 0)
  \false: (= 0 1)
  \infinity: (/ 1 0.(0)1)
  \global-bindings: bindings
  \...: \...

  # TODO: evaluate arguments
  # TODO: validate arguments
  \concat:
  (get
    {
      true: bindings::2
      false: (concat
        (insert
          bindings::2
          (next bindings::3)
          (get
            bindings::3
            (next bindings::3)))
        (remove
          bindings::3
          (next bindings::3)))
    }
    (= (count bindings::3) 0)

  # TODO: can't remove key 1 from bindings
  \code:
  (concat
    ()
    (evaluate
      (remove (local bindings) 1)))

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

  \do: ...
  \function: ...
  \let: ...

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
}
