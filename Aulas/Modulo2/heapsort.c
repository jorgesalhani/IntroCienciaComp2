#include <stdio.h>
#include <stdlib.h>

#include "sorting.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Informe o tamanho do vetor\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int* vet = gera_vetor(n, 1, (int)(n*3));
    if (n <= 20) imprime_vetor(vet, n);

    printf("Build Maxheap...\n");
    // Primeira posicao ignorada
    build_maxheap(vet, n-1);
    if (n <= 20) imprime_vetor(vet, n);

    free(vet);
    return 0;
}