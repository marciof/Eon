%include "arg.asm"

section .bss
align 1

gdtr:
    resw 1
    resd 1

section .text
align 4

global e_Memory_Physical_set_gdt_reg
e_Memory_Physical_set_gdt_reg:
    enter 0, 0
    
    mov ax, E_ARG(1)
    mov [gdtr], ax
    
    mov eax, E_ARG(2)
    mov [gdtr + 2], eax
    
    lgdt [gdtr]
    leave
    ret
