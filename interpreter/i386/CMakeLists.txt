enable_language(ASM_NASM)
set(EXECUTABLE_NAME_I386 ${PROJECT_NAME}-i386)

# Some linkers require absolute paths to the linker script.
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/layout.lds)

# Don't force 64-bit in case it's cross-compiling on a 32-bit system.
string(REPLACE "-f elf64" ""
    CMAKE_ASM_NASM_COMPILE_OBJECT "${CMAKE_ASM_NASM_COMPILE_OBJECT}")
if(CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m elf_i386")
endif()

# Disable dynamic linking for static linking with a custom script.
if(CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$")
    string(REPLACE "-rdynamic" ""
        CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS}")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --script=${LINKER_SCRIPT}")

    string(REPLACE "<CMAKE_C_COMPILER>" "<CMAKE_LINKER>"
        CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_LINK_EXECUTABLE}")

    string(REGEX REPLACE "<(CMAKE_C_LINK_)?FLAGS>" ""
        CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_LINK_EXECUTABLE}")
endif()

# NASM requires include directories to end in a slash.
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -f elf -i ${CMAKE_CURRENT_SOURCE_DIR}/")

# Force a free-standing environment, no standard library available.
if(CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -nostdlib -nodefaultlibs -ffreestanding")
endif()

add_executable(${EXECUTABLE_NAME_I386}
    ${LINKER_SCRIPT}
    ${CORE_SOURCES}
    Multiboot.c
    Multiboot.h
    vga/Attr.c
    vga/Attr.h
    vga/Color.c
    vga/Color.h
    vga/CRT.c
    vga/CRT.h
    vga/Extern.c
    vga/Extern.h
    vga/Gfx.c
    vga/Gfx.h
    vga/Seqr.c
    vga/Seqr.h
    vga/Text.c
    vga/Text.h
    IO.asm
    IO.h
    vga/Log.c
    vga/Log.h
    Memory.asm
    Memory.c
    arg.asm
    main.asm
    main.c)

set_target_properties(${EXECUTABLE_NAME_I386} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

add_custom_command(TARGET ${EXECUTABLE_NAME_I386}
    POST_BUILD
    COMMAND grub-file --is-x86-multiboot $<TARGET_FILE:${EXECUTABLE_NAME_I386}>
    COMMENT "Verifying executable is Multiboot-compliant via `grub-file`")
