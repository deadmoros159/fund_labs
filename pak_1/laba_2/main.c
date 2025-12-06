#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 500000

int is_prime(int x)
{
    for (int i = 2; i < x / 2; i++)
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
    
    int right = pow(MAX, 0.5) + 1;
    int arr[MAX];
    arr[0] = 0;
    arr[1] = 0;

    for (int i = 2; i <= MAX; i++)
    {
        arr[i] = i;
    }

    for (int i = 2; i < right; i++)
    {
        if (is_prime(i))
        {
            for (int j = i + 1; j <= MAX; j++)
            {
                if (arr[j] % i == 0){
                    arr[j] = 0;
                }
            }
        }
    }

    int arr_simple[MAX];
    int size_arr_simple = 1;

    for (int i = 0; i < MAX; i++)
    {
        if (arr[i] != 0)
        {
            arr_simple[size_arr_simple] = arr[i];
            size_arr_simple++;
        }
    }
    // for (int i = 0; i < 10; i++) printf("%d ", arr_simple[i]);
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", arr_simple[*p++]);
    }
}

int main()
{
    char k[100];
    fgets(k, sizeof(k), stdin);
    int size_k = 0;

    for (int i = 0; k[i] != '\0'; i++)
    {
        if (size_k > 10)
        {
            fprintf(stderr, "Input smaller number\n");
            return 1;
        }
        size_k++;
        if (isalpha(k[i]))
        {
            fprintf(stderr, "number cannot contain alpha\n");
            return 1;
        }
    }
    int a = atoi(k);

    int* raspred = malloc(sizeof(int) * a);

    for (int i = 0; i < a; i++)
    {
        

        char temp[100];
        fgets(temp, sizeof(temp), stdin);
        int size_temp = 0;

        for (int i = 0; temp[i] != '\0'; i++)
        {
            if (size_temp > 10)
            {
                fprintf(stderr, "Input smaller number\n");
                return 1;
            }
            size_temp++;
            if (isalpha(temp[i]))
            {
                fprintf(stderr, "number cannot contain alpha\n");
                return 1;
            }
        }
        int res = atoi(temp);
        raspred[i] = res;
    }

    eratosfen(raspred, a);
    free(raspred);
    return 0;
}
