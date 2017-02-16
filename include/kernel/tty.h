#ifndef __TTY_H__
#define __TTY_H__

#include "kernel/io.h"

#include "stdint.h"
#include "string.h"


struct tty_driver_descriptor {
    uint8_t width;
    uint8_t height;
    uint8_t  cursor_x;
    uint8_t  cursor_y;
    uint16_t attribute;
    uint16_t *video_memory;
};


void init_driver_tty();
void driver_tty_clear_screen();
void driver_tty_update_cursor();
void driver_tty_output_char(char );
void driver_tty_output_string(char *);

#endif