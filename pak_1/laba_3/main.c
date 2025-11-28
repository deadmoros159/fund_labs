#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


void is_uravnenie(float epsilon, float a, float b, float c)
{
    float D = b*b - 4*a*c;
    if (D < epsilon && D < 0)
    {
        printf("Error: Has imaginary solution for a = %f, b = %f, c = %f\n", a, b, c);
        return;
    }
    if (D == epsilon)
    {
        printf("Has one solution for a = %f, b = %f, c = %f: x = %f\n", ((-b) / (4*a)), a, b, c);
        return;
    }
    float x1 = (-b + sqrt(D)) / (2*a);
    float x2 = (-b - sqrt(D)) / (2*a);
    if (fabs(x1 -x2) < epsilon)
    {
        printf("Has one solution for a = %f, b = %f, c = %f: x = %f\n", a, b, c, x1);
        return;
    }
    printf("Has two solutions for a = %f, b = %f, c = %f: x1 = %f , x2 = %f\n", a, b, c, x1 ,x2);
    return;

}

int comp(const void *a, const void *b) 
{
    return (*(int *)a - *(int *)b); 
} 

int is_triangle(float epsilon, float a, float b, float c)
{
    float arr[] = {a, b, c};
    qsort(arr, 3, sizeof(arr[0]), comp);
    float is_90 = arr[2]*arr[2] - (arr[1]*arr[1] + arr[0]*arr[0]);
    if (fabs(is_90) < epsilon) return 1;
    return 0;
}

int is_kratno(int x1, int x2)
{
    if (x1 == 0 || x2 == 0) return 0;
    if (x1 % x2 == 0)
    {
        return 1;
    }
    return 0;
}


int main(int argc, char *argv[])
{
    char* flag = argv[1];
    if (*flag != '-' && *flag != '/')
    {
        printf("Invalid initialization flag\n");
        return 1;
    }
    flag++;
    switch (*flag)
    {
    case 'm':
        int a = atoi(argv[2]);
        int b = atoi(argv[3]);
        if (is_kratno(a, b)) printf("%d is multiple to %d\n", a, b);
        else printf("%d is NOT multiple to %d\n", a, b);
        break;
    case 't':
        float eps_t = atof(argv[2]);
        float x1 = atof(argv[3]);
        float x2 = atof(argv[4]);
        float x3 = atof(argv[5]);
        if (is_triangle(eps_t, x1, x2, x3))
        {
            printf("You can make triangel\n");
        }
        else printf("You can NOT make triangel\n");
        break;
    case 'q':
        float eps_q = atof(argv[2]);
        float a_q = atof(argv[3]);
        float b_q = atof(argv[4]);
        float c_q = atof(argv[5]);
        is_uravnenie(eps_q, a_q, b_q ,c_q);
        is_uravnenie(eps_q, a_q, c_q ,b_q);
        is_uravnenie(eps_q, b_q, a_q ,c_q);
        is_uravnenie(eps_q, b_q, c_q ,a_q);
        is_uravnenie(eps_q, c_q, a_q ,b_q);
        is_uravnenie(eps_q, c_q, b_q ,a_q);
        break;
    default:
    printf("Invalid flag\n");
        break;
    }
    return 0;
}
