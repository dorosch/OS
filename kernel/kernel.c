#include "kernel/tty.h"
#include "kernel/interrupts.h"




int kernel_main(void) {
    init_interrupts();
    init_driver_tty();

    driver_tty_output_string("Kernel say: 'Hello world!'\n");

    return 0;
}
