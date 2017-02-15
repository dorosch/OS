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