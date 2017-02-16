#include "kernel/interrupts.h"




struct IDT_entry IDT_table[IDT_number];
struct IDT_pointer IDT_pointer;


IRQ_HANDLER(timer_int_handler) {
    (*((char*)(0xB8000 + 79 * 2)))++;
}


IRQ_HANDLER(keyboard_int_handler) {
    uint8_t key_code;
    uint8_t status;

    key_code = read_port(0x60);
    status = read_port(0x61);
    write_port(0x61, status | 1);

    driver_tty_output_char(key_code);
}



void init_interrupts() {
    load_IDT();

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

    set_entry_IDT(0x20, (uint32_t)&timer_int_handler, 0x08, 0x8E);
    set_entry_IDT(0x21, (uint32_t)&keyboard_int_handler, 0x08, 0x8E);

    /*  */
    __asm__("sti");
}



void load_IDT() {
    uint16_t IDT_size = IDT_number * sizeof(struct IDT_entry);

    memset(IDT_table, 0, IDT_size);

    IDT_pointer.number = IDT_size - 1;
    IDT_pointer.base = (uint32_t)&IDT_table;

    __asm__ (
        "lidt %0"
        :
        : "m" (IDT_pointer)
    );
}



void set_entry_IDT(uint8_t index, uint32_t base, uint16_t selector, uint8_t type) {
    __asm__("pushf");
    __asm__("cli");

    IDT_table[index].lowerbits_0_15 = (uint16_t)(base & 0xFFFF);
    IDT_table[index].selector = selector;
    IDT_table[index].zero = 0x0;
    IDT_table[index].type = type;
    IDT_table[index].higherbits_16_31 = (uint16_t)(base >> 16);

    __asm__("popf");
}