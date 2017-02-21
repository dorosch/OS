#include "kernel/drivers/keyboard.h"




IRQ_HANDLER(keyboard_int_handler) {
    uint8_t status;
    uint8_t key_code;

    key_code = read_port(0x60);
    status = read_port(0x61);
    write_port(0x61, status | 1);

    driver_tty_output_char(key_code);
}



void init_driver_keyboard() {
    set_interrupt_handler(IRQ + 1, (uint32_t)&keyboard_int_handler, 0x08, 0x8E);
}