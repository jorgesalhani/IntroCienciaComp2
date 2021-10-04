#include <stdio.h>
#include <stdlib.h>

long int fatorial(long int n) {
                                    // Contagem de operacoes: 
                                    // a = atribuicao, 
                                    // c = comparacao,
                                    // o = operacao aritmetica,
                                    //
                                    // Caso n = 3
                                    //
                                    // | n=3    | n=2   | n=1   | n=0
    if (n == 0) {                   // | c      | c     | c     | c
        return 1;                   // |        |       |       | 
    }                           
    return n * fatorial(n-1);       // | o -->  | o --> | o --> | 
                                    // 4c + 3o
                                    // f(n) = (n)c + (n-1)o
                                    // f(n) = n(c + o) - o
                                    // f(n) ~ n
}

int main(void) {

    int n;
    printf("Calcule fatorial de: ");
    scanf("%d", &n);
    // n = 6; // TEST

    long int fn = fatorial(n);

    printf("Fatorial de %d = %ld\n", n, fn);
}