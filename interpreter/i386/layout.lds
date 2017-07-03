ENTRY("_start")

SECTIONS {
    /* The Multiboot header must stay in the first 8 KiB of the final
       binary file so that Multiboot compliant boot loaders can find it. */
    .multiboot_header : {
        *(.multiboot_header)
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
}
