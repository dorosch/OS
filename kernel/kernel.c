#include "kernel/interrupt.h"
#include "kernel/drivers/tty.h"
#include "kernel/drivers/timer.h"
#include "kernel/drivers/keyboard.h"




int kernel_main(void) {
    init_interrupts();

    init_driver_tty();
    init_driver_timer();
    init_driver_keyboard();

    driver_tty_output_string("Kernel say: 'Hello world!'\n");

    return 0;
}
