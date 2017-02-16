#include "kernel/interrupts.h"
#include "kernel/tty.h"




int kernel_main(void) {
    init_interrupts();
    init_driver_tty();


    driver_tty_clear_screen();

    return 0;
}
