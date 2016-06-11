enable_language(ASM_NASM)

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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -fno-exceptions -fno-nonansi-builtins -fno-rtti -nostdlib -nodefaultlibs -nostartfiles -ffreestanding")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m elf_i386 --fatal-warnings --script ${CMAKE_CURRENT_SOURCE_DIR}/layout.lds")

include_directories(SYSTEM ../ext/grub/include)

add_executable(${PROJECT_NAME}-x86
    # Order is important, check linker script for details.
    layout.lds
    multiboot/Header.cpp

    ${core_sources}

    ../ext/grub/include/multiboot.h

    multiboot/Boot_Device.cpp
    multiboot/Boot_Device.h
    multiboot/Drive.cpp
    multiboot/Drive.h
    multiboot/Information.cpp
    multiboot/Information.h
    multiboot/Memory_Region_Iterator.cpp
    multiboot/Memory_Region_Iterator.h
    vga/attribute.cpp
    vga/attribute.h
    vga/color.cpp
    vga/color.h
    vga/crt.cpp
    vga/crt.h
    vga/general.cpp
    vga/general.h
    vga/graphics.cpp
    vga/graphics.h
    vga/sequencer.cpp
    vga/sequencer.h
    vga/text_mode.cpp
    vga/text_mode.h
    Bit.h
    io.nasm
    io.h
    Log.cpp
    Memory.nasm
    Memory.cpp
    support.nasm
    support.cpp
    support.h
    System.nasm
    System.cpp)
