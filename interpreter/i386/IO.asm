%include "arg.asm"

%macro E_IO_READ_FN 2
global e_IO_read_%1
e_IO_read_%1:
    enter 0, 0
    mov edx, E_ARG(1)

    ; Clear return value register.
    mov eax, 0

    ; Return the value read.
    in %2, dx
    
    leave
    ret
%endmacro

%macro E_IO_WRITE_FN 2
global e_IO_write_%1
e_IO_write_%1:
    enter 0, 0
    
    mov edx, E_ARG(1)
    mov eax, E_ARG(2)
    out dx, %2
    
    leave
    ret
%endmacro

section .text
align 4

E_IO_READ_FN byte, al
E_IO_READ_FN dword, eax
E_IO_READ_FN word, ax

E_IO_WRITE_FN byte, al
E_IO_WRITE_FN dword, eax
E_IO_WRITE_FN word, ax
