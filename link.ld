/**
 * Just because you can not compile the kernel. You must collect a special
 * kind of executable code aligned on the border in 4Kb pages. This is
 * done if you specify linker linking rules.
 */



/* The entry point to the kernel source code: */
ENTRY (init)


SECTIONS
{
    /* The address from which the code will start in kernel memory: */
    . = 0x00100000;


    /* Code section: */
    .text ALIGN (0x1000) :
    {
        *(.mboot)
        *(.text)
    }


    /* Section initialized data: */
    .data ALIGN (0x1000) :
    {
        *(.data)
    }


    /* Section uninitialized data: */
    .bss :
    {
        *(.bss)
    }


    /* Location in memory where there is no kernel code: */
    end = .;
    _end = .;
    __end = .;
}
