%include "arg.asm"
%define STACK_LENGTH (16 * 1024)

extern main

section .bss
align 4

global k_Multiboot_info
k_Multiboot_info:
    resd 1

global k_Multiboot_magic_num
k_Multiboot_magic_num:
    resd 1

stack:
    resb STACK_LENGTH

section .text
align 4

global k_Cpu_halt
k_Cpu_halt:
    cli
    hlt

; @see layout.lds
global _start
_start:
    ; The stack pointer initial value isn't "stack + STACK_LENGTH - 1" because
    ; it always points to the last element.
    mov esp, (stack + STACK_LENGTH)

    mov [k_Multiboot_magic_num], eax
    mov [k_Multiboot_info], ebx
    
    call main
