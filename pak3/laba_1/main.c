#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char digits[] = "0123456789ABCDEF";

void convert_helper(unsigned int n, int bits, int mask) {
    if ((n >> bits) != 0) {
        convert_helper(n >> bits, bits, mask);
    }
    putchar(digits[n & mask]);
}

void convert_base2r(int n) {
    unsigned int un = (unsigned int)n;
    
    if (n == 0) {
        printf("0\n0\n0\n0\n0\n");
        return;
    }
    
    // r = 1
    {
        int bits = 1;
        int mask = (1 << bits) - 1;
        if (un >> bits) convert_helper(un >> bits, bits, mask);
        putchar(digits[un & mask]);
        putchar('\n');
    }
    
    // r = 2
    {
        int bits = 2;
        int mask = (1 << bits) - 1;
        if (un >> bits) convert_helper(un >> bits, bits, mask);
        putchar(digits[un & mask]);
        putchar('\n');
    }
    
    // r = 3
    {
        int bits = 3;
        int mask = (1 << bits) - 1;
        if (un >> bits) convert_helper(un >> bits, bits, mask);
        putchar(digits[un & mask]);
        putchar('\n');
    }
    
    // r = 4
    {
        int bits = 4;
        int mask = (1 << bits) - 1;
        if (un >> bits) convert_helper(un >> bits, bits, mask);
        putchar(digits[un & mask]);
        putchar('\n');
    }
    
    // r = 5
    {
        int bits = 5;
        int mask = (1 << bits) - 1;
        if (un >> bits) convert_helper(un >> bits, bits, mask);
        putchar(digits[un & mask]);
        putchar('\n');
    }
}

int main() {
    char input[256];
    long number;
    char *endptr;
    
    printf("Введите целое число: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    number = strtol(input, &endptr, 10);

    if (endptr == input) {
        fprintf(stderr, "Invalid number\n");
        return 1;
    }

    if (number > INT_MAX || number < INT_MIN) {
        fprintf(stderr, "Overflow\n");
        return 1;
    }
    
    convert_base2r((int)number);
    
    return 0;
}
