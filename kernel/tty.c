#include "kernel/tty.h"




struct tty_driver_descriptor __tty_driver;


void init_driver_tty() {
    uint8_t cursor_x;
    uint8_t cursor_y;

    cursor_x = *((uint8_t *)0x451);
    cursor_y = *((uint8_t *)0x450);

    __tty_driver.tty = (uint16_t *)0xB8000;
    __tty_driver.port = *((uint16_t *)0x463);
    __tty_driver.attribute = FG_WHITE | BG_BLACK;
    __tty_driver.width = *((uint16_t *)0x44A);
    __tty_driver.height = 25;
    __tty_driver.cursor = (cursor_x * __tty_driver.width) + cursor_y;
}



void driver_tty_clear_screen() {
    uint32_t size;
    uint16_t attribute;

    attribute = (__tty_driver.attribute << 8) + ' ';
    size = __tty_driver.width * __tty_driver.height;

    memset_word(__tty_driver.tty, attribute, size);
    /* driver_tty_move_cursor_to(0); */
}



void driver_tty_output_char(char symbol) {
    __tty_driver.tty[__tty_driver.cursor++] = symbol;
    __tty_driver.tty[__tty_driver.cursor++] = __tty_driver.attribute;
}



void driver_tty_output_string(char *string) {
    char *pointer;

    pointer = string;
    do {
        driver_tty_output_char(*pointer);
    } while (*pointer++);
}