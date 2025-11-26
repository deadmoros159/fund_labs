#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void deliteli(int x)
{
    for (int i = 1; i <= 100; i++)
    {
        if (x % i == 0) printf("%d ", i);
    }
    printf("\n");
}

int is_prime(int x)
{
    int prime = 1;
    for (int i = 2; i < x; i++)
    {
        if (x % i == 0) prime = 0;
    }
    return prime;
}

void summa(int x)
{
    int sum = 0;
    for (int i = 1; i <= x; i++)
    {
        sum += i;
    }
    printf("%d\n", sum);
}

void faqq(int x)
{
    int p = 1;
    for (int i = 1; i <= x; i++)
    {
        p *= i;
    }
    printf("%d\n", p);
}

int stepen(int a, int b)
{
    int res = a;
    for (int i = 1; i < b; i++)
    {
        res *= a;
    }
    return res;
}

void table_stepeni(int x)
{
    if (x > 10)
    {
        printf("x должен быть не больше 10;\n");
        return;
    }
    for (int i = 1; i <= 10; i++)
    {
        printf("\n");
        printf("For pokazatel = %d: ", i);
        for (int j = 1; j <= x; j++)
        {
            printf("%d ", stepen(i, j));
        }
        printf("\n");
    }
}

void digit_to_hex(int x)
{
    char temp_x = x;
    char arr[100];
    int size_arr = 0;
    while (temp_x > 16)
    {
        char ostatok = temp_x % 16;
        if (ostatok >= 10)
        {
            arr[size_arr] = 'A' + (ostatok - 10);
            size_arr++;
        }
        else
        {
            arr[size_arr] = '0' + ostatok;
            size_arr++;
        }
        temp_x /= 16;
    }
    
    if (temp_x >= 10)
    {
        arr[size_arr] = 'A' + (temp_x - 10);
        size_arr++;
    }
    else
    {
        arr[size_arr] = '0' + temp_x;
        size_arr++;
    }
    for (int i = size_arr - 1; i != -1; i--)
    {
        printf("%c ", arr[i]);
    }
    printf("\n");

}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Ошибка ввода\n");
        return 1;
    }
    char *flag = argv[2];
    if (*flag != '-' && *flag != '/')
    {
        printf("Неверный флаг\n");
        return 1;
    }
    int x = atoi(argv[1]);
    

    switch (flag[1])
    {
    case 'h':
        deliteli(x);
        break;
    case 'p':
        if (is_prime(x)) printf("%d is simple\n", x);
        else printf("%d is not simple\n", x);
        break;
    case 'a':
        summa(x);
        break;
    case 'f':
        faqq(x);
        break;
    case 'e':
        table_stepeni(x);
        break;
    case 's':
        digit_to_hex(x);
        break;

    default:
    printf("Неизвестный флаг\n");
        return 1;
    }
    return 0;
}

