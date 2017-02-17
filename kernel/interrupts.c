#include "kernel/interrupts.h"




void init_interrupts() {
    _load_interrupt_descriptor_table();

    _register_all_interrupts_handler();

    /* ICW1 - begin initialization PIC */
    write_port(PIC1_CMD_PORT, 0x11);
    write_port(PIC2_CMD_PORT, 0x11);
    /* ICW2 - remap offset address of IDT */
    write_port(PIC1_DATA_PORT, IRQ_base);
    write_port(PIC2_DATA_PORT, IRQ_base + 8);
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

    _idt_pointer.number = idt_size - 1;
    _idt_pointer.base = (uint32_t)&_idt;

    memset(&_idt, 0, idt_size);

    __asm__ __volatile__(
        "lidt %0"
        :
        : "m" (_idt_pointer)
    );
}



void _register_all_interrupts_handler() {
    set_interrupt_handler(0x20, (uint32_t)&timer_int_handler, 0x08, 0x8E);
    set_interrupt_handler(0x21, (uint32_t)&keyboard_int_handler, 0x08, 0x8E);
}



void set_interrupt_handler(uint8_t index, uint32_t base, uint16_t selector, uint8_t type) {
    __asm__ __volatile__(
        "pushf \n\t"
        "cli"
        :
        :
    );

    _idt[index].lowerbits_0_15 = (uint16_t)(base & 0xFFFF);
    _idt[index].selector = selector;
    _idt[index].zero = 0x0;
    _idt[index].type = type;
    _idt[index].higherbits_16_31 = (uint16_t)(base >> 16);

    __asm__("popf");
}




IRQ_HANDLER(timer_int_handler) {
    (*((char*)(0xB8000 + 79 * 2)))++;
}



IRQ_HANDLER(keyboard_int_handler) {
    uint8_t status;
    uint8_t key_code;

    key_code = read_port(0x60);
    status = read_port(0x61);
    write_port(0x61, status | 1);

    driver_tty_output_char(key_code);
}