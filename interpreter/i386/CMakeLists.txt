enable_language(ASM_NASM)

# Don't force 64-bit.
string(REPLACE "-f elf64" ""
    CMAKE_ASM_NASM_COMPILE_OBJECT "${CMAKE_ASM_NASM_COMPILE_OBJECT}")

string(REPLACE "-rdynamic" ""
    CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS}")

string(REPLACE "<CMAKE_CXX_COMPILER>" "<CMAKE_LINKER>"
    CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")

string(REGEX REPLACE "<(CMAKE_CXX_LINK_)?FLAGS>" ""
    CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")

# NASM requires include directories to end in a slash.
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -f elf -i ${CMAKE_CURRENT_SOURCE_DIR}/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -fno-exceptions -fno-nonansi-builtins -fno-rtti -nostdlib -nodefaultlibs -nostartfiles -ffreestanding -pedantic-errors -Wall -Wextra")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")

# FIXME: missing build dependency on the linker script
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m elf_i386 --script ${CMAKE_CURRENT_SOURCE_DIR}/layout.lds")

add_executable(${PROJECT_NAME}.i386
    ${core_sources}
    multiboot/header.c
    multiboot/Boot_Device.cpp
    multiboot/Boot_Device.h
    multiboot/Drive.cpp
    multiboot/Drive.h
    multiboot/Info.cpp
    multiboot/Info.h
    multiboot/Memory_Region.cpp
    multiboot/Memory_Region.h
    vga/Attr.cpp
    vga/Attr.h
    vga/Color.cpp
    vga/Color.h
    vga/CRT.cpp
    vga/CRT.h
    vga/Extern.cpp
    vga/Extern.h
    vga/Gfx.cpp
    vga/Gfx.h
    vga/Seqr.cpp
    vga/Seqr.h
    vga/Text.cpp
    vga/Text.h
    Bit.h
    IO.asm
    IO.h
    Log.cpp
    Memory.asm
    Memory.cpp
    arg.asm
    support.cpp
    support.h
    System.asm
    System.cpp)
