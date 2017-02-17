/**
 * This is the main kernel loader file.
 */



/* We tell GRUB that the kernel uses a multiboot mechanism: */
    /**
     * All load modules are loaded with the operating system and
     * should be aligned with the boundary of 4 KB page.
     */
.set BOOT_FLAGS, 0x00000001

    /**
     * Finding that "magic number" bootloader understands that
     * the kernel supports multiboot.
     */
.set BOOT_MAGIC_NUMBER, 0x1BADB002

    /**
     * Header checksum must be such that she was giving a zero sum.
     * It is calculated as: CHECKSUM = . -("magic number" + flags)
     */
.set CHECKSUM,     -(BOOT_MAGIC_NUMBER + BOOT_FLAGS)



/**
 * Indicates that the main function of the kernel is located in
 * a different place.
 */
.extern kernel_main



/* Section multiboot header: */
.section .mboot
    .int BOOT_MAGIC_NUMBER
    .int BOOT_FLAGS
    .int CHECKSUM



/* Start of code section: */
.section .text
    /* We make a point of entry available to the linker (ld). */
    .global     init



/* The main entry point: */
init:
    push    %ebx         /* Put the stack pointer to multiboot-structure. */

    cli                  /* Enable all system interrupts. */
    call    kernel_main  /* Call the main function of the kernel */

loop:
    jmp loop