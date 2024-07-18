ENTRY(_start)

SECTIONS
{
    /* Start the binary at address 0x8000 for the kernel, don't change */
    . = 0x8000;

    /* The .text section, which contains the code */
    .text :
    {
        *(.text)
    }

    /* The .data section, which contains initialized data, for example strings */
    .data :
    {
        *(.data)
    }

    /* The .bss section, which contains uninitialized data, for example buffers */
    .bss :
    {
        *(.bss)
        *(COMMON)
    }
}
