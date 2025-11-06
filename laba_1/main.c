#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdarg.h>
#include "header.h"

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

return_code is_finite(const int base, const double num, const double eps, int* const result) {
    if (result == NULL) {
        return INVALID_INPUT;
    }
    
    if (base < 2 || base > 36) {
        return INVALID_INPUT;
    }
    
    if (num <= 0.0 || num >= 1.0) {
        return INVALID_INPUT;
    }
    
    const long long max_denom = 1000000000LL;
    long long nume, denom;
    
    double current = num;
    long long a = 0, b = 1;
    long long c = 1, d = 1;
    int found = 0;
    
    while (b <= max_denom && d <= max_denom && !found) {
        long long med_n = a + c;
        long long med_d = b + d;
        
        if (med_d > max_denom) break;
        
        double med = (double)med_n / med_d;
        
        if (fabs(current - med) < eps) {
            nume = med_n;
            denom = med_d;
            found = 1;
            break;
        }
        
        if (med < current) {
            a = med_n;
            b = med_d;
        } else {
            c = med_n;
            d = med_d;
        }
    }
    
    if (!found) {
        denom = max_denom;
        nume = (long long)(num * denom + 0.5);
    }
    
    int div = gcd(nume, denom);
    nume /= div;
    denom /= div;
    
    int temp_base = base;
    int temp_denom = denom;
    int finite = 1;
    
    for (int p = 2; p <= temp_denom && p <= temp_base; p++) {
        if (temp_denom % p == 0) {
            int is_div = (temp_base % p == 0) ? 1 : 0;
            
            if (!is_div) {
                finite = 0;
                break;
            }
            
            while (temp_denom % p == 0) {
                temp_denom /= p;
            }
        }
    }
    
    if (temp_denom > 1) {
        int temp = temp_base;
        int is_div = 0;
        for (int p = 2; p <= temp; p++) {
            if (temp % p == 0 && temp_denom % p == 0) {
                is_div = 1;
                break;
            }
        }
        if (!is_div) {
            finite = 0;
        }
    }
    
    *result = finite;
    return OK;
}

return_code check_finite(const int base, const double eps, int* const results, const int count, ...) {
    if (results == NULL) {
        return INVALID_INPUT;
    }
    
    if (count <= 0) {
        return INVALID_INPUT;
    }
    
    if (base < 2) {
        return INVALID_INPUT;
    }
    
    va_list args;
    va_start(args, count);
    
    for (int i = 0; i < count; i++) {
        double num = va_arg(args, double);
        return_code rc = is_finite(base, num, eps, &results[i]);
        if (rc != OK) {
            va_end(args);
            return rc;
        }
    }
    
    va_end(args);
    return OK;
}

int main() {
    int results[5];
    
    printf("TEST 1: Base 10\n");
    check_finite(10, 1e-10, results, 5, 
        0.5, 
        0.25,  
        0.2,
        0.1,
        1.0/3.0
    );
    for (int i = 0; i < 5; i++) {
        printf("Result %d: %s\n", i, results[i] ? "finite" : "infinite");
    }
    printf("\n");

    printf("TEST 2: Base 2\n");
    int results2[4];
    check_finite(2, 1e-10, results2, 4,
        0.5,
        0.25,
        0.125,
        0.1
    );
    for (int i = 0; i < 4; i++) {
        printf("Result %d: %s\n", i, results2[i] ? "finite" : "infinite");
    }
    printf("\n");

    printf("TEST 3: Base 8\n");
    int results3[4];
    check_finite(8, 1e-10, results3, 4,
        0.125,
        0.25,
        0.5,
        1.0/3.0
    );
    for (int i = 0; i < 4; i++) {
        printf("Result %d: %s\n", i, results3[i] ? "finite" : "infinite");
    }
    printf("\n");

    printf("TEST 4: Base 16\n");
    int results4[5];
    check_finite(16, 1e-10, results4, 5,
        0.0625,
        0.125,
        0.25,
        0.5,
        0.1
    );
    for (int i = 0; i < 5; i++) {
        printf("Result %d: %s\n", i, results4[i] ? "finite" : "infinite");
    }
    printf("\n");

    printf("TEST 5: Base 3\n");
    int results5[4];
    check_finite(3, 1e-10, results5, 4,
        1.0/3.0, 
        1.0/9.0, 
        0.5, 
        0.25
    );
    for (int i = 0; i < 4; i++) {
        printf("Result %d: %s\n", i, results5[i] ? "finite" : "infinite");
    }
    
    return 0;
}
