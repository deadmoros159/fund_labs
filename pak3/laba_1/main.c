#include <stdio.h>

void convert_base2r(int n, int r) {
    int bits = r;
    int base = 1 << r;
    int mask = base - 1;

    char result[200];
    int pos = 0;

    do {
        int digit = n & mask;
        n >>= bits;

        if (digit < 10)
            result[pos++] = '0' + digit;
        else
            result[pos++] = 'A' + (digit - 10);

    } while (n != 0);

    for (int i = pos - 1; i >= 0; i--)
        putchar(result[i]);
}

int main() {
    int number = 12345;

    printf("Число %d в различных основаниях:\n", number);

    for (int r = 1; r <= 5; r++) {
        printf("Основание 2^%d = %d : ", r, 1 << r);
        convert_base2r(number, r);
        printf("\n");
    }

    return 0;
}
