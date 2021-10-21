#include <stdlib.h>
#include <stdio.h>

void quicksort(char* v, int ini, int fim) {
    
    // caso base: vetores de tamanho 0 ou 1
    if (fim <= ini) return;

    // particao: em torno do *pivo*
    int p = ini;
    int i = ini + 1;
    int j = fim;

    while (i <= j) {                            // Enquanto nao trocar de lados
        while (i < fim && v[i] <= v[p]) i++;    // i ->
        while (v[j] > v[p]) j--;                //   <- j

        if (j > i) {
            char tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
        }
    }
    // posicionar *pivo* na posicao correta
    p = j;
    char tmp = v[p];
    v[p] = v[ini];
    v[ini] = tmp;


    // chamada recursiva
    quicksort(v, ini, p-1);
    quicksort(v, p+1, fim);
}

int main(void) {
    char A[8] = {'E','A','Y','D','B','F','C','\0'};

    printf("%s\n", A);

    quicksort(A, 0, 6);

    printf("%s\n", A);

    return 0;
}