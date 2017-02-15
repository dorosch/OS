#include "kernel/interrupts.h"




struct IDT_entry IDT_table[IDT_number];
struct IDT_pointer IDT_pointer;


void init_interrupts() {
    /*
    PIC1 - IRQ0-7  on 0x20
    PIC2 - IRQ8-15 on 0x28
    */
    uint8_t IRQ_base = 0x20;

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

    IDT_pointer.number = (sizeof(struct IDT_entry) * IDT_number) - 1;
    IDT_pointer.base = (uint32_t)&IDT_table;

    __asm__ __volatile__ (
        "lidt %0"
        :
        : "m" (IDT_pointer)
    );
}


void set_entry_IDT(uint8_t index, uint32_t base, uint16_t selector, uint8_t type) {
    __asm__ __volatile__ ("pushf\n\rcli\n\r" : : );

    IDT_table[index].lowerbits_0_15 = (base & 0xFFFF);
    IDT_table[index].selector = selector;
    IDT_table[index].zero = 0x0;
    IDT_table[index].type = type;
    IDT_table[index].higherbits_16_31 = base >> 16;

    __asm__ __volatile__ ("popf\n\r" : : );
}