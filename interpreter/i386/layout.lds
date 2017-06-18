ENTRY("main")

SECTIONS {
    .rodata : {
        /* The Multiboot header must stay in the first 8 KiB of the final
           binary file so that Multiboot compliant boot loaders can find it. */
        *(.rodata .rdata)

        /* C++ static/global constructors list. */
        _cpp_ctors_begin = .;
        *(.ctor*)
        _cpp_ctors_end = .;
        
        /* Ditto for destructors. */
        _cpp_dtors_begin = .;
        *(.dtor*)
        _cpp_dtors_end = .;
    }
    
    .data : {
        *(.data)
    }
    
    .bss : {
        *(.bss)
    }
    
    .text : {
        *(.text)
    }
    
    /DISCARD/ : {
        *(.comment)
    }
}
