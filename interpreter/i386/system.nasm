%include "support.nasm"

%define STACK_LENGTH (16 * 1024)
extern c_main

section .bss
align 4

PUBLIC _multiboot_info:
    resd 1
PUBLIC _multiboot_magic_nr:
    resd 1
stack:
    resb STACK_LENGTH

CODE_SECTION

PUBLIC halt:
    cli
    hlt

PUBLIC main:
    ; The stack pointer initial value isn't "stack + STACK_LENGTH - 1" because
    ; it always points to the last element.
    mov esp, (stack + STACK_LENGTH)
    
    mov [_multiboot_magic_nr], eax
    mov [_multiboot_info], ebx
    
    call c_main

PUBLIC reset:
    ; TODO: explain part about keyboard.
    ; Reset by causing a triple fault (which doesn't require a keyboard).
    int 3
    ; TODO: can reuse `halt`?
    cli
    hlt
