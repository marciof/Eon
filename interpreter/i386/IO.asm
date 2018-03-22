%include "arg.asm"

%macro K_IO_READ_FN 2
global k_IO_read_%1
k_IO_read_%1:
    enter 0, 0
    mov edx, K_ARG(1)

    ; Clear return value register.
    mov eax, 0

    ; Return the value read.
    in %2, dx
    
    leave
    ret
%endmacro

%macro K_IO_WRITE_FN 2
global k_IO_write_%1
k_IO_write_%1:
    enter 0, 0
    
    mov edx, K_ARG(1)
    mov eax, K_ARG(2)
    out dx, %2
    
    leave
    ret
%endmacro

section .text
align 4

K_IO_READ_FN byte, al
K_IO_READ_FN dword, eax
K_IO_READ_FN word, ax

K_IO_WRITE_FN byte, al
K_IO_WRITE_FN dword, eax
K_IO_WRITE_FN word, ax
