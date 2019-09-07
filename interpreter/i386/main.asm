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

; FIXME: shutdown instead of halting
; FIXME: allow halting for debugging?
global k_Cpu_halt
k_Cpu_halt:
    cli
    hlt

global _start
_start:
    ; The stack pointer initial value isn't "stack + STACK_LENGTH - 1" because
    ; it always points to the last element.
    mov esp, (stack + STACK_LENGTH)

    ; FIXME: don't use global state, pass as arguments
    mov [k_Multiboot_magic_num], eax
    mov [k_Multiboot_info], ebx
    
    call main

; FIXME: unused
global k_Cpu_reset
k_Cpu_reset:
    ; FIXME: explain part about keyboard
    ; Reset by causing a triple fault (which doesn't require a keyboard).
    int 3
    ; FIXME: can reuse `halt`?
    cli
    hlt
