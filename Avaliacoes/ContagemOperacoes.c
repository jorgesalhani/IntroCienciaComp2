#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long int algoritmo2(int N) {

    // Operacoes
    // a - atribuicao
    // c - comparacao
    // r - retorno
    // o - operacoes aritmeticas

    long int a = 0;             // a
    long int b = 1;             // a
                                //                                      Caso N = 5
    if (N == 1) return a;       // c    < pior caso, sem retorno        
    if (N == 2) return b;       // c    < pior caso, sem retorno
    long int c;
    while (N-2 > 0) {           // (o + c)  *(N-1)                      |3 > 0           |2 > 0          |1 > 0         |0 > 0 false
        c = a + b;              // (o + a)  *(N-2)                      |c = (0 + 1)     |c = (1 + 1)    |c = (1 + 2)   |
        a = b;                  // a        *(N-2)                      |a = 1           |a = 1          |a = 2         |
        b = c;                  // a        *(N-2)                      |b = 1           |b = 2          |b = 3         |
        N = N - 1;              // (o + a)  *(N-2)                      |N = 4 ----->    |N = 3 ----->   |N = 2 ----->  |
    }
    return c;                   // r
                                // ----------------
                                // 2a + 2c + (o+c)(N-1) + (2(o+a) + 2a)(N-2) + r
                                // 2a + 2c + (o+c)N - o - c + (2o + 4a)N - 2(2o + 4a) + r
                                // 2a + c - o + N(o + c + 2o + 4a) - 4o - 8a + r
                                // (-6a + c - 5o + r) + N(3o + 4a + c)

                                // Considerando a == c == o == r = C
                                // f(n) = (-9C) + (8C)*N
}

int main (int argv, char* argc[]) {
    
    if (argv < 2) {
        printf("Informe: %s <N>\n", argc[0]);
        return 1;
    }

    int N = atoi(argc[1]);

    clock_t t1, t2; 

    t1 = clock();
    long int alg2 = algoritmo2(N);
    t2 = clock();

    double time = (t2-t1)/(double)CLOCKS_PER_SEC;
    printf("%lf\n", time);
    return 0;
}