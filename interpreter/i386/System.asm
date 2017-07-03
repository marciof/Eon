%include "arg.asm"
%define STACK_LENGTH (16 * 1024)

extern main

section .bss
align 4

global e_multiboot_info
e_multiboot_info:
    resd 1

global e_multiboot_magic_num
e_multiboot_magic_num:
    resd 1

stack:
    resb STACK_LENGTH

section .text
align 4

global e_System_halt
e_System_halt:
    cli
    hlt

global _start
_start:
    ; The stack pointer initial value isn't "stack + STACK_LENGTH - 1" because
    ; it always points to the last element.
    mov esp, (stack + STACK_LENGTH)

    ; FIXME: don't use global state, pass as arguments
    mov [e_multiboot_magic_num], eax
    mov [e_multiboot_info], ebx
    
    call main

global e_System_reset
e_System_reset:
    ; FIXME: explain part about keyboard
    ; Reset by causing a triple fault (which doesn't require a keyboard).
    int 3
    ; FIXME: can reuse `halt`?
    cli
    hlt
