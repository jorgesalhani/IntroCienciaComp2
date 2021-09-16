#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long int fibonacci(long int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

long int fibonacci_iterativo(long int n) {
    long int F = 0;
    long int Ftemp = 1;

    for (int i = 1; i <= n; i++) {
        F += Ftemp;
        Ftemp = F - Ftemp;
    }

    return F;
}

int main(void) {

    int n;
    scanf("%d", &n);

    clock_t t0, t1;
    double time_diff;

    t0 = clock();
    long int fn = fibonacci(n);
    t1 = clock();
    time_diff = (t1 - t0)/(double)CLOCKS_PER_SEC;

    printf("Fibonacci(%d) = %ld em %lf seg\n", n, fn, time_diff);

    t0 = clock();
    long int fi = fibonacci_iterativo(n);
    t1 = clock();
    time_diff = (t1 - t0)/(double)CLOCKS_PER_SEC;

    printf("Fibonacci_iterativo(%d) = %ld em %lf seg\n", n, fi, time_diff);
}