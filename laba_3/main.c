#include "header.h"
#include <math.h>


static int add_to_buffer(char* buffer, size_t* written, size_t max_len, const char* str) {
    if (!buffer || !written || !str) return CUSTOM_ERROR_NULL_POINTER;
    
    size_t len = strlen(str);
    if (*written + len >= max_len) return CUSTOM_ERROR_BUFFER_TOO_SMALL;
    
    memcpy(buffer + *written, str, len);
    *written += len;
    buffer[*written] = '\0';
    return CUSTOM_SUCCESS;
}

// Римские цифры 

static void print_roman(int num, char* buffer, size_t* written) {
    if (num <= 0) {
        add_to_buffer(buffer, written, 1024, "0");
        return;
    }
    
    struct RomanDigit {
        int value;
        const char* symbol;
    };
    
    struct RomanDigit roman_numerals[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    
    int temp = num;
    char result[64] = {0};
    size_t pos = 0;
    
    for (size_t i = 0; i < sizeof(roman_numerals)/sizeof(roman_numerals[0]); i++) {
        while (temp >= roman_numerals[i].value) {
            const char* symbol = roman_numerals[i].symbol;
            size_t len = strlen(symbol);
            memcpy(result + pos, symbol, len);
            pos += len;
            temp -= roman_numerals[i].value;
        }
    }
    result[pos] = '\0';
    add_to_buffer(buffer, written, 1024, result);
}

// Целендорфово представление

static void print_zeckendorf(unsigned int num, char* buffer, size_t* written) {
    if (num == 0) {
        add_to_buffer(buffer, written, 1024, "01");
        return;
    }
    
    unsigned int fib[50] = {1, 2};
    int fib_count = 2;
    
    for (int i = 2; i < 50; i++) {
        fib[i] = fib[i-1] + fib[i-2];
        if (fib[i] > num) break;
        fib_count++;
    }
    
    char result[128] = {0};
    size_t pos = 0;
    unsigned int temp = num;
    
    for (int i = fib_count - 1; i >= 0; i--) {
        if (temp >= fib[i]) {
            result[pos++] = '1';
            temp -= fib[i];
        } else {
            result[pos++] = '0';
        }
    }
    
    result[pos++] = '1';
    result[pos] = '\0';
    
    add_to_buffer(buffer, written, 1024, result);
}

// Системы счисления

static void print_base_num(int num, int base, int uppercase, char* buffer, size_t* written) {
    if (base < 2 || base > 36) base = 10;
    
    char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char result[65] = {0};
    int pos = 64;
    result[pos] = '\0';
    
    int is_negative = num < 0;
    unsigned int n = is_negative ? -num : num;
    
    if (n == 0) {
        result[--pos] = '0';
    } else {
        while (n > 0) {
            result[--pos] = digits[n % base];
            n /= base;
        }
    }
    
    if (is_negative) {
        result[--pos] = '-';
    }
    
    if (uppercase) {
        for (int i = pos; result[i]; i++) {
            if (result[i] >= 'a' && result[i] <= 'z') {
                result[i] = result[i] - 'a' + 'A';
            }
        }
    }
    
    add_to_buffer(buffer, written, 1024, result + pos);
}

// Конвертация из строки

static int convert_from_base(const char* str, int base, int uppercase) {
    if (!str || base < 2 || base > 36) return 0;
    
    int result = 0;
    int sign = 1;
    const char* ptr = str;
    
    if (*ptr == '-') {
        sign = -1;
        ptr++;
    } else if (*ptr == '+') {
        ptr++;
    }
    
    while (*ptr) {
        char c = *ptr;
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'z') {
            digit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            break;
        }
        
        if (digit >= base) break;
        
        result = result * base + digit;
        ptr++;
    }
    
    return result * sign;
}

// Дамп памяти целых чисел

static void print_memory_dump_int(int num, char* buffer, size_t* written) {
    unsigned char* bytes = (unsigned char*)&num;
    char result[256] = {0};
    size_t pos = 0;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            result[pos++] = (bytes[i] & (1 << j)) ? '1' : '0';
        }
        if (i < 3) result[pos++] = ' ';
    }
    result[pos] = '\0';
    
    add_to_buffer(buffer, written, 1024, result);
}

static void print_memory_dump_unsigned(unsigned int num, char* buffer, size_t* written) {
    unsigned char* bytes = (unsigned char*)&num;
    char result[256] = {0};
    size_t pos = 0;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            result[pos++] = (bytes[i] & (1 << j)) ? '1' : '0';
        }
        if (i < 3) result[pos++] = ' ';
    }
    result[pos] = '\0';
    
    add_to_buffer(buffer, written, 1024, result);
}

// Дамп памяти вещественных чисел

