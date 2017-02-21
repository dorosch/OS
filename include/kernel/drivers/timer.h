#ifndef __TIMER_H__
#define __TIMER_H__

#include "kernel/interrupt.h"

#include "stdint.h"


struct driver_timer_descriptor {
    uint32_t ticks;
    uint32_t seconds_at_start;

};


void init_driver_timer();
uint32_t driver_timer_seconds_at_start();
void driver_timer_sleep(uint32_t);

#endif