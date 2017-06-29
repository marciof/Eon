enable_language(ASM_NASM)

# Don't force 64-bit.
string(REPLACE "-f elf64" ""
    CMAKE_ASM_NASM_COMPILE_OBJECT "${CMAKE_ASM_NASM_COMPILE_OBJECT}")

string(REPLACE "-rdynamic" ""
    CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS}")

string(REPLACE "<CMAKE_C_COMPILER>" "<CMAKE_LINKER>"
    CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_LINK_EXECUTABLE}")

string(REGEX REPLACE "<(CMAKE_C_LINK_)?FLAGS>" ""
    CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_LINK_EXECUTABLE}")

# NASM requires include directories to end in a slash.
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -f elf -i ${CMAKE_CURRENT_SOURCE_DIR}/")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -fno-exceptions -nostdlib -nodefaultlibs -nostartfiles -ffreestanding")

# FIXME: missing build dependency on the linker script
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m elf_i386 --script ${CMAKE_CURRENT_SOURCE_DIR}/layout.lds")

add_executable(${PROJECT_NAME}.i386
    ${core_sources}
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
    Bit.h
    IO.asm
    IO.h
    Log.c
    Memory.asm
    Memory.c
    arg.asm
    System.asm
    System.c)
