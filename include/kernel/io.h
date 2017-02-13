#ifndef __IO_H__
#define __IO_H__

#include "stdint.h"


void outb(uint16_t , uint8_t );
uint8_t inb(uint16_t );

#endif