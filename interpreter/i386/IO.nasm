%include "support.nasm"

%macro E_IO_READ_FN 2
PUBLIC e_IO_read_%1:
    enter 0, 0
    mov edx, ARG(1)

    ; Clear return value register.
    mov eax, 0

    ; Return the value read.
    in %2, dx
    
    leave
    ret
%endmacro

%macro E_IO_WRITE_FN 2
PUBLIC e_IO_write_%1:
    enter 0, 0
    
    mov edx, ARG(1)
    mov eax, ARG(2)
    out dx, %2
    
    leave
    ret
%endmacro

CODE_SECTION

E_IO_READ_FN byte, al
E_IO_READ_FN dword, eax
E_IO_READ_FN word, ax

E_IO_WRITE_FN byte, al
E_IO_WRITE_FN dword, eax
E_IO_WRITE_FN word, ax
