#ifndef __STRING_H__
#define __STRING_H__

#include "stddef.h"

/**
 * Prototypes of string functions
 */
int strlen(const char * );
void *memset(void *, int , size_t );
void *memset_word(void *, short , size_t );

#endif