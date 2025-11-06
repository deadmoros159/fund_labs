#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdarg.h>

typedef enum return_code {
    OK,
    INVALID_INPUT,
    ERROR_OVERFLOW,
    ERROR_MEMORY
} return_code;

int gcd(int a, int b);
return_code is_finite(const int base, const double num, const double eps, int* const result);
return_code check_finite(const int base, const double eps, int* const results, const int count, ...);
