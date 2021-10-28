#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubblesort(char *item, int count);

void heapsort(char *item, int count);

void insertionsort(char *item, int count);

void selectionsort(char *item, int count);

void shellsort(char *item, int count);

int* gera_vetor(int tam, int min, int max);

void imprime_vetor(int*v, int N);

void quicksort(char* v, int ini, int fim, int (*eep)());

void max_heapify(int* v, int p, int N);

void build_maxheap(int*v, int N);