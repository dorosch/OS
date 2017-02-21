#include "kernel/drivers/timer.h"




static uint32_t __ticks = 0;

IRQ_HANDLER(timer_interrupt_handler) {
    __ticks++;
    if (__ticks % 18 == 0) {
        driver_tty_output_string("One second\n");
        __ticks = 0;
    }
}



void init_driver_timer() {
    set_interrupt_handler(IRQ + 0, (uint32_t)&timer_interrupt_handler, 0x08, 0x8E);
}