#include "kernel/interrupt.h"




void init_interrupts() {
    _load_interrupt_descriptor_table();

    /* ICW1 - begin initialization PIC */
    write_port(PIC1_CMD_PORT, 0x11);
    write_port(PIC2_CMD_PORT, 0x11);
    /* ICW2 - remap offset address of IDT */
    write_port(PIC1_DATA_PORT, IRQ);
    write_port(PIC2_DATA_PORT, IRQ + 8);
    /* ICW3 - setup cascading */
    write_port(PIC1_DATA_PORT, 0x04);
    write_port(PIC2_DATA_PORT, 0x02);
    /* ICW4 - environment info */
    write_port(PIC1_DATA_PORT, 0x01);
    write_port(PIC2_DATA_PORT, 0x01);

    /* mask interrupts */
    write_port(PIC1_DATA_PORT, 0x0);
    write_port(PIC2_DATA_PORT, 0x0);

    __asm__("sti");
}



void _load_interrupt_descriptor_table() {
    uint32_t idt_size;

    struct {
        uint16_t number;
        uint32_t base;
    } __attribute__((packed)) _idt_pointer;

    idt_size = IDT_number * sizeof(struct interrupt_descriptor_table);

    memset(&_idt, 0, idt_size);

    _idt_pointer.number = idt_size - 1;
    _idt_pointer.base = (uint32_t)&_idt;

    __asm__ __volatile__(
        "lidt %0"
        :
        : "m" (_idt_pointer)
    );
}



void set_interrupt_handler(uint8_t index, uint32_t base, uint16_t selector, uint8_t type) {
    __asm__ __volatile__(
        "pushf \n\t"
        "cli"
    );

    _idt[index].lowerbits_0_15 = (uint16_t)(base & 0xFFFF);
    _idt[index].selector = selector;
    _idt[index].zero = 0x0;
    _idt[index].type = type;
    _idt[index].higherbits_16_31 = (uint16_t)(base >> 16);

    __asm__ __volatile__("popf");
}