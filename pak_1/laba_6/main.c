#include "func.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
    if (argc != 2){
        fprintf(stdout, "error: invalid arguments\n");
        return -1;
    }
    float epsilon = (float)atof(argv[1]);
    if (epsilon<0){
        fprintf(stderr, "error: invalid epsilon\n");
        return -1;
    }
    if (epsilon< 0.0000000000001){
        fprintf(stderr, "so small eps (max = 0.0000000000001)\n");
        return -1;
    }
    double result_a = integral(epsilon, 'a'), result_b = integral(epsilon, 'b'), result_c = integral(epsilon, 'c'), result_d = integral(epsilon, 'd');
    fprintf(stdout, "result (a): %f\nresult (b): %f\nresult (c): %f\nresult (d): %f\n", result_a, result_b, result_c, result_d);
    
}