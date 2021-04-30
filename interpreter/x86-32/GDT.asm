%include "arg.asm"

section .bss
align 1

gdtr:
    resw 1
    resd 1

section .text
align 4

global k_GDT_set_reg
k_GDT_set_reg:
    enter 0, 0
    
    mov ax, K_ARG(1)
    mov [gdtr], ax
    
    mov eax, K_ARG(2)
    mov [gdtr + 2], eax
    
    lgdt [gdtr]
    leave
    ret
