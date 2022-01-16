#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimeVetor(int* vetor, int tamanhoVetor){
	if (tamanhoVetor <= 100){
		int i;
		for (i=1; i<tamanhoVetor; i++){
			printf("%i ", vetor[i]);
		}
	}
	printf("\n");
}

/*
	Heap: 
	- baseada em uma estrutura de árvore binária
	- nó-raiz
	- nós-filhos
	- nós-folhas

	Representação da árvore em uma estrutura de vetor
	- pai: i
	- filho esq: 2*i
	- filho dir: 2*i + 1

	 1 2 3 4 5 6
	[9 6 8 5 6 7]

	     6
	  5      
         

	[5 | 6 6 7 8 9]

	MaxHeap:
	- pai é maior ou igual que seus filhos
	- a análise inicia-se no último elemento que não seja nó-folha
	- quando a condição de Heap é quebrada, troca-se elementos e verifica-se todas as sub-ramificações
	- após a construção do MaxHeap executamos o processo de ordenação

	Ordenação:
	- troca-se o primeiro elemento pelo último
	- reduz o tamanho do Heap
	- verifica consistência do MaxHeap

	Observações: para facilitar implementação, consideramos que o vetor inicia-se na posição 1

*/


void heapifyMax(int* vetor, int pai, int tamanho){
	//verificar os filhos da "pai", se ferir a condição trocar o maior filho com o pai
	int filho = pai*2;//filho da esquerda

	//garantir que o nó-filho da esquerda existe
	if (filho > tamanho) return;

	//verificar a condição de heap em relação aos filhos
	//1 - o filho da esquerda é maior que o pai
	//2 - existe o filho da direita
	//3 - o filho da direita é maior que o pai
	//printf("Pai: %i. Esquerda %i.\n", vetor[pai], vetor[filho]);
	if (vetor[filho] > vetor[pai] || (filho+1 <= tamanho && vetor[filho+1] > vetor[pai])){
		//1 - existe o filho da direita
		//2 - o filho da direita é maior que o filho da esquerda
		if (filho+1 <= tamanho && vetor[filho+1] > vetor[filho])
			filho = filho+1;
		//se falso, filho deve ser trocado com o pai (padrão é trocar com o filho da esquerda)

		//troca o pai com o maior filho
		//***se o maior filho é o da esquerda, ele já se encontra em "filho"
		int aux = vetor[pai];
		vetor[pai] = vetor[filho];
		vetor[filho] = aux;

		//atualizar possíveis "netos" restantes
		heapifyMax(vetor, filho, tamanho);
	}
}

void heapSort(int* vetor, int tamanho){
	//construção do MaxHeap
	int ultimoPai = (int)tamanho/2.0;
	int i;
	for (i = ultimoPai; i>=1; i--)
		heapifyMax(vetor, i, tamanho);

	imprimeVetor(vetor, tamanho);

	//processo de ordenação
	while (tamanho >= 2){
		//seleciona maior
		int maior = vetor[1];
		vetor[1] = vetor[tamanho];
		vetor[tamanho] = maior;

		tamanho--;
		heapifyMax(vetor, 1, tamanho);
	}
}

int main(int argc, char* argv[]){
	int geracaoVetor = atoi(argv[1]);
	int tamanhoVetor = atoi(argv[2])+1;
	clock_t inicio, final;
	
	//geração dos elementos
	int *vetor = malloc(tamanhoVetor * sizeof(int));
	srand(time(NULL));
	
	int i;
	vetor[0] = -1;
	for (i=1; i<tamanhoVetor; i++){
		if (geracaoVetor == 0) //aleatório
			vetor[i] = rand() % 1000;
		else if (geracaoVetor == 1) //ordenado
			vetor[i] = i;
		else if (geracaoVetor == 2) //invertido
			vetor[i] = tamanhoVetor - i;
		else if (geracaoVetor == 3 && i<=tamanhoVetor/2) //primeira metade ordenada e o restante aleatório
			vetor[i] = i;
		else if (geracaoVetor == 3) //primeira metade ordenada e o restante aleatório
			vetor[i] = (rand() % 1000) + i;
	}
	
	printf("Heap Gerado: ");
	imprimeVetor(vetor, tamanhoVetor);
	inicio = clock();
	heapSort(vetor, tamanhoVetor-1);
	final = clock();
	printf("Heap Ordenado: "); 
	imprimeVetor(vetor, tamanhoVetor);
	printf("Tempo de ordenacao Heap: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetor);

	return 0;	
}