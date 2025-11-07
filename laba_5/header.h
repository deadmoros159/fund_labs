#ifndef TEXT_FORMATTER_H
#define TEXT_FORMATTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    SUCCESS,
    ERROR_OPEN_FILE,
    ERROR_MEMORY,
    ERROR_INVALID_INPUT
} return_code;

return_code format_file(const char* input_path, const char* output_path);
return_code wrap_line(const char* line, FILE* output);

#endif
