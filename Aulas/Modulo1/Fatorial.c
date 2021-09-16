#include <stdio.h>
#include <stdlib.h>

long int fatorial(long int n) {
    if (n == 0) {
        return 1;
    }

    return n * fatorial(n-1);
}

int main(void) {

    int n;
    scanf("%d", &n);

    long int fn = fatorial(n);

    printf("Fatorial de %d = %ld\n", n, fn);
}