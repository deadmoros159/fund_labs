#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_N 1000000

int is_prime(int x)
{
    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void eratosfen(int* chisla, int size)
{
    int* p = &chisla[0];
    
    int right = pow(MAX_N, 0.5) + 1;
    int arr[MAX_N];
    arr[0] = 0;
    arr[1] = 0;

    for (int i = 2; i <= MAX_N; i++)
    {
        arr[i] = i;
    }

    for (int i = 2; i < right; i++)
    {
        if (is_prime(i))
        {
            for (int j = i + 1; j <= MAX_N; j++)
            {
                if (arr[j] % i == 0){
                    arr[j] = 0;
                }
            }
        }
    }

    int arr_simple[MAX_N];
    int size_arr_simple = 1;

    for (int i = 0; i < MAX_N; i++)
    {
        if (arr[i] != 0)
        {
            arr_simple[size_arr_simple] = arr[i];
            size_arr_simple++;
        }
    }
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", arr_simple[*p++]);
    }
}

int read_number_with_leading_zeros() {
    char input[256];
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }
    input[strcspn(input, "\n")] = '\0';

    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            return -1;  // Некорректный ввод
        }
    }

    int start = 0;
    while (input[start] == '0' && input[start + 1] != '\0') {
        start++;
    }
    if (input[start] == '\0') {
        return 0;
    }
    int len = strlen(input + start);
    if (len > 10) {
        return -2;  // Слишком длинное число
    }
    if (len == 10) {
        const char* max_int_str = "2147483647";
        for (int i = 0; i < 10; i++) {
            if (input[start + i] > max_int_str[i]) {
                return -2;
            } else if (input[start + i] < max_int_str[i]) {
                break;
            }
        }
    }
    return atoi(input);
}


int main()
{
    printf("Введите количество порядковых номеров простых чисел: ");
    int K = read_number_with_leading_zeros();

    if (K <= 0) {
        if (K == 0) {
            fprintf(stderr, "Число запросов должно быть положительным\n");
        } else if (K == -1) {
            fprintf(stderr, "Ошибка: введите положительное число\n");
        } else if (K == -2) {
            fprintf(stderr, "Слишком большое число\n");
        }
        return 1;
    }
    int* raspred = malloc(sizeof(int) * K);

    for (int i = 0; i < K; i++)
    {
        int res = read_number_with_leading_zeros();
        if (res <= 0) {
            if (res == 0) {
                fprintf(stderr, "Число должно быть положительным\n");
            } else if (res == -1) {
                fprintf(stderr, "Ошибка: введите положительное число\n");
            } else if (res == -2) {
                fprintf(stderr, "Слишком большое число\n");
            }
            return 1;
        }
        raspred[i] = res;
    }
    printf("Результаты:\n");
    eratosfen(raspred, K);
    free(raspred);
    return 0;
}
