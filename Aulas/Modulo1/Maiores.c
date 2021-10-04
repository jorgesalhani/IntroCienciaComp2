#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0

int* aloca_e_preenche_vetor(int n) {
    int* p_local = malloc(n*sizeof(int));

    for (int i = 0; i < n; i++) {
        p_local[i] = rand() % n;
        if (DEBUG) printf("%d ", p_local[i]);
    }
    if (DEBUG) printf("\n");
    return p_local;
}

int maiores(int valor, int* vetor, int n) {
                                                /** ALGORITMO
    
                                                Contagem de operacoes:
                                                    - aritmeticas e comparacoes = a
                                                    - atribuicoes = c
                                                    - acessos a ponteiro ou vetor = p
                                                    - retorno de funcao = r
                                                */
    int qtd_maiores = 0;                        // c
                                                // | i=0        | i=1
    for (int i = 0; i < n; i++) {               // | c + a      | a + c + a
        if (vetor[i] > valor) {                 // | p + a      | p + a
            qtd_maiores++;                      // | a + c -->  | a + c --> x(n-1)
        }                                       //
    }                                           // (3a + p + 2c) + (4a + 2c + p)(n-1)
                                                // (4a + 2c + p)n - a

    return qtd_maiores;                         // r
                                                // 
                                                // (4a + 2c + p)n - a + r
                                                // r[n] = (4a + 2c + p)n - a + r
}

int main (int argc, char* argv[]) {
    
    if (argc < 2) {
        printf("Informe o tamanho do vetor de entrada.\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 1 || n > 10000000) {
        printf("O tamaho do vetor de entrada deve ser entre 1 e 10000000");
        return 1;
    }

    int* vet = NULL;
    vet = aloca_e_preenche_vetor(n);

    int* vet_maiores = malloc(n*sizeof(int));

    clock_t c1, c2;

    c1 = clock();

    /** ALGORITMO
    
    Contagem de operacoes:
        - aritmeticas e comparacoes = a
        - atribuicoes = c
        - acessos a ponteiro ou vetor = p
        - retorno de funcao = r
    */
                                                    // | j=0            | j=1
    for (int j = 0; j < n; j++) {                   // | c + a          | a + c + a
        vet_maiores[j] = maiores(vet[j], vet, n);   // | p + c + r -->  | p + c + r --> x(n-1)
                                                    // 
                                                    // (2c + a + p + r[n]) + (2a + 2c + p + r[n])(n-1)
                                                    // (2a + 2c + p + r[n])n - a
        // printf("%d - existem %d > %d\n", j, vet_maiores[j], vet[j]);
    }

    /* Sendo:   r[n] = (4a + 2c + p)n - a + r e tambem:
                (2a + 2c + p + r[n])n - a
    
    f(n) =  (2a + 2c + p)n + r[n].n - a
            (2a + 2c + p)n + ((4a + 2c + p)n - a + r)n - a
                             ((4a + 2c + p)n^2 - a.n) - a
            (a + 2c + p)n + (4a + 2c + p)n^2 - a

    f(n) = (4a + 2c + p)n^2 + (a + 2c + p)n - a
    
    
    Caso a = c = r = p = C

    Funcao de eficiencia:

    f(n) = (7C)n^2 + (4C)n - C
    f(n) ~ n^2
    */

    c2 = clock();

    double tempo = (c2 - c1) / (double)CLOCKS_PER_SEC;
    printf("Tempo de execucao para %d elementos = %lf seg\n", n, tempo);
    free(vet_maiores);
    free(vet);
    return 0;
}