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
        monitor[position+1] = 0x07;
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
        monitor[position+1] = 0x07;
        index = index + 1;
        position = position + 2;
    }
}




int kernel_main(void) {
    char *string = "Kernel say: 'Hello World!'\n";

    clear_display();
    write_string_on_display(string);


    while (1) {

    }

    return 0;
}
