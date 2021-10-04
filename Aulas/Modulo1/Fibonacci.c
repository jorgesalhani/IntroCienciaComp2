#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long int fibonacci(long int n) {
                                                // Contagem de operacoes
                                                // a: atribuicao
                                                // o: operacao
                                                // c: comparacao
                                                // r: retorno de funcao

                                                // Caso n=3
                                                // | n=3    | n=1       n=2     | n=0
    if (n == 0) return 0;                       // | c      | c         c       | (c + r)
    if (n == 1) return 1;                       // | c      | (c + r)   c       |

    return fibonacci(n - 1) + fibonacci(n - 2); // | 3o --> |           2o -->  |

                                                // (2c + 3o) + (2c + r) + (2c + 2o) + c + r
                                                // (7c + 5o + 2r)

                                                // (2n + 1)c + (n + 1)o + (n-1)r
                                                // r[n] = (2n + 1)c + (n + 1)o + (n-1)r

                                                // Considerando
                                                // c = o = r = C
                                                // r[n] = (4n + 1)C
                                                // r[n] = (4C)n + C
                                                // r[n] ~ n             ERROR!

    /* *
     * Analise de recorrencia:
     * f(n) = 2c + f(n-1) + f(n-2)
     * 
     * Sendo f(n-1) ~ f(n-2): Limite inferior f(n-2)                    k
     * f(n) = 2c + 2f(n-2)  = 2(c + f(n-2))                             1
     *                      = 2(c + 2(c + f(n-4)))  = 6c + 4f(n-4)      2
     *                      = 6c + 4(2(c + f(n-6))) 
     *                      = 6c + 4(2c + 2f(n-6))  = 14c + 8f(n-6)     3
     *                       
     *                                      
     * 
     * f(k) = (2^k + 2k)c + (2^k)(f(n-2k))
     * 
     * Finaliza quando: n - 2k = 0  Entao: k = n/2
     * f(n) = (2^(n/2) + n)c + 2^(n/2)f(0)
     * 
     * Se f(0) = c
     * f(n) = c(2.2^(n/2) + n)
     * f(n) ~ 2^(n/2)
     * 
     * Sendo f(n-1) ~ f(n-2): Limite superior f(n-1)                    k
     * f(n) = 2c + 2f(n-1)  = 2(c + f(n-1))                             1
     *                      = 2(c + 2(c + f(n-2)))  = 6c + 4f(n-2)      2
     *                      = 6c + 4(2(c + f(n-3))) = 14c + 8f(n-3)     3
     * 
     * f(k) = (2^k + 2k)c + (2^k)(f(n-k))
     * 
     * Finaliza quando: n - k = 0   Entao: k = n
     * f(n) = (2^n + 2n)c + (2^n)(f(0))
     * 
     * Se f(0) = c
     * f(n) = c(2.2^n + 2n)
     * f(n) ~ 2^n
     * 
     * A funcao f(n) de fato esta limitada entre:
     * 
     * 2^(n/2) <= f(n) <= 2^(n)
     * */
}

long int fibonacci_iterativo(long int n) {

                                                // Contagem de operacoes
                                                // a: atribuicao
                                                // o: operacao
                                                // c: comparacao
                                                // r: retorno de funcao

    long int F = 0;                             // a
    long int Ftemp = 1;                         // a

    for (int i = 1; i <= n; i++) {              // a + c
        F += Ftemp;                             // o + a
        Ftemp = F - Ftemp;                      // o + a --> x n
    }                                           // 2a + (3a + 2o + c)n
                                                
                                                // Seja:
                                                // a = o = c = C
                                                // r[n] = (6C)n + 2C
                                                // r[n] ~ n
    return F;
}

int main(void) {

    int n;
    printf("Fibonacci de: ");
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