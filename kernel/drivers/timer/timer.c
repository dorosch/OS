#include "kernel/drivers/timer.h"




static struct driver_timer_descriptor _timer;


IRQ_HANDLER(timer_interrupt_handler) {
    _timer.ticks++;

    if ((_timer.ticks % 18) == 0) {
        _timer.ticks = 0;
        _timer.seconds_at_start++;

        driver_tty_output_string("second\n");
    }
}



void init_driver_timer() {
    _timer.ticks = 0;
    _timer.seconds_at_start = 0;

    set_interrupt_handler(IRQ + 0, (uint32_t)&timer_interrupt_handler, 0x08, 0x8E);
}



uint32_t driver_timer_seconds_at_start() {
    return _timer.seconds_at_start;
}



void driver_timer_sleep(uint32_t seconds) {
    uint32_t end_ticks = _timer.seconds_at_start + seconds;

    do {

    } while (_timer.seconds_at_start < end_ticks);
}