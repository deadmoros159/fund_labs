#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

int char_to_digit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return -1;
}

int find_min_base(const char *num_str) {
    int max_digit = 1;
    int len = strlen(num_str);
    
    for (int i = 0; i < len; i++) {
        int digit = char_to_digit(num_str[i]);
        if (digit < 0) return -1;
        if (digit > max_digit) {
            max_digit = digit;
        }
    }
    
    return max_digit + 1;
}

int convert_to_decimal(const char *num_str, int base, int *overflow) {
    long long result = 0;
    int len = strlen(num_str);
    
    for (int i = 0; i < len; i++) {
        int digit = char_to_digit(num_str[i]);
        if (result > (LLONG_MAX - digit) / base) {
            *overflow = 1;
            return 0;
        }
        result = result * base + digit;
    }
    
    if (result > INT_MAX || result < INT_MIN) {
        *overflow = 1;
        return 0;
    }
    
    *overflow = 0;
    return (int)result;
}

void remove_leading_zeros(char *str) {
    int len = strlen(str);
    int first_non_zero = -1;
    
    for (int i = 0; i < len; i++) {
        if (str[i] != '0') {
            first_non_zero = i;
            break;
        }
    }
    
    if (first_non_zero == -1) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    
    if (first_non_zero > 0) {
        int new_len = len - first_non_zero;
        for (int i = 0; i < new_len; i++) {
            str[i] = str[i + first_non_zero];
        }
        str[new_len] = '\0';
    }
}

void process_numbers(FILE* input, FILE* output) {
    char buffer[256];
    int buffer_pos = 0;
    int in_number = 0;
    
    while (1) {
        int c = fgetc(input);
        
        if (c == EOF || c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            if (in_number && buffer_pos > 0) {
                buffer[buffer_pos] = '\0';
                
                char original[256];
                strcpy(original, buffer);
                remove_leading_zeros(buffer);
                
                int base = find_min_base(original);
                if (base < 2 || base > 36) {
                    fprintf(stderr, "Error: Invalid number '%s'\n", original);
                } else {
                    int overflow = 0;
                    int decimal = convert_to_decimal(original, base, &overflow);
                    
                    if (overflow) {
                        fprintf(output, "%s in min base: %d in decimal: Overflow\n", 
                                strlen(buffer) > 0 ? buffer : "0", base);
                    }
                    else {
                        fprintf(output, "%s in min base: %d in decimal: %d\n", 
                                strlen(buffer) > 0 ? buffer : "0", base, decimal);
                    }
                }
                
                buffer_pos = 0;
                in_number = 0;
            }
            
            if (c == EOF) break;
            continue;
        }
        
        if (isalnum(c)) {
            c = toupper(c);
            buffer[buffer_pos++] = c;
            in_number = 1;
            
            if (buffer_pos >= 255) {
                fprintf(output, "OVERFLOW buffer\n");
                fprintf(stderr, "OVERFLOW buffer\n");
                buffer[255] = '\0';
                buffer_pos = 255;
                return;
            }
        } else {
            if (in_number) {
                fprintf(stderr, "Error: Invalid char in num\n");
                buffer_pos = 0;
                in_number = 0;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid amount of input\n");
        return 1;
    }
    
    FILE* file_in = fopen(argv[1], "r");
    if (file_in == NULL) {
        fprintf(stderr, "Cannot open input file '%s'\n", argv[1]);
        return 1;
    }
    
    FILE* file_out = fopen(argv[2], "w");
    if (file_out == NULL) {
        fprintf(stderr, "Cannot open output file '%s'\n", argv[2]);
        fclose(file_in);
        return 1;
    }
    
    process_numbers(file_in, file_out);
    
    fclose(file_in);
    fclose(file_out);

    return 0;
}
