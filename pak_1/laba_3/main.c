#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define MAX_INT     1000000


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

void all_permutations(float eps_q, float a_q, float b_q, float c_q)
{
    if (a_q == 0.0 && b_q == 0.00 && c_q == 0.0)
    {
        printf("Infinity solutions\n");
        return;
    }



    is_uravnenie(eps_q, a_q, b_q ,c_q);
    is_uravnenie(eps_q, a_q, c_q ,b_q);
    is_uravnenie(eps_q, b_q, a_q ,c_q);
    is_uravnenie(eps_q, b_q, c_q ,a_q);
    is_uravnenie(eps_q, c_q, a_q ,b_q);
    is_uravnenie(eps_q, c_q, b_q ,a_q);
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
        if (argc != 4)
        {
            fprintf(stderr, "Invalid amount of variables!\n");
            return 1;
        }
        char* m_p_argv_1 = argv[2];
        int m_is_argv_1_number = 1;
        for (int i = 0; i < strlen(argv[2]); i++)
        {
            if (isalpha(*m_p_argv_1))
            {
                m_is_argv_1_number = 0;
                fprintf(stderr, "Only numbers!\n");
                return 1;
            }
            m_p_argv_1++;
        }
        char* m_p_argv_2 = argv[3];
        int m_is_argv_2_number = 1;
        for (int i = 0; i < strlen(argv[3]); i++)
        {
            if (isalpha(*m_p_argv_2))
            {
                m_is_argv_2_number = 0;
                fprintf(stderr, "Only numbers!\n");
                return 1;
            }
            m_p_argv_2++;
        }
        int a = atoi(argv[2]);
        int b = atoi(argv[3]);
        if (a > MAX_INT || b > MAX_INT)
        {
            fprintf(stderr, "Input lower number!\n");
            return 1;
        }
        if (is_kratno(a, b)) printf("%d is multiple to %d\n", a, b);
        else printf("%d is NOT multiple to %d\n", a, b);
        break;
    case 't':
        if (argc != 6)
        {
            fprintf(stderr, "Invalid amount of variables!\n");
            return 1;
        }
        char* t_p_argv_1 = argv[2];
        int t_is_argv_1_number = 1;
        for (int i = 0; i < strlen(argv[2]); i++)
        {
            if (isalpha(*t_p_argv_1))
            {
                t_is_argv_1_number = 0;
                fprintf(stderr, "Only numbers!\n");
                return 1;
            }
            t_p_argv_1++;
        }
        char* t_p_argv_2 = argv[3];
        int t_is_argv_2_number = 1;
        for (int i = 0; i < strlen(argv[3]); i++)
        {
            if (isalpha(*t_p_argv_2))
            {
                t_is_argv_2_number = 0;
                fprintf(stderr, "Only numbers!\n");
                return 1;
            }
            t_p_argv_2++;
        }

        char* t_p_argv_3 = argv[4];
        int t_is_argv_3_number = 1;
        for (int i = 0; i < strlen(argv[4]); i++)
        {
            if (isalpha(*t_p_argv_3))
            {
                t_is_argv_3_number = 0;
                fprintf(stderr, "Only numbers!\n");
                return 1;
            }
            t_p_argv_3++;
        }
        char* t_p_argv_4 = argv[5];
        int t_is_argv_4_number = 1;
        for (int i = 0; i < strlen(argv[5]); i++)
        {
            if (isalpha(*t_p_argv_4))
            {
                t_is_argv_4_number = 0;
                fprintf(stderr, "Only numbers!\n");
                return 1;
            }
            t_p_argv_4++;
        }
        float eps_t = atof(argv[2]);
        float x1 = atof(argv[3]);
        float x2 = atof(argv[4]);
        float x3 = atof(argv[5]);
        if (x1 > MAX_INT || x2 > MAX_INT || x3 > MAX_INT)
        {
            fprintf(stderr, "Input lower number!\n");
            return 1;
        }
        if (is_triangle(eps_t, x1, x2, x3))
        {
            printf("You can make triangel\n");
        }
        else printf("You can NOT make triangel\n");
        break;
    case 'q':
        if (argc != 6)
        {
            fprintf(stderr, "Invalid amount of variables!\n");
            return 1;
        }
        char* q_p_argv_1 = argv[2];
        int q_is_argv_1_number = 1;
        for (int i = 0; i < strlen(argv[2]); i++)
        {
            if (isalpha(*q_p_argv_1))
            {
                q_is_argv_1_number = 0;
                fprintf(stderr, "Only numbers!\n");
                return 1;
            }
            q_p_argv_1++;
        }
        char* q_p_argv_2 = argv[3];
        int q_is_argv_2_number = 1;
        for (int i = 0; i < strlen(argv[3]); i++)
        {
            if (isalpha(*q_p_argv_2))
            {
                q_is_argv_2_number = 0;
                fprintf(stderr, "Only numbers!\n");
                return 1;
            }
            q_p_argv_2++;
        }

        char* q_p_argv_3 = argv[4];
        int q_is_argv_3_number = 1;
        for (int i = 0; i < strlen(argv[4]); i++)
        {
            if (isalpha(*q_p_argv_3))
            {
                q_is_argv_3_number = 0;
                fprintf(stderr, "Only numbers!\n");
                return 1;
            }
            q_p_argv_3++;
        }
        char* q_p_argv_4 = argv[5];
        int q_is_argv_4_number = 1;
        for (int i = 0; i < strlen(argv[5]); i++)
        {
            if (isalpha(*q_p_argv_4))
            {
                q_is_argv_4_number = 0;
                fprintf(stderr, "Only numbers!\n");
                return 1;
            }
            q_p_argv_4++;
        }
        
        float eps_q = atof(argv[2]);
        float a_q = atof(argv[3]);
        float b_q = atof(argv[4]);
        float c_q = atof(argv[5]);
        if (a_q > MAX_INT || b_q > MAX_INT || c_q > MAX_INT)
        {
            fprintf(stderr, "Input lower number!\n");
            return 1;
        }
        all_permutations(eps_q, a_q, b_q ,c_q);
        break;
    default:
    printf("Invalid flag\n");
        break;
    }
    return 0;
}