static void print_memory_dump_double(double num, char* buffer, size_t* written) {
    unsigned char* bytes = (unsigned char*)&num;
    char result[512] = {0};
    size_t pos = 0;
    
    for (int i = 0; i < 8; i++) {
        for (int j = 7; j >= 0; j--) {
            result[pos++] = (bytes[i] & (1 << j)) ? '1' : '0';
        }
        if (i < 7) result[pos++] = ' ';
    }
    result[pos] = '\0';
    
    add_to_buffer(buffer, written, 1024, result);
}

static void print_memory_dump_float(float num, char* buffer, size_t* written) {
    unsigned char* bytes = (unsigned char*)&num;
    char result[256] = {0};
    size_t pos = 0;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            result[pos++] = (bytes[i] & (1 << j)) ? '1' : '0';
        }
        if (i < 3) result[pos++] = ' ';
    }
    result[pos] = '\0';
    
    add_to_buffer(buffer, written, 1024, result);
}

// Основные функции

int custom_fprintf(FILE* stream, const char* format, ...) {
    if (!stream || !format) return CUSTOM_ERROR_NULL_POINTER;
    
    va_list args;
    va_start(args, format);
    
    char buffer[1024] = {0};
    size_t written = 0;
    int status = CUSTOM_SUCCESS;
    
    while (*format && status == CUSTOM_SUCCESS) {
        if (*format != '%') {
            buffer[written++] = *format++;
            buffer[written] = '\0';
            continue;
        }
        
        format++;
        
        if (*format == 'R' && *(format + 1) == 'o') {
            int num = va_arg(args, int);
            print_roman(num, buffer, &written);
            format += 2;
        }
        else if (*format == 'Z' && *(format + 1) == 'r') {
            unsigned int num = va_arg(args, unsigned int);
            print_zeckendorf(num, buffer, &written);
            format += 2;
        }
        else if (*format == 'C' && *(format + 1) == 'v') {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            print_base_num(num, base, 0, buffer, &written);
            format += 2;
        }
        else if (*format == 'C' && *(format + 1) == 'V') {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            print_base_num(num, base, 1, buffer, &written);
            format += 2;
        }
        else if (*format == 't' && *(format + 1) == 'o') {
            char* str = va_arg(args, char*);
            int base = va_arg(args, int);
            int result = convert_from_base(str, base, 0);
            char temp[32];
            sprintf(temp, "%d", result);
            add_to_buffer(buffer, &written, 1024, temp);
            format += 2;
        }
        else if (*format == 'T' && *(format + 1) == 'O') {
            char* str = va_arg(args, char*);
            int base = va_arg(args, int);
            int result = convert_from_base(str, base, 1);
            char temp[32];
            sprintf(temp, "%d", result);
            add_to_buffer(buffer, &written, 1024, temp);
            format += 2;
        }
        else if (*format == 'm' && *(format + 1) == 'i') {
            int num = va_arg(args, int);
            print_memory_dump_int(num, buffer, &written);
            format += 2;
        }
        else if (*format == 'm' && *(format + 1) == 'u') {
            unsigned int num = va_arg(args, unsigned int);
            print_memory_dump_unsigned(num, buffer, &written);
            format += 2;
        }
        else if (*format == 'm' && *(format + 1) == 'd') {
            double num = va_arg(args, double);
            print_memory_dump_double(num, buffer, &written);
            format += 2;
        }
        else if (*format == 'm' && *(format + 1) == 'f') {
            float num = va_arg(args, double);
            print_memory_dump_float(num, buffer, &written);
            format += 2;
        }
        else {
            buffer[written++] = '%';
            if (*format != '\0') {
                buffer[written++] = *format++;
            }
            buffer[written] = '\0';
        }
    }
    
    if (status == CUSTOM_SUCCESS) {
        fprintf(stream, "%s", buffer);
    }
    
    va_end(args);
    return status;
}

