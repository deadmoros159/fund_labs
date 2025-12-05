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

// e
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

// Pi
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

// double gamma_limit(double epsilon)
// {
//     double m = 1.0;
//     double prev = 0.0;
//     double current;
    
//     do {
//         prev = current;
//         current = 0.0;
        
//         for (int k = 1; k <= m; k++) {
//             double comb = sochetanie(m, k);
//             current += comb * pow(-1, k) / k * log_factorial(k);
//         }
        
//         m++;
//     } while (fabs(current - prev) > epsilon && m < MAX_ITERS);
//     return current;
// }

// double gamma_series(double epsilon) {
//     double pi_val = pi_series(epsilon/10);
//     double sum = -pi_val*pi_val/6.0;
    
//     int k = 2;
//     double term;
    
//     do {
//         double floor_k = floor(k);
//         term = 1.0/(floor_k*floor_k) - 1.0/k;
//         sum += term;
//         k++;
//     } while (fabs(term) > epsilon && k < MAX_ITERS);
    
//     return sum;
// }
// ////

// long double gamma_limits(int m) {
//     long double sum = 0.0L;
//     long double C = 1.0L; /* C(m,0) = 1, но суммируем с k=1 */
//     for (int k = 1; k <= m; ++k) {
//         /* обновляем биномиальный коэффициент C = C(m,k) */
//         C = C * (long double)(m - k + 1) / (long double)k;
//         /* ln(k!) вычислим через lgamma: ln(k!) = lgamma(k+1) */
//         long double lnfact = lgamma((long double)k + 1.0L);
//         long double term = ((k % 2) ? -1.0L : 1.0L) * C * (lnfact / (long double)k);
//         sum += term;
//     }
//     return sum;
// }

// /* 2) Сумма вида: -pi^2/6 + sum_{k=2..N} (1/floor(sqrt(k))^2 - 1/k) */
// long double gamma_series_test(long long N) {
//     long double sum = 0.0L;
//     for (long long k = 2; k <= N; ++k) {
//         long long r = (long long)floor(sqrt((long double)k));
//         if (r < 1) r = 1;
//         long double a = 1.0L / ((long double)r * (long double)r); /* 1/(floor(sqrt(k)))^2 */
//         long double b = 1.0L / (long double)k;
//         sum += (a - b);
//     }
//     double PI = pi_limit(1e-10);
//     long double val = - (PI * PI) / 6.0L + sum;
//     return val;
// }

int main(int argc, char const *argv[])
{
    double x = e_limit(1e-10);
    printf("=====Test for e=====\n");
    printf("Test for limit: %.15f\n", e_limit(1e-10));
    printf("Test for series: %.15f\n", e_series(1e-10));
    printf("Test for uravnenie: %.15f\n", e_uravnenie(1e-10));

    printf("=====Test for pi=====\n");
    printf("Test for limit: %.15f\n", pi_limit(1e-10));
    printf("Test for series: %.15f\n", pi_series(1e-10));
    printf("Test for uravnenie: %.15f\n", pi_uravnenie(1e-10));

    printf("=====Test for ln2=====\n");
    printf("Test for limit: %.15f\n", ln2_limit(1e-10));
    printf("Test for series: %.15f\n", ln2_series(1e-10));
    printf("Test for uravnenie: %.15f\n", ln2_uravnenie(1e-10));

    printf("=====Test for sqrt2=====\n");
    printf("Test for limit: %.15f\n", sqrt2_limit(1e-10));
    printf("Test for series: %.15f\n", sqrt2_series(1e-10));
    printf("Test for uravnenie: %.15f\n", sqrt2_uravnenie(1e-10));

    // printf("=====Test for gamma=====\n");
    // printf("Test for limit: %.15Lg\n", gamma_limits(1e-10));
    // printf("Test for series: %.15Lg\n", gamma_series_test(1e-10));
    // printf("Test for uravnenie: %.15Lg\n", sqrt2_uravnenie(1e-10));
    return 0;
}
