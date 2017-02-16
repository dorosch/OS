#include "kernel/tty.h"




static struct tty_driver_descriptor _tty;


void init_driver_tty() {
    _tty.width = 80;
    _tty.height = 25;
    _tty.cursor_x = 0;
    _tty.cursor_y = 0;
    _tty.attribute = 0x0f;
    _tty.video_memory = (uint16_t *)(0xB8000);

    driver_tty_clear_screen();
}



void driver_tty_clear_screen() {
    uint16_t size;
    uint16_t attribute;

    size = _tty.width * _tty.height;
    attribute = _tty.attribute << 8;

    memset_word(_tty.video_memory, attribute, size);

    _tty.cursor_x = 0;
    _tty.cursor_y = 0;

    driver_tty_update_cursor();
}




void driver_tty_update_cursor() {
    uint16_t location;

    location = (_tty.cursor_y * _tty.width) + _tty.cursor_x;

    write_port(0x3D4, 14);
    write_port(0x3D5, location >> 8);
    write_port(0x3D4, 15);
    write_port(0x3D5, location);
}



void driver_tty_output_char(char symbol) {
    uint16_t offset;
    uint16_t *location;
    uint16_t attribute = _tty.attribute << 8;

    if (symbol == '\n') {
        _tty.cursor_x = 0;
        _tty.cursor_y++;
    }
    else {
        offset = (_tty.cursor_y * _tty.width) + _tty.cursor_x;
        location = _tty.video_memory + offset;
        *location = symbol | attribute;
        _tty.cursor_x++;
    }

    driver_tty_update_cursor();
}



void driver_tty_output_string(char *string) {
    char *pointer;

    pointer = string;
    do {
        driver_tty_output_char(*pointer);
    } while (*pointer++);
}