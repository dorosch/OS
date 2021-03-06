#include "string.h"




/**
 * The function definition line length.
 *
 * Args:
 *     const char *string - pointer to the string to determine the length
 * Returns:
 *     int length - the length of the line
 */
int strlen(const char *string) {
    register const char *start = string;

    while (*start++) {
    }

    return --start - string;
}



void *memset(void *start, int symbol, size_t number) {
    unsigned char *pointer = start;

    while (number--) {
        *pointer++ = (unsigned char)symbol;
    }

    return start;
}



void *memset_word(void *start, short symbol, size_t number) {
    unsigned short *pointer = start;

    while (number--) {
        *pointer++ = (unsigned short)symbol;
    }

    return start;
}