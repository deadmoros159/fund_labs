#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_DIGITS 1024

int char_to_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return -1;
}

char value_to_char(int v) {
    if (v < 10) return '0' + v;
    return 'A' + (v - 10);
}

void normalize_number(char *num) {
    int len = strlen(num);
    int is_negative = (num[0] == '-');
    int start = is_negative ? 1 : 0;
    
    while (num[start] == '0' && start < len - 1) {
        start++;
    }
    
    if (num[start] == '0' && (start == len - 1 || (is_negative && start == len - 1))) {
        num[0] = '0';
        num[1] = '\0';
        return;
    }
    
    if (start > (is_negative ? 1 : 0)) {
        int j = is_negative ? 1 : 0;
        for (int i = start; i < len; i++) {
            num[j++] = num[i];
        }
        num[j] = '\0';
    }
}

int compare_abs(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    
    if (len_a > len_b) return 1;
    if (len_a < len_b) return -1;
    
    for (int i = 0; i < len_a; i++) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    
    return 0;
}

void get_absolute(const char *num, char *abs_num) {
    if (num[0] == '-') {
        strcpy(abs_num, num + 1);
    } else {
        strcpy(abs_num, num);
    }
    normalize_number(abs_num);
}

int is_valid_number(const char *s, int base) {
    int start = (s[0] == '-') ? 1 : 0;
    for (int i = start; s[i] != '\0'; i++) {
        int digit_val = char_to_value(s[i]);
        if (digit_val < 0 || digit_val >= base) return 0;
    }
    return 1;
}

int divide_number(const char *num, int original_base, int divisor, char *quotient) {
    long long temp = 0;
    int len = strlen(num);
    int q_pos = 0;
    int has_started = 0;
    
    for (int i = 0; i < len; i++) {
        temp = temp * original_base + char_to_value(num[i]);
        if (temp >= divisor || has_started) {
            quotient[q_pos++] = value_to_char(temp / divisor);
            temp %= divisor;
            has_started = 1;
        }
    }
    
    if (q_pos == 0) {
        quotient[0] = '0';
        q_pos = 1;
    }
    
    quotient[q_pos] = '\0';
    return temp;
}

void convert_to_base(const char *num, int original_base, int new_base, char *result) {
    char temp[MAX_DIGITS];
    char abs_num[MAX_DIGITS];
    int is_negative = (num[0] == '-');
    
    get_absolute(num, abs_num);
    
    if (strcmp(abs_num, "0") == 0) {
        strcpy(result, "0");
        return;
    }
    
    char remainders[MAX_DIGITS];
    int rem_pos = 0;
    
    strcpy(temp, abs_num);
    while (strcmp(temp, "0") != 0) {
        int remainder = divide_number(temp, original_base, new_base, temp);
        remainders[rem_pos++] = value_to_char(remainder);
    }
    
    int pos = 0;
    if (is_negative) {
        result[pos++] = '-';
    }
    
    for (int i = rem_pos - 1; i >= 0; i--) {
        result[pos++] = remainders[i];
    }
    result[pos] = '\0';
}

void print_all_conversions(const char *max_number, int original_base) {
    char converted[MAX_DIGITS * 2];
    int bases[] = {9, 18, 27, 36};
    
    printf("Максимальное по модулю число в разных системах счисления:\n");
    printf("Основание %2d: %s\n", original_base, max_number);
    
    for (int i = 0; i < 4; i++) {
        convert_to_base(max_number, original_base, bases[i], converted);
        printf("Основание %2d: %s\n", bases[i], converted);
    }
}

int main() {
    int base;
    
    printf("Введите основание системы счисления (2-36): ");
    scanf("%d", &base);
    if (base < 2 || base > 36) {
        fprintf(stderr, "Ошибка: Основание должно быть от 2 до 36\n");
        return 1;
    }
    
    char input[MAX_DIGITS];
    char max_number[MAX_DIGITS] = "";
    char max_abs[MAX_DIGITS] = "";
    int first = 1;
    
    printf("Введите числа в системе с основанием %d :\n", base);
    
    while (1) {
        scanf("%s", input);
        if (strcmp(input, "Stop") == 0) break;
        
        if (strlen(input) > MAX_DIGITS) {
            fprintf(stderr, "Error to big nubmer\n");
            return 1;
        }
        
        if (!is_valid_number(input, base)) {
            fprintf(stderr, "Invalid input\n");
            return 1;
        }
        
        normalize_number(input);
        
        char current_abs[MAX_DIGITS];
        get_absolute(input, current_abs);
        
        if (first || compare_abs(current_abs, max_abs) > 0) {
            strcpy(max_number, input);
            strcpy(max_abs, current_abs);
            first = 0;
        }
    }
    
    if (first) {
        printf("Не было введено ни одного числа!\n");
        return 0;
    }
    
    print_all_conversions(max_number, base);
    
    return 0;
}
