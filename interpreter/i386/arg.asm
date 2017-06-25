; Addresses an argument in the stack by its position (one-based index).
; Stack addressing is always performed with double words for performance
; and because of 32 bits mode. Since everything is aligned at double word
; boundaries, anything smaller will be promoted.
%define E_ARG(n) [ebp + (n * 4) + 4]
