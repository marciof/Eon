%include "support.nasm"

%macro FUNCTION_READ 2
PUBLIC read_%1:
    enter 0, 0
    mov edx, ARG(1)

    ; Clear return value register.
    mov eax, 0

    ; Return the value read.
    in %2, dx
    
    leave
    ret
%endmacro

%macro FUNCTION_WRITE 2
PUBLIC write_%1:
    enter 0, 0
    
    mov edx, ARG(1)
    mov eax, ARG(2)
    out dx, %2
    
    leave
    ret
%endmacro

CODE_SECTION

FUNCTION_READ byte, al
FUNCTION_READ dword, eax
FUNCTION_READ word, ax

FUNCTION_WRITE byte, al
FUNCTION_WRITE dword, eax
FUNCTION_WRITE word, ax
