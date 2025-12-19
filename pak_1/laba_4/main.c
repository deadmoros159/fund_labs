#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_ITERS 8000


double faq(double n)
{
    double result = 1.0;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

double sochetanie(int n, int k) {
    double result = 1.0;
    for (int i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i;
    }
    return result;
}

double log_factorial(int n) {
    double sum = 0.0;
    for (int i = 2; i <= n; i++) {
        sum += log(i);
    }
    return sum;
}

double e_limit(double epsilon)
{
    double n = 1;
    double prev = 0.0;
    double curr = pow(1.00 + 1.00/n, n);
    while (n < MAX_ITERS && fabs(curr - prev) > epsilon)
    {
        prev = curr;
        n += 1;
        curr = pow(1.00 + 1.00/n, n);
    }
    return curr;
}

double e_series(double epsilon)
{
    int n = 1;
    double summa = 1.00;
    double curr = 1;
    while (fabs(curr) > epsilon && n < MAX_ITERS)
    {
        curr /= n;
        n++;
        summa += curr;
    }
    return summa;
}

double e_uravnenie(double epsilon)
{
    double x_low = 2.0, x_high = 3.0;

    while (fabs(x_high - x_low) > epsilon)
    {
        double x_mid = (x_high + x_low) / 2.0;
        if (log(x_mid) > 1.0) x_high = x_mid;
        else x_low = x_mid;
    }
    return (x_low + x_high) / 2.0;
}

double pi_limit(double epsilon)
{
    int n = 1;
    double prev = 0.0;
    double curr = (pow(pow(2, n) * faq(n), 4)) / (n * pow(faq(2*n), 2));
    
    while (fabs(curr - prev) > epsilon && n < MAX_ITERS) {
        prev = curr;
        n += 1;
        curr = (pow(pow(2, n) * faq(n), 4)) / (n * pow(faq(2*n), 2));
    }
    return curr;
}

double pi_series(double epsilon)
{
    int n = 1;
    double summa = 0.00;
    double curr = 4 * ((pow(-1, n-1)) / (2*n - 1));
    while (fabs(curr) > epsilon && n < MAX_ITERS)
    {
        summa += curr;
        n += 1;
        curr = 4 * ((pow(-1, n-1)) / (2*n - 1));
    }
    return summa;
}

double pi_uravnenie(double epsilon) {
    double x_low = 3.0, x_high = 4.0;
    
    while (fabs(x_high - x_low) > epsilon) {
        double x_mid = (x_low + x_high) / 2.0;
        if (cos(x_mid) > -1.0) {
            x_low = x_mid;
        } else {
            x_high = x_mid;
        }
    }
    return (x_low + x_high) / 2.0;
}

double ln2_limit(double epsilon)
{
    int n = 1;
    double prev = 0.0;
    double curr = n * (pow(2.00, 1.00/n) - 1);
    
    while (fabs(curr - prev) > epsilon && n < MAX_ITERS) {
        prev = curr;
        n += 1;
        curr = n * (pow(2, 1.00/n) - 1);
    }
    return curr;
}

double ln2_series(double epsilon)
{
    int n = 1;
    double summa = 0.00;
    double temp = pow(-1.00, n-1.0) / n;
    while (n < MAX_ITERS && fabs(temp) > epsilon)
    {
        summa += temp;
        n += 1;
        temp = pow(-1.00, n-1) / n;
    }
    return summa;
}

double ln2_uravnenie(double epsilon)
{
    double x_low = 0.00;
    double x_high = 1.00;

    while (fabs(x_low - x_high) > epsilon)
    {
        double x_mid = (x_high + x_low) / 2.0;
        if (exp(x_mid) > 2.0) x_high = x_mid;
        else x_low = x_mid;
    }
    return (x_high + x_low) / 2.0;
}

double sqrt2_limit(double epsilon)
{
    int n = 1;
    double prev = -0.5;
    double curr = prev - (prev*prev/2.0) + 1;
    while (n < MAX_ITERS && fabs(curr - prev) > epsilon)
    {
        prev = curr;
        n += 1;
        curr = prev - (prev*prev/2.0) + 1;
    }
    return curr;
}

double sqrt2_series(double epsilon)
{
    double proizvedenie = 1.0;
    int k = 2;
    double curr = pow (2, pow(2, -k));
    while (fabs(curr) > epsilon && k < MAX_ITERS)
    {
        proizvedenie *= curr;
        k++;
        curr = pow (2, pow(2, -k));
    }
    return proizvedenie;
}

double sqrt2_uravnenie(double epsilon)
{
    double x_low = 1.00;
    double x_high = 2.00;
    while (fabs(x_low - x_high) > epsilon)
    {
        double x_mid = (x_low + x_high) / 2.0;
        if (x_mid * x_mid > 2) x_high = x_mid;
        else x_low = x_mid;
    }
    return (x_low + x_high) / 2.0;
}

double gamma_limit(double epsilon) {
    double H_n = 1.0;
    double prev = 0.0;
    double gamma = 1.0 - log(1.0);
    
    for (int n = 2; n <= MAX_ITERS; n++) {
        H_n += 1.0 / n;
        double new_gamma = H_n - log(n);
        
        if (fabs(new_gamma - gamma) < epsilon && n > 10) {
            return new_gamma;
        }
        gamma = new_gamma;
    }
    return gamma;
}

double gamma_series(double epsilon) {
    double sum = 0.0;
    double term;
    int n = 2;
    
    double prev_sum = 0.0;
    do {
        double zeta = 0.0;
        int m_terms = 100;
        for (int m = 1; m <= m_terms; m++) {
            zeta += 1.0 / pow(m, n);
        }
        
        term = (pow(-1.0, n) * (zeta - 1)) / n;
        sum += term;
        n++;
        
        if (n > 100) break;
    } while (fabs(sum - prev_sum) > epsilon);
    
    return 1.0 - sum;
}

double gamma_uravnenie(double epsilon) {
    double left = 0.5;
    double right = 0.6;
    double mid;
    
    for (int iter = 0; iter < 100; iter++) {
        mid = (left + right) / 2.0;
        
        double n = 1000.0;
        double product = 1.0;
        
        for (int k = 2; k <= n; k++) {
            product *= k / (k - 1.0);
        }
        
        double left_side = exp(-mid);
        double right_side = (log(n) / n) * product;
        
        if (left_side > right_side) {
            left = mid;
        } else {
            right = mid;
        }
        
        if (right - left < epsilon) {
            break;
        }
    }
    
    return (left + right) / 2.0;
}

int main(int argc, char const *argv[])
{
    printf("=====Test for e=====\n");
    printf("Test for limit: %.15f\n", e_limit(1e-10));
    printf("Test for series: %.15f\n", e_series(1e-10));
    printf("Test for uravnenie: %.15f\n", e_uravnenie(1e-10));

    printf("\n=====Test for pi=====\n");
    printf("Test for limit: %.15f\n", pi_limit(1e-10));
    printf("Test for series: %.15f\n", pi_series(1e-10));
    printf("Test for uravnenie: %.15f\n", pi_uravnenie(1e-10));

    printf("\n=====Test for ln2=====\n");
    printf("Test for limit: %.15f\n", ln2_limit(1e-10));
    printf("Test for series: %.15f\n", ln2_series(1e-10));
    printf("Test for uravnenie: %.15f\n", ln2_uravnenie(1e-10));

    printf("\n=====Test for sqrt2=====\n");
    printf("Test for limit: %.15f\n", sqrt2_limit(1e-10));
    printf("Test for series: %.15f\n", sqrt2_series(1e-10));
    printf("Test for uravnenie: %.15f\n", sqrt2_uravnenie(1e-10));

    printf("\n=====Test for gamma=====\n");
    printf("Test for limit: %.15f\n", gamma_limit(1e-8));
    printf("Test for series: %.15f\n", gamma_series(1e-8));
    printf("Test for uravnenie: %.15f\n", gamma_uravnenie(1e-8));
    
    return 0;
}
