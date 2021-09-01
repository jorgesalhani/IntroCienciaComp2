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
    int qtd_maiores = 0;                        // (a) 
    for (int i = 0; i < n; i++) {               // 1. (a + c) ; 2. (2a + c)*(n-1)
        if (vetor[i] > valor) {                 // (p + c) * n
            qtd_maiores++;                      // (2a) * n
        }
    }

    return qtd_maiores;                         // r
                                                // -----
                                                // (a) + (a+c) + (n-1)(2a+c) + (n)(p+c) + (n)(2a) + r
                                                // m(n) = n(4a + 2c + p) + r
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

    for (int j = 0; j < n; j++) { // 1. (a + c) ; 2 em diante (2a + c)
        vet_maiores[j] = maiores(vet[j], vet, n); // 2p + maiores
        // maiores = m(n) = n(4a + 2c + p) + r
        // printf("%d - existem %d > %d\n", j, vet_maiores[j], vet[j]);
    }

    // f(n) = (a + c) + (n-1)(2a+c) + (n)2p + (n)(m(n))
    // f(n) = 2na + nc - a + 2np + n(n(4a + 2c + p) + r)
    // f(n) = n(2a + c + 2p) - a + n**2(4a + 2c + p) + nr
    // f(n) = (4a + 2c + p)n**2 + (2a + 2p + c + r)n - a

    // Caso a = c = r = p = C
    //
    // Funcao de eficiente da contagem de maiores
    //
    // f(n) = (7C)(n**2) + (6C)(n) - C

    c2 = clock();

    double tempo = (c2 - c1) / (double)CLOCKS_PER_SEC;
    printf("Tempo de execucao para %d elementos = %lf seg\n", n, tempo);
    free(vet_maiores);
    free(vet);
    return 0;
}