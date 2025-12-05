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

    char s[200];
    long long max_value = 0;

    while (1) {
        scanf("%s", s);
        if (strcmp(s, "Stop") == 0)
            break;

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
