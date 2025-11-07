#ifndef OVERPRINTF_H
#define OVERPRINTF_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

enum {
    CUSTOM_SUCCESS = 0,
    CUSTOM_ERROR_NULL_POINTER = 1,
    CUSTOM_ERROR_INVALID_BASE = 2,
    CUSTOM_ERROR_BUFFER_TOO_SMALL = 3,
    CUSTOM_ERROR_FORMAT = 4
};

int custom_fprintf(FILE* stream, const char* format, ...);
int custom_sprintf(char* str, const char* format, ...);

#endif
