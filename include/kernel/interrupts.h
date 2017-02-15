#ifndef __IDT_H__
#define __IDT_H__

#include "kernel/io.h"

#include "stdint.h"


#define PIC1_CMD_PORT   0x20
#define PIC1_DATA_PORT  0x21

#define PIC2_CMD_PORT   0xA0
#define PIC2_DATA_PORT  0xA1

#define IDT_number      256


struct IDT_entry {
    uint16_t lowerbits_0_15;
    uint16_t selector;
    uint8_t zero;
    uint8_t type;
    uint16_t higherbits_16_31;
} __attribute__((packed));

struct IDT_pointer {
  uint16_t number;
  uint32_t base;
} __attribute__((packed));


void init_interrupts();
void set_entry_IDT(uint8_t , uint32_t , uint16_t , uint8_t );

#endif