#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAX_INT 1000000

static float g_sort_epsilon;

int is_number(const char *str) {
    if (*str == '-' || *str == '+') str++;
    
    int has_digit = 0;
    int has_dot = 0;
    
    while (*str) {
        if (isdigit(*str)) {
            has_digit = 1;
        } else if (*str == '.') {
            if (has_dot) return 0;
            has_dot = 1;
        } else {
            return 0;
        }
        str++;
    }
    return has_digit;
}

int float_compare(const void *a, const void *b) {
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    
    if (fabs(fa - fb) < g_sort_epsilon) {
        return 0;
    }
    return (fa > fb) ? 1 : -1;
}

int compare_floats(float a, float b, float epsilon) {
    return fabs(a - b) < epsilon;
}

void solve_equation(float epsilon, float a, float b, float c) {
    if (fabs(a) < epsilon) {
        if (fabs(b) < epsilon) {
            if (fabs(c) < epsilon) {
                printf("For a=%g, b=%g, c=%g: Infinite solutions\n", a, b, c);
            } else {
                printf("For a=%g, b=%g, c=%g: No solutions\n", a, b, c);
            }
        } else {
            float x = -c / b;
            printf("For a=%g, b=%g, c=%g: One linear solution x=%g\n", a, b, c, x);
        }
        return;
    }
    
    float D = b * b - 4 * a * c;
    
    if (D < -epsilon) {
        printf("For a=%g, b=%g, c=%g: No real solutions (D=%g)\n", a, b, c, D);
    } else if (fabs(D) < epsilon) {
        float x = -b / (2 * a);
        printf("For a=%g, b=%g, c=%g: One solution x=%g\n", a, b, c, x);
    } else {
        float sqrtD = sqrt(D);
        float x1 = (-b + sqrtD) / (2 * a);
        float x2 = (-b - sqrtD) / (2 * a);
        
        if (fabs(x1 - x2) < epsilon) {
            printf("For a=%g, b=%g, c=%g: One solution x=%g\n", a, b, c, x1);
        } else {
            printf("For a=%g, b=%g, c=%g: Two solutions x1=%g, x2=%g\n", a, b, c, x1, x2);
        }
    }
}

void process_all_permutations(float eps, float a, float b, float c) {
    printf("Processing all permutations with epsilon=%g:\n", eps);
    
    float coeffs[6][3] = {
        {a, b, c}, {a, c, b},
        {b, a, c}, {b, c, a},
        {c, a, b}, {c, b, a}
    };
    
    int printed[6] = {0};
    
    for (int i = 0; i < 6; i++) {
        if (printed[i]) continue;
        
        for (int j = i + 1; j < 6; j++) {
            if (compare_floats(coeffs[i][0], coeffs[j][0], eps) &&
                compare_floats(coeffs[i][1], coeffs[j][1], eps) &&
                compare_floats(coeffs[i][2], coeffs[j][2], eps)) {
                printed[j] = 1;
            }
        }
        
        if (!printed[i]) {
            solve_equation(eps, coeffs[i][0], coeffs[i][1], coeffs[i][2]);
        }
    }
}

int is_right_triangle(float epsilon, float a, float b, float c) {
    if (a <= 0 || b <= 0 || c <= 0) return 0;
    
    g_sort_epsilon = epsilon;
    
    float sides[3] = {a, b, c};
    qsort(sides, 3, sizeof(float), float_compare);
    
    float diff = fabs(sides[2] * sides[2] - (sides[1] * sides[1] + sides[0] * sides[0]));
    return diff < epsilon;
}

int is_multiple(int x1, int x2) {
    if (x1 == 0 || x2 == 0) {
        fprintf(stderr, "Numbers must be non-zero\n");
        return 0;
    }
    return (x1 % x2 == 0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Invalid usage\n");
        return 1;
    }
    
    char *flag = argv[1];
    if ((flag[0] != '-' && flag[0] != '/') || flag[1] == '\0') {
        fprintf(stderr, "Invalid flag format\n");
        return 1;
    }
    
    char flag_char = flag[1];
    
    switch (flag_char) {
        case 'm': {
            if (argc != 4) {
                fprintf(stderr, "Usage: %s -m int int\n", argv[0]);
                return 1;
            }
            
            for (int i = 2; i < 4; i++) {
                char* endptr;
                long val = strtol(argv[i], &endptr, 10);
                if (*endptr != '\0' || argv[i][0] == '\0') {
                    fprintf(stderr, "Number is not a integer\n");
                    return 1;
                }
                if (val == 0) {
                    fprintf(stderr, "Numbers cannot be zeros\n");
                    return 1;
                }
            }
            
            int a = atoi(argv[2]);
            int b = atoi(argv[3]);
            
            if (is_multiple(a, b)) {
                printf("%d is multiple of %d\n", a, b);
            } else {
                printf("%d is NOT multiple of %d\n", a, b);
            }
            break;
        }
        
        case 't': {
            if (argc != 6) {
                fprintf(stderr, "Usage: %s -t epsilon float float float\n", argv[0]);
                return 1;
            }
            
            for (int i = 2; i < 6; i++) {
                if (!is_number(argv[i])) {
                    fprintf(stderr, "Argument is not a number\n");
                    return 1;
                }
            }
            
            float epsilon = atof(argv[2]);
            if (epsilon <= 0) {
                fprintf(stderr, "Epsilon must be positive\n");
                return 1;
            }
            
            float sides[3];
            for (int i = 0; i < 3; i++) {
                sides[i] = atof(argv[3 + i]);
                if (sides[i] <= 0) {
                    printf("Must be positive numbers\n");
                    return 1;
                }
            }
            
            if (is_right_triangle(epsilon, sides[0], sides[1], sides[2])) {
                printf("The numbers can form a right triangle\n");
            } else {
                printf("The numbers CANNOT form a right triangle\n");
            }
            break;
        }
        
        case 'q': {
            if (argc != 6) {
                fprintf(stderr, "Usage: %s -q epsilon float float float\n", argv[0]);
                return 1;
            }
            
            for (int i = 2; i < 6; i++) {
                if (!is_number(argv[i])) {
                    fprintf(stderr, "Argument is not a number\n");
                    return 1;
                }
            }
            
            float epsilon = atof(argv[2]);
            if (epsilon <= 0) {
                fprintf(stderr, "Epsilon must be positive\n");
                return 1;
            }
            
            float coeffs[3];
            for (int i = 0; i < 3; i++) {
                coeffs[i] = atof(argv[3 + i]);
            }
            
            process_all_permutations(epsilon, coeffs[0], coeffs[1], coeffs[2]);
            break;
        }
        
        default:
            fprintf(stderr, "Unknown flag: \n");
            return 1;
    }
    
    return 0;
}
