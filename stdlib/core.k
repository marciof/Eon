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

  \_if: \((get
    {
      true: \(evaluate bindings::3)
      false: \(evaluate bindings::4)
    }
    (evaluate bindings::2))

  \_and: \(evaluate (get
    {
      true: bindings::3
      false: false
    }
    (evaluate bindings::2)))

  \_or: \(evaluate (get
    {
      true: true
      false: bindings::3
    }
    (evaluate bindings::2)))

  \_not: \(get
    {
      true: false
      false: true
    }
    (evaluate bindings::2))

  \_<>: \(_not (=
    (evaluate bindings::2)
    (evaluate bindings::3)))

  \_<=: \(_not (>
    (evaluate bindings::2)
    (evaluate bindings::3)))

  \_>=: \(_not (<
    (evaluate bindings::2)
    (evaluate bindings::3)))

  \do: ...
  \function: ...
  \let: ...
}
