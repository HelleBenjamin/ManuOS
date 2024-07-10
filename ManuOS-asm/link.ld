ENTRY(start)

SECTIONS
{
    /* Start the binary at address 0x8000 for the kernel */
    . = 0x8000;

    /* The .text section, which contains the code */
    .text :
    {
        *(.text)
    }

    /* The .data section, which contains initialized data */
    .data :
    {
        *(.data)
    }

    /* The .bss section, which contains uninitialized data */
    .bss :
    {
        *(.bss)
        *(COMMON)
    }


}
