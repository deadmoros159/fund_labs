#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double trapezoidal_integral(double (*f)(double), double a, double b, double epsilon) {
    int n = 1;
    double h = b - a;
    double prev_result = 0.5 * (f(a) + f(b)) * h;
    double result;
    int max_iterations = 100000;
    
    for (int i = 0; i < max_iterations; i++) {
        n *= 2;
        h = (b - a) / n;
        
        double sum = 0.0;
        for (int k = 1; k < n; k += 2) {
            sum += f(a + k * h);
        }
        
        result = 0.5 * prev_result + h * sum;
        
        if (fabs(result - prev_result) < epsilon) {
            return result;
        }
        
        prev_result = result;
    }
    
    return result;
}

double func_a(double x) {
    if (fabs(x) < 1e-12) {
        return 1.0;
    }
    return log(1.0 + x) / x;
}

double func_b(double x) {
    return exp(-x * x / 2.0);
}

double func_c(double x) {
    if (fabs(1.0 - x) < 1e-12) {
        return 0.0;
    }
    return log(1.0 / (1.0 - x));
}

double func_d(double x) {
    if (fabs(x) < 1e-12) {
        return 1.0;
    }
    return pow(x, x);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid amount of argc\n");
        return 1;
    }
    
    double epsilon = atof(argv[1]);
    
    if (epsilon <= 0) {
        fprintf(stderr, "Epsilon be possitve\n");
        return 1;
    }
    
    printf("a. f ln(1+x)/x dx = %.10f\n", 
           trapezoidal_integral(func_a, 0.0, 1.0, epsilon));
    
    printf("b. f e^(-x²/2) dx = %.10f\n", 
           trapezoidal_integral(func_b, 0.0, 1.0, epsilon));
    
    printf("c. f ln(1/(1-x)) dx = %.10f\n", 
           trapezoidal_integral(func_c, 0.0, 1.0, epsilon));
    
    printf("d. f x^x dx = %.10f\n", 
           trapezoidal_integral(func_d, 0.0, 1.0, epsilon));
    
    return 0;
}
