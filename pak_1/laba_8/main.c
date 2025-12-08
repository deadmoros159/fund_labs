#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

long long char_to_value(char c) {
    if (isdigit(c)) return c - '0';
    return c - 'A' + 10;
}

char value_to_char(int v) {
    if (v < 10) return '0' + v;
    return 'A' + (v - 10);
}

long long convert_to_decimal(const char *s, int base) {
    int len = strlen(s);
    int neg = (s[0] == '-');
    long long val = 0;

    for (int i = neg; i < len; i++) {
        val = val * base + char_to_value(s[i]);
    }

    return neg ? -val : val;
}

void convert_from_decimal(long long n, int base, char *out) {
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    int neg = (n < 0);
    if (neg) n = -n;

    char buf[100];
    int pos = 0;

    while (n > 0) {
        buf[pos++] = value_to_char(n % base);
        n /= base;
    }

    if (neg) buf[pos++] = '-';

    for (int i = 0; i < pos; i++)
        out[i] = buf[pos - 1 - i];
    out[pos] = '\0';
}

int main()
{
    int base;
    scanf("%d", &base);
    if (base > 36 || base < 2 || isalpha(base))
    {
        fprintf(stderr, "Invalid input for base!\n");
        return 1;
    }

    char s[200];
    long long max_value = 0;

    char all_nums[37] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J','K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T','U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    char current_nums[base];
    for (int i = 0; i < base; i++) current_nums[i] = all_nums[i];

    while (1)
    {
        scanf("%s", s);
        char check_for_stop[100];
        char* p = &s[0];
        if (*p == 'S' && *(p+1) == 't' && *(p+2) == 'o' && *(p+3) == 'p') break;

        for (; *p != '\0'; p++)
        {
            int correct_digit = 0;
            for (int j = 0; j < strlen(current_nums); j++)
            {
                if (*p == current_nums[j])
                {
                    correct_digit = 1;
                    break;
                }
            }
            if (!correct_digit)
            {
                fprintf(stderr, "Number cannot contain digits higher than %d\n", base);
                return 1;
            }
        }



        long long val = convert_to_decimal(s, base);

        if (llabs(val) > llabs(max_value)) {
            max_value = val;
        }
    }

    printf("Max value in deciaml: %lld\n", max_value);

    int targets[] = {9, 18, 27, 36};
    char out[200];

    for (int i = 0; i < 4; i++) {
        convert_from_decimal(max_value, targets[i], out);
        printf("%lld in base %d is: %s\n",max_value, targets[i], out);
    }

    return 0;
}
