#ifndef __IDT_H__
#define __IDT_H__

#include "kernel/io.h"
#include "kernel/drivers/tty.h"

#include "stdint.h"
#include "string.h"


#define PIC1_CMD_PORT   0x20
#define PIC1_DATA_PORT  0x21
#define PIC2_CMD_PORT   0xA0
#define PIC2_DATA_PORT  0xA1

#define IDT_number      256

#define IRQ             0x20


struct interrupt_descriptor_table {
    uint16_t lowerbits_0_15;
    uint16_t selector;
    uint8_t zero;
    uint8_t type;
    uint16_t higherbits_16_31;
} __attribute__((packed));

extern struct interrupt_descriptor_table _idt[];


void init_interrupts();
void _load_interrupt_descriptor_table();
void set_interrupt_handler(uint8_t , uint32_t , uint16_t , uint8_t );




#define IRQ_HANDLER(name) void name(); \
    __asm__(#name ": pusha \n call _" #name " \n movb $0x20, %al \n outb %al, $0x20 \n outb %al, $0xA0 \n popa \n iret"); \
    void _ ## name()


#endif