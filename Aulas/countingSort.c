#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	int key;
	int value;
	//outros atributos
} Record;

void imprimeVetor(Record* vetor, int tamanhoVetor){
	if (tamanhoVetor <= 100){
		int i;
		for (i=0; i<tamanhoVetor; i++){
			printf("[%i] %i; ", vetor[i].key, vetor[i].value);
		}
	}
	printf("\n");
}

/*
	De forma geral, os melhores algoritmos de compara��o s�o n.log(n)
	Counting Sort � fundamentado em contagens e n�o compara��es
	O ganho na complexidade f(n) < n.log(n) vem com o custo adicional de aloca��o de mem�ria auxiliar.
	
	Exemplo com structs: [1 5 0 0 5 1 2 5 3 1] - keys
	
	- 1) C�pia completa dos dados originais.
	- 2) Aloca��o de mem�ria: (refer�ncia das chaves a serem ordenadas)
		2.1) Percorrer as chaves e verificar o m�nimo e m�ximo (m�nimo = 0; m�ximo = 5)
		2.2) Cria��o de um vetor adicional de contagem:
			[0 0 0 0 0 0]
		2.3) Percorrer o vetor de contagem com o somat�rio por chave:
			[2 3 1 1 0 3]
	- 3) Contagem acumulada de frequ�ncias (chaves discretas)
			[0 2 5 6 7 7]
	- 4) Posicionamento de chaves (forma ordenada): c�pia: [1 5 0 0 5 1 2 5 3 1] 
		original			  contagem acumulada
	 0 1 2 3 4 5 6 7 8 9      0 1 2 3 4 5
	[1 5 0 0 5 1 2 5 3 1]	 [0 2 5 6 7 7] - chave 1 (c�pia) para a posi��o 2 (contagem); posiciona e soma posi��o;
	[1 5 1 0 5 1 2 5 3 1]	 [0 3 5 6 7 7] - chave 5 (c�pia) para a posi��o 7 (contagem); posiciona e soma posi��o;
	[1 5 1 0 5 1 2 5 3 1]	 [0 3 5 6 7 8] - chave 0 (c�pia) para a posi��o 0 (contagem); posiciona e soma posi��o;
	[0 5 1 0 5 1 2 5 3 1]	 [1 3 5 6 7 8] - chave 0 (c�pia) para a posi��o 1 (contagem); posiciona e soma posi��o;
	[0 0 1 0 5 1 2 5 5 1]	 [2 3 5 6 7 8] - chave 5 (c�pia) para a posi��o 8 (contagem); posiciona e soma posi��o;
	[0 0 1 1 5 1 2 5 5 1]	 [2 3 5 6 7 9] - chave 1 (c�pia) para a posi��o 3 (contagem); posiciona e soma posi��o;
	[0 0 1 1 5 2 2 5 5 1]	 [2 4 5 6 7 9] - chave 2 (c�pia) para a posi��o 5 (contagem); posiciona e soma posi��o;
	[0 0 1 1 5 2 2 5 5 1]	 [2 4 6 6 7 9] - chave 5 (c�pia) para a posi��o 9 (contagem); posiciona e soma posi��o;
	[0 0 1 1 5 2 2 5 5 5]	 [2 4 6 6 7 10] - chave 3 (c�pia) para a posi��o 6 (contagem); posiciona e soma posi��o;
	[0 0 1 1 5 2 3 5 5 5]	 [2 4 6 7 7 10] - chave 1 (c�pia) para a posi��o 4 (contagem); posiciona e soma posi��o;
	[0 0 1 1 1 2 3 5 5 5]	 [2 5 6 7 7 10] - fim
	
	Complexidade:
	- 1.1 - malloc)
	- 2.1 - copia,max,min ) n
	- 2.2 - calloc)
	- 2.3 - contagem) n
	-   3 - cont. acumulada) k
	-   4 - posicionamento) n
	
	Ent�o: f(n) = 3n + k; O(n+k)
	
	Observa��o:
	- a ordem relativa dos elementos de uma mesma chave � perservada (algoritmo est�vel)
	- requer dois vetores auxiliares: um de tamanho n e outro de tamanho k
	- a fun��o de efici�ncia � totalmente dependente da quantidade de chaves (k)
	- se todas as chaves s�o diferentes e sequenciais, ent�o k=n e O(2n)
*/

void countingSort(Record* vetor, int tamanho){
	//1) C�pia completa dos dados originais.
	Record* vetorAux = (Record*) malloc(tamanho * sizeof(Record));
	
	//2.1) Percorrer as chaves e verificar o m�nimo e m�ximo
	int max, min;
	max = min = vetor[0].key;
	int i = 0;
	for(i = 1; i<tamanho; i++){
		if (vetor[i].key > max) max = vetor[i].key;
		if (vetor[i].key < min) min = vetor[i].key;
		vetorAux[i] = vetor[i];
	}

	//2.2) Cria��o de um vetor adicional de contagem [0 - 5] -> 6 posi��es [5-0+1]
	int* vetorContagem = (int*) calloc(max-min+1, sizeof(int));
	
	//2.3) Percorrer o vetor de contagem com o somat�rio por chave
	// [2, 5, 7] -> [1 0 0 1 0 1] 
	for(i = 0; i<tamanho; i++){
		int posicaoKey = vetor[i].key - min; //ajuste (- min)
		vetorContagem[posicaoKey]++;
	}
	
	//3) contagem acumulada das chaves [1 0 0 1 0 1] -> [0 1 1 1 2 2]
	int total = 0;
	for(i = 0; i<=(max-min); i++){
		int contagemAnterior = vetorContagem[i];
		vetorContagem[i] = total;
		total = total + contagemAnterior;
	}
	
	//4) percorrer o vetor de contagem e produzir posicionamento correto
	for(i = 0; i<tamanho; i++){
		int posicaoOrdenada = vetorContagem[vetorAux[i].key-min];
		vetor[posicaoOrdenada] = vetorAux[i];
		vetorContagem[vetorAux[i].key-min]++;
	}
	
	free(vetorContagem);
	free(vetorAux);
}

int main(int argc, char* argv[]){
	int geracaoVetor = atoi(argv[1]);
	int tamanhoVetor = atoi(argv[2]);
	clock_t inicio, final;
	
	//gera��o dos elementos
	Record* vetor = (Record*) malloc(tamanhoVetor * sizeof(Record));
	srand(time(NULL));
	
	int i;
	for (i=0; i<tamanhoVetor; i++){
		if (geracaoVetor == 0) //aleat�rio
			vetor[i].key = rand() % 1000;
		else if (geracaoVetor == 1) //ordenado
			vetor[i].key = i;
		else if (geracaoVetor == 2) //invertido
			vetor[i].key = tamanhoVetor - i;
		else if (geracaoVetor == 3 && i<=tamanhoVetor/2) //primeira metade ordenada e o restante aleat�rio
			vetor[i].key = i;
		else if (geracaoVetor == 3) //primeira metade ordenada e o restante aleat�rio
			vetor[i].key = (rand() % 1000) + i;
		vetor[i].value = -(rand() % 1000);
	}
	
	printf("Counting Gerado: ");
	imprimeVetor(vetor, tamanhoVetor);
	inicio = clock();
	countingSort(vetor, tamanhoVetor);
	final = clock();
	printf("Counting Ordenado: "); 
	imprimeVetor(vetor, tamanhoVetor);
	printf("Tempo de ordenacao Counting: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetor);

	return 0;	
}