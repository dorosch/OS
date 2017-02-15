#include "kernel/interrupts.h"




/* Display color ; FG | BG */
/* Text color: */
#define BG_BLACK           0x00
#define BG_BLUE            0x01
#define BG_GREEN           0x02
#define BG_CYAN            0x03
#define BG_RED             0x04
#define BG_MAGENTA         0x05
#define BG_BROWN           0x06
#define BG_LIGHT_GRAY      0x07
#define BG_DARK_GREY       0x08
#define BG_LIGHT_BLUE      0x09
#define BG_LIGHT_GREEN     0x0a
#define BG_LIGHT_CYAN      0x0b
#define BG_LIGHT_RED       0x0c
#define BG_LIGHT_MAGENTA   0x0d
#define BG_LIGHT_BROWN     0x0e
#define BG_WHITE           0x0f

#define FG_BLACK           0x00
#define FG_BLUE            0x10
#define FG_GREEN           0x20
#define FG_CYAN            0x30
#define FG_RED             0x40
#define FG_MAGENTA         0x50
#define FG_BROWN           0x60
#define FG_LIGHT_GRAY      0x70
#define FG_DARK_GREY       0x80
#define FG_LIGHT_BLUE      0x90
#define FG_LIGHT_GREEN     0xa0
#define FG_LIGHT_CYAN      0xb0
#define FG_LIGHT_RED       0xc0
#define FG_LIGHT_MAGENTA   0xd0
#define FG_LIGHT_BROWN     0xe0
#define FG_WHITE           0xf0




void clear_display(void) {
    char *monitor;
    unsigned int position;
    unsigned int monitor_width;
    unsigned int monitor_height;

    position = 0;
    monitor_width = 80;
    monitor_height = 25;
    monitor = (char *)0xb8000;

    /* this loops clears the screen there are 25 lines each of 80 columns; */
    do {
        /* blank character */
        monitor[position] = ' ';
        /* attribute-byte - light grey on black screen */
        /*monitor[position+1] = 0x0f; */
        monitor[position+1] = BG_BLACK;
        /* each element takes 2 bytes */
        position = position + 2;
    } while (position < (monitor_width * monitor_height) * 2);
}



void write_string_on_display(char *string) {
    char *monitor;
    unsigned int index;
    unsigned int position;

    index = 0;
    position = 0;
    monitor = (char *)0xb8000;

    /* this loop writes the string to video memory */
    while (string[index] != '\0') {
        /* the character's ascii */
        monitor[position] = string[index];
        /* attribute-byte: give character black bg and light grey fg */
        monitor[position+1] = FG_LIGHT_GRAY | BG_BLACK;
        index = index + 1;
        position = position + 2;
    }
}





int kernel_main(void) {
    void init_interrupts();

    char *string = "Kernel say: 'Hello World!'";

    clear_display();
    write_string_on_display(string);

    return 0;
}
