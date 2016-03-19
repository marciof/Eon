%include "support.nasm"


section .bss
align 1

gdtr:
    resw 1
    resd 1


CODE_SECTION

PUBLIC set_gdtr:
    enter 0, 0
    
    mov ax, ARG(1)
    mov [gdtr], ax
    
    mov eax, ARG(2)
    mov [gdtr + 2], eax
    
    lgdt [gdtr]
    leave
    ret
