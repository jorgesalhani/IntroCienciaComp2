#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define FAIL -404
#define EXPERIMENTOS 100

bool validate_input_amount(int* argc, char* prog_name) {
    if (*argc < 6) {
        printf("Uso do programa: \n");
        printf(" %s <tam vetor> <val min> <val max> <verb> <n amostras>\n", prog_name);
        return false;
    }
    return true;
}

int* gera_vetor (long int tam, int min, int max, int ordenado) {

	// verifica problemas
	if (tam < 1 || min > max) return NULL;

	int* vet = (int *) malloc(sizeof(int)*tam);

	// verifica se houve problema na alocacao
	if (vet == NULL) return NULL;
	vet[0] = (rand() % 2) + min;
	for (int i = 1; i < tam; i++) {
		// ex. min = 0, max = 5, [0, 4] = [0,4+1] = [0, 5]
		//     min = 3, max = 8, [0, 5] + 3 = [3, 8]
		if (!ordenado) {
			vet[i] = (rand()%(max-min+1)) + min;
		}
		else {
			int val = vet[i-1] + rand()%3;
			if (val > max) val = max;
			vet[i] = val;
		}
	}
	return vet;
}

void imprime_vetor(int* v, int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int busca_sequencial(int* v, int chave, int N) {
	for (int i = 0; i < N; i++) {   
		if (v[i] == chave)
			return i;
	}	
	return FAIL;
}

void analise(int* v1, int chave, long int amostras) {

    clock_t t1, t2;

    FILE* exp_file = fopen("busca_sequencial.txt", "a");

    for (long int x = 1; x < EXPERIMENTOS; x++) {
        long int N = exp();
        double tempo_medio = 0.0;
        for (int i = 0; i < amostras; i++) {
            t1 = clock();
            int pos = busca_sequencial(v1, chave, N);
            t2 = clock();

            double ts = (t2-t1)/(double)CLOCKS_PER_SEC;
            tempo_medio += ts/(double)amostras;
        }
        fprintf(exp_file, "%ld\t%.7lf\n", N, tempo_medio);
    }

    fclose(exp_file);
    
}

int main (int argc, char* argv[]) {

    if (!validate_input_amount(&argc, argv[0])) {
        return 1;
    }

    int N = atol(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);
    int verb = atoi(argv[4]);
    int amostras = atol(argv[5]);

    srand(time(NULL));
    int* v1 = gera_vetor(N, min, max, 1);

    int chave = v1[N-1];

    if (verb) {
        imprime_vetor(v1, N);
        int pos = busca_sequencial(v1, chave, N);
        printf("Chave: %d\n", chave);
        printf("Encontrada na posicao: %d\n", pos);
    } else {
        analise(v1, chave, amostras);
    }

    free(v1);

    return 0;

}