#ifndef __IO_H__
#define __IO_H__

#include "stdint.h"


void write_port(uint16_t , uint8_t );
uint8_t read_port(uint16_t );

#endif