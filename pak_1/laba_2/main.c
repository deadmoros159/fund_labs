#include <stdio.h>
#include <math.h>


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

int n_prime(int x)
{
    if (x < 0)
    {
        printf("Invalid index\n");
        return -1;
    }

    if (x == 0)
    {
        return 2;
    }

    int count = 1;
    int i = 3;
    while(count <= x)
    {
        if (is_prime(i))
        {
            if (x == count)
            {
                return i;
            }
        }
        i += 2;
        count++;
    }
    return -1;
}


int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    for (int i = 1; i < T + 1; i++)
    {
        printf("Input %d digit: ", i);
        int n;
        scanf("%d", &n);
        printf("Result: %d\n", n_prime(n));
    }
    return 0;
}