int custom_sprintf(char* str, const char* format, ...) {
    if (!str || !format) return CUSTOM_ERROR_NULL_POINTER;
    
    va_list args;
    va_start(args, format);
    
    size_t written = 0;
    int status = CUSTOM_SUCCESS;
    
    while (*format && status == CUSTOM_SUCCESS) {
        if (*format != '%') {
            str[written++] = *format++;
            str[written] = '\0';
            continue;
        }
        
        format++;
        
        if (*format == 'R' && *(format + 1) == 'o') {
            int num = va_arg(args, int);
            print_roman(num, str, &written);
            format += 2;
        }
        else if (*format == 'Z' && *(format + 1) == 'r') {
            unsigned int num = va_arg(args, unsigned int);
            print_zeckendorf(num, str, &written);
            format += 2;
        }
        else if (*format == 'C' && *(format + 1) == 'v') {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            print_base_num(num, base, 0, str, &written);
            format += 2;
        }
        else if (*format == 'C' && *(format + 1) == 'V') {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            print_base_num(num, base, 1, str, &written);
            format += 2;
        }
        else if (*format == 't' && *(format + 1) == 'o') {
            char* str_arg = va_arg(args, char*);
            int base = va_arg(args, int);
            int result = convert_from_base(str_arg, base, 0);
            char temp[32];
            sprintf(temp, "%d", result);
            add_to_buffer(str, &written, 1024, temp);
            format += 2;
        }
        else if (*format == 'T' && *(format + 1) == 'O') {
            char* str_arg = va_arg(args, char*);
            int base = va_arg(args, int);
            int result = convert_from_base(str_arg, base, 1);
            char temp[32];
            sprintf(temp, "%d", result);
            add_to_buffer(str, &written, 1024, temp);
            format += 2;
        }
        else if (*format == 'm' && *(format + 1) == 'i') {
            int num = va_arg(args, int);
            print_memory_dump_int(num, str, &written);
            format += 2;
        }
        else if (*format == 'm' && *(format + 1) == 'u') {
            unsigned int num = va_arg(args, unsigned int);
            print_memory_dump_unsigned(num, str, &written);
            format += 2;
        }
        else if (*format == 'm' && *(format + 1) == 'd') {
            double num = va_arg(args, double);
            print_memory_dump_double(num, str, &written);
            format += 2;
        }
        else if (*format == 'm' && *(format + 1) == 'f') {
            float num = va_arg(args, double);
            print_memory_dump_float(num, str, &written);
            format += 2;
        }
        else {
            str[written++] = '%';
            if (*format != '\0') {
                str[written++] = *format++;
            }
            str[written] = '\0';
        }
    }
    
    va_end(args);
    return status;
}

// Тесты

int main() {
    printf("=== Testing custom fprintf and sprintf functions ===\n\n");
    
    printf("1. Roman numerals (%%Ro):\n");
    printf("   Result:   123 = ");
    custom_fprintf(stdout, "%Ro", 123);
    printf(", 49 = ");
    custom_fprintf(stdout, "%Ro", 49);
    printf(", 2023 = ");
    custom_fprintf(stdout, "%Ro", 2023);
    printf("\n");
    
    printf("\n2. Zeckendorf representation (%%Zr):\n");
    printf("   Result:   10 = ");
    custom_fprintf(stdout, "%Zr", 10);
    printf(", 20 = ");
    custom_fprintf(stdout, "%Zr", 20);
    printf(", 15 = ");
    custom_fprintf(stdout, "%Zr", 15);
    printf("\n");
    
    printf("\n3. Base conversion lowercase (%%Cv):\n");
    printf("   Result:   255 in base 16 = ");
    custom_fprintf(stdout, "%Cv", 255, 16);
    printf(", 42 in base 2 = ");
    custom_fprintf(stdout, "%Cv", 42, 2);
    printf("\n");
    
    printf("\n4. Base conversion uppercase (%%CV):\n");
    printf("   Result:   255 in base 16 = ");
    custom_fprintf(stdout, "%CV", 255, 16);
    printf(", 42 in base 2 = ");
    custom_fprintf(stdout, "%CV", 42, 2);
    printf("\n");
    
    printf("\n5. String to decimal lowercase (%%to):\n");
    printf("   Result:   \"ff\" from base 16 = ");
    custom_fprintf(stdout, "%to", "ff", 16);
    printf(", \"1010\" from base 2 = ");
    custom_fprintf(stdout, "%to", "1010", 2);
    printf("\n");
    
    printf("\n6. String to decimal uppercase (%%TO):\n");
    printf("   Result:   \"FF\" from base 16 = ");
    custom_fprintf(stdout, "%TO", "FF", 16);
    printf(", \"1010\" from base 2 = ");
    custom_fprintf(stdout, "%TO", "1010", 2);
    printf("\n");
    
    printf("\n7. Memory dump signed int (%%mi):\n");
    int test_int = 12345;
    printf("   %d = ", test_int);
    custom_fprintf(stdout, "%mi", test_int);
    printf("\n");
    
    printf("\n8. Memory dump unsigned int (%%mu):\n");
    unsigned int test_uint = 12345;
    printf("   %u = ", test_uint);
    custom_fprintf(stdout, "%mu", test_uint);
    printf("\n");
    
    printf("\n9. Memory dump double (%%md):\n");
    double test_double = 3.14159;
    printf("   %f = ", test_double);
    custom_fprintf(stdout, "%md", test_double);
    printf("\n");
    
    printf("\n10. Memory dump float (%%mf):\n");
    float test_float = 2.71828f;
    printf("   %f = ", test_float);
    custom_fprintf(stdout, "%mf", test_float);
    printf("\n");
    
    printf("\n11. Testing custom_sprintf:\n");
    char buffer[256];
    custom_sprintf(buffer, "Roman: %Ro, Base16: %Cv", 49, 255, 16);
    printf("   Result: %s\n", buffer);
    
    printf("\n12. Error:\n");
    int result = custom_fprintf(NULL, "test");
    printf("   NULL stream test: %s\n", result == CUSTOM_ERROR_NULL_POINTER ? "PASS" : "FAIL");
    
    printf("\nAll tests completed\n");
    
    return 0;
}
