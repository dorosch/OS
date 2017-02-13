#include "stdint.h"




void outb(uint16_t port, uint8_t value) {
    __asm__ __volatile__ (
        "outb %1, %0"
        :
        : "dN" (port)
        , "a" (value)
    );
}



uint8_t inb(uint16_t port) {
    uint8_t result;

    __asm__ __volatile__ (
        "inb %1, %0"
        : "=a" (result)
        : "dN" (port)
    );

    return result;
}