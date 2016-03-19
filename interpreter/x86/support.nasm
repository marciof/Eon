; Stack addressing is always performed with double words for performance
; and because of 32 bits mode. Since everything is aligned at double word
; boundaries, anything smaller will be promoted.


; Addresses an argument in the stack by its position (one-based index).
%define ARG(n) [ebp + (n * 4) + 4]


; Marks the beginning of a code (text) section.
%macro CODE_SECTION 0
    section .text
    align 4
%endmacro


; Marks a symbol as global.
%macro PUBLIC 1
    global %1
    %1
%endmacro
