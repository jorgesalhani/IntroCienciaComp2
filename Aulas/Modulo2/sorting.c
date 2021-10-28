#include <stdlib.h>
#include "sorting.h"

int* gera_vetor(int tam, int min, int max) {
    if (tam < 1 || min > max) return NULL;

    int* vet = (int*) malloc(sizeof(int)*tam);

    if (vet == NULL) return NULL;

    for (int i = 0; i < tam; i++) {
        int val = (rand()%(max-min+1)) + min;
        vet[i] = val;
    }

    return vet;
}

void imprime_vetor(int*v, int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void bubblesort(char *item, int count) {
    register int a, b;
    register char t;

    for (a = 1; a < count; ++a) {
        for (b = count-1; b >= a; --b) {
            if (item[b-1] > item[b]) {
                t = item[b-1];
                item[b-1] = item[b];
                item[b] = t;
            }
        }
    }
}

void insertionsort(char *item, int count) {
    register int a, b;
    char t;

    for (a = 1; a < count; ++a) {
        t = item[a];
        for (b = a-1; b >=0 && t < item[b]; b--) {
            item[b+1] = item[b];
        }
        item[b+1] = t;
    }
}

void shellsort(char *item, int count) {
    register int i, j, gap, k;
    char x, a[5];

    a[0] = 9;
    a[1] = 5;
    a[2] = 3;
    a[3] = 2;
    a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; i++) {
            x = item[i];
            for (j = i-gap; x < item[j] && j >= 0; j=j-gap) {
                item[j+gap] = item[j];
            }
            item[j+gap] = x;
        }
    }
}

void selectionsort(char *item, int count) {
    register int a, b, c;
    int exchange;
    char t;

    for (a = 0; a < count-1; ++a) {
        exchange = 0;
        c = a;
        t = item[a];

        for (b = a+1; b < count ; ++b) {
            if (item[b] < t) {
                c = b;
                t = item[b];
                exchange = 1;
            }
        }

        if (exchange) {
            item[c] = item[a];
            item[a] = t;
        }
    }
}

void quicksort(char* v, int ini, int fim, int (*eep)()) {
    
    // caso base: vetores de tamanho 0 ou 1
    if (fim <= ini) return;

    // particao: em torno do *pivo*
    int p = eep(ini, fim);
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
    quicksort(v, ini, p-1, eep);
    quicksort(v, p+1, fim, eep);
}

void max_heapify(int* v, int p, int N) {
    int f = p*2;
    if (f > N) return;

    if ((v[f] > v[p]) || ((f+1 <= N) && (v[f+1] > v[p]))) {
        if (f+1 <= N && v[f+1] > v[f]) {
            f++;
        }

        int tmp = v[p];
        v[p] = v[f];
        v[f] = tmp;

        max_heapify(v, f, N);
    }
}

void build_maxheap(int* v, int N) {
    int m = (int) N/2.0;
    for (int p = m; p >= 1; p--) {
        max_heapify(v, p, N);
    }
}

void heapsort(int* v, int N) {
    build_maxheap(v, N);
    
    while (N >= 2) {
        int maior = v[1];
        v[1] = v[N];
        v[N] = maior;

        N--;
        max_heapify(v, 1, N);
    }
}