#include <stdio.h>

void convert_base2r(int temp) {

    for (int r = 1; r <= 5; r++)
    {
        int n = temp;
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
        {
            printf("%c", result[i]);
        }
        printf("\n");
    }
}

int main() {
    int number;
    scanf("%d", &number);
    convert_base2r(number);
    return 0;
}
