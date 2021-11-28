#include <stdlib.h>
#include <stdio.h>

/**
 * Counting sort original
 * Counting sort com registros
 * 
 * Limitacoes
 *  - natural para inteiros
 *  - faz mais sentido quado há repetição de chaves
 *  - faz mais sentido quando o intervalo das chaves (K): K <= N
 * 
 * Jorge Salhani - 2021
 */

void countingsort(int*v, int N) {

    /**
     * @brief 
     * Criar vetor auxiliar para fazer a contagem das chaves
     *  
     * Valores a ordenar (chaves): entre 0 e 6
     * 
     *  0 1 2 3 4 5 6
     * [0,0,0,0,0,0,0]
     * 
     * v = [6,6,0,1,2,2,0,3,0]
     * 
     *  0 1 2 3 4 5 6
     * [3,1,2,1,0,0,2]
     * 
     * v = [0,0,0,1,2,2,3,6,6]
     * 
     * Realizar contagem
     * Percorrer o vetor de contagem copiando para o vetor original
     * 
     * E se as chaves forem entre 100 e 108?
     * 100, ... ..., 108
     *  [0,0,0,0,0,0,0]
     */

    // 0 - encontrar chaves min e max
    int max, min;                               // Operacoes
    max = min = v[0];                           // a - aritmetica;
                                                // b - atribuicao;
                                                // c - comparacao; 
    for (int i = 1; i < N; i++) {
        if (v[i] > max) max = v[i];             // c+b
        if (v[i] < min) min = v[i];             // c+b
    }
                                                // 2(c+b)N

    // 1 - criar vetor de contagem
    int tam_c = (max-min)+1;
    int *C = (int*) calloc(tam_c, sizeof(int)); // Kb

    // 2 - contar frequencia de cada chave
    for (int i = 0; i < N; i++) {
        int pos_chave = v[i] - min;             // a
        C[pos_chave]++;                         // a
    }                                           // (2a)N

    // 3 - recriar o vetor usando as frequencias
    int i = 0;
    for (int j = 0; j < tam_c; j++) {
        while (C[j]) {                          // c
            v[i] = j+min;                       // a
            C[j]--;                             // a
            i++;                                // a
        }
    }                                           // (K + N)(c+3a)

                                                // f(n) = N(2(c + b)) + Kb + N(2a + c + 3a)
                                                // f(n) = N(5a + 2b + 5c) + K(3a + b + c)

    /**
     * @brief 
     * 
     *  j
     *  0 1 2 3 4 5 6 7 8 
     * [3,1,2,1,0,0,2,0,1]
     * 
     *      i
     * v = [100, ]
     *          i
     * v = [100,100, ]
     *              i
     * v = [100,100,100, ]
     *                  i
     * v = [100,100,100,101, ]
     * ...
     */

    free(C);
}

int main(void) {
    
    int N = 10;
    int minc = 100;

    int *v = (int*) malloc(sizeof(int) * N);

    int i = 0;
    printf("Vetor a ordenar: ");
    for (i = 0; i < N; i++) {
        v[i] = (rand()%(int)(N / 3.0)) + minc; // 1/3 do vetor para ter repeticao
        printf("%d ", v[i]);
    }
    printf("\n");

    countingsort(v, N);

    printf("Vetor ordenado: ");
    for (i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    free(v);

    return 0;
}