#include <stdlib.h>
#include <stdio.h>
#include <sorting.h>

int pivo_inicio(int i, int f) {
    return i;
}

int pivo_central(int i, int f) {
    return (int) ((i+f)/2.0);
}

int pivo_aleatorio(int i, int f) {
    return (int) (rand()%(f-1)) + 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
		printf("Informe tamanho do vetor\n");
		return 1;
	}
	int n = atoi(argv[1]);

	clock_t c1, c2;
	double qs_time, ms_time;

	srand(1);
	int* vet = gera_vetor(n, 1, (int)(n*3));
	if (n <= 20) imprime_vetor(vet, n);
	printf("Quicksort...\n");	
	c1 = clock();
	quicksort(vet, 0, n-1, pivo_aleatorio);
	c2 = clock();
	qs_time = (c2-c1)/(double)CLOCKS_PER_SEC;
	if (n <= 20) imprime_vetor(vet, n);

	free(vet);


    return 0;
}