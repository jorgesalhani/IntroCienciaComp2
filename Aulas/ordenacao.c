#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimeVetor(int* vetor, int tamanhoVetor){
	if (tamanhoVetor <= 100){
		int i;
		for (i=0; i<tamanhoVetor; i++){
			printf("%i ", vetor[i]);
		}
	}
	printf("\n");
}

/*
	- Percorre um conjunto de elementos da esquerda para a direita e 
	à medida que avança vai deixando os elementos à esquerda ordenados
	- Exemplo:
		| 5 8 7 13 20 22 85 1 4 9
		5 | 8 7 13 20 22 85 1 4 9
		5 8 | 7 13 20 22 85 1 4 9
		5 7 | 8 13 20 22 85 1 4 9
		5 7 8 | 13 20 22 85 1 4 9
		...
		5 7 8 13 20 22 85 | 1 4 9
			5 7 8 13 20 22   | 85 4 9
			5 7 8 13 20   22 | 85 4 9
			  5 7 8 13 20 22 | 85 4 9
			1 5 7 8 13 20 22 | 85 4 9
			1 5 7 8 13 20 22 85 | 4 9
		...
		1 4 5 7 8 9 13 20 22 85 |
*/
int* insertionSort(int* vetor, int tamanho){
	int j;
	for(j = 1; j < tamanho; j++){//o elemento na posição 0 não precisa analisar
		int chave = vetor[j]; //variável auxiliar, temporária para armazenar o valor do momento
		int i = j - 1; //armazenar a posição de análise do momento
		while (i >= 0 && vetor[i] > chave){//final do vetor ; valor do vetor é maior que a chave de análise
			vetor[i+1] = vetor[i];
			i--;
		}
		vetor[i+1] = chave;
	}
	
	return vetor;
}

/*
	Método de ordenação baseado em divisão e conquista
	Exemplo:
		[8 7 9 2 0 3 5 3] -> primeiro estágio
		[8 7 9 2] [0 3 5 3] -> mergeSort(0 a 3)
		[8 7] [9 2] [0 3 5 3] -> mergeSort(0 a 1)
		[8] [7] [9 2] [0 3 5 3] -> mergeSort(0 a 0)
		[7 8] [9 2] [0 3 5 3] -> intercalação (0 a 1)
		[7 8] [9] [2] [0 3 5 3] -> mergeSort(2 a 3)
		[7 8] [2 9] [0 3 5 3] -> intercalação(2 a 3)
		[2 7 8 9 ] [0 3 5 3] -> intercalação(0 a 3)
		...
		[2 7 8 9 ] [0 3 3 5] -> intercalação(4 a 7)
		[0 2 3 3 5 7 8 9] -> intercalação(0 a 7)
*/

void intercala(int* vetor, int inicio, int centro, int fim){
	//intercalação
	int* vetorAux = (int*)malloc(sizeof(int) * (fim-inicio)+1);

	int i = inicio;	// indice da primeira lista ordenada
	int j = centro+1; //indice da segunda lista ordenada
	int k = 0; //indice do vetor auxiliar

	//compara e intercala os elementos do menor para o maior
	while(i <= centro && j <= fim){
		
		if (vetor[i] <= vetor[j]){ //verifica qual é o elemento menor entre as duas listas
			vetorAux[k] = vetor[i];
			i++; //proximo elemento da primeira metade
		}
		else{
			vetorAux[k] = vetor[j];
			j++; //proximo elemento da segunda metade
		}
		k++;
	}

	while(i <= centro){//há elementos na primeira metade ainda?
		vetorAux[k] = vetor[i];
		i++;
		k++;
	}

	while(j <= fim){//há elementos na segunda metade ainda?
		vetorAux[k] = vetor[j];
		j++;
		k++;
	}

	//atualizando o vetor original com o vetor auxiliar
	for(i = inicio, k = 0; i <= fim; i++,k++)
		vetor[i] = vetorAux[k];
	free(vetorAux);
}

void mergeSort(int* vetor, int inicio, int fim){
	//caso base
	if (fim <= inicio) return;

	//processo de divisão
	int centro = (int)((inicio+fim)/2.0);
	mergeSort(vetor, inicio, centro);
	mergeSort(vetor, centro+1, fim);

	//processo de conquista
	intercala(vetor, inicio, centro, fim);
}

/*
	- Método de ordenação que busca confirmar os maiores valores,
	tendo certeza da localização do último elemento para o primeiro.
	Exemplo:
		[9 2 5 1 0 6 |]
		[2 5 1 0 6 | 9]
		[2 5 1 0 | 6 9]
		[2 1 0 | 5 6 9]
		[1 0 | 2 5 6 9]
		[0 | 1 2 5 6 9]
		[| 0 1 2 5 6 9]
*/

int* bubbleSort(int* vetor, int tamanho){
	int i, j;
	for(i = 0; i < tamanho-1; i++){
		for(j = 0; j < tamanho-1-i; j++){
			if (vetor[j] > vetor[j+1]){
				int aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;		
			}
		}
	}
	
	return vetor;

	//Primeiro for: (n-1)
	//Segundo for: 1a.(n-1-0); 2a.(n-1-1); 3a.(n-1-2); ka.(n-1-(n-2)=1) então 
	//	somatorio (n-i-1) de i=0 até n-2 ou  somatorio (n-k) de k=1 até n-1
	//Por meio de Progressão Aritmética: ((número de termos*(primeiro termo+ultimo termo))/2
	//	((n-1).((n-1)+1))/2 = (n.n - n)/2
}

int* bubbleSortRecursivo(int* vetor, int tamanho, int i){
	if (i >= tamanho-1) return vetor;

	int j;
	for(j = 0; j < tamanho-1-i; j++){
		if (vetor[j] > vetor[j+1]){
			int aux = vetor[j];
			vetor[j] = vetor[j+1];
			vetor[j+1] = aux;		
		}
	}
	return bubbleSortRecursivo(vetor, tamanho, i+1);
	
	//f(1) = 1
	//f(n) = c.(n-1) + f(n-1) 							-> primeira execução
	//f(n) = c.(n-1) + c.(n-2) + f(n-2)					-> segunda execução
	//f(n) = c.(n-1) + c.(n-2) + c.(n-3) + f(n-3)		-> terceira execução

	//f(n) = somatório (c.(n-i)) + f(n-k) de i=1 até k	-> recorrência genérica
	//com o caso base: f(1) = 1 -> f(1) = f(n-k) então n-k = 1 -> k = n-1
	//retomando:
	//f(n) = somatório (c.(n-i)) + 1 de i=1 até n-1
	//f(n) = c.somatório (n-i) + 1 de i=1 até n-1
	//Por meio de Progressão Aritmética: ((número de termos*(primeiro termo+ultimo termo))/2
	//	((n-1).((n-1)+(n-(n-1))))/2 = c[(n.n - n)/2] + 1
}

int main(int argc, char* argv[]){
	int geracaoVetor = atoi(argv[1]);
	int tamanhoVetor = atoi(argv[2]);
	clock_t inicio, final;
	
	//geração dos elementos
	int *vetorInsertion = malloc(tamanhoVetor * sizeof(int));
	int *vetorMerge = malloc(tamanhoVetor * sizeof(int));
	int *vetorBubble = malloc(tamanhoVetor * sizeof(int));
	srand(time(NULL));
	
	int i;
	for (i=0; i<tamanhoVetor; i++){
		if (geracaoVetor == 0) //aleatório
			vetorInsertion[i] = rand() % 1000;
		else if (geracaoVetor == 1) //ordenado
			vetorInsertion[i] = i;
		else if (geracaoVetor == 2) //invertido
			vetorInsertion[i] = tamanhoVetor - i;
		else if (geracaoVetor == 3 && i<=tamanhoVetor/2) //primeira metade ordenada e o restante aleatório
			vetorInsertion[i] = i;
		else if (geracaoVetor == 3) //primeira metade ordenada e o restante aleatório
			vetorInsertion[i] = (rand() % 1000) + i;
		vetorMerge[i] = vetorInsertion[i];
		vetorBubble[i] = vetorInsertion[i];
	}
	
	printf("Insertion Gerado: ");
	imprimeVetor(vetorInsertion, tamanhoVetor);
	inicio = clock();
	vetorInsertion = insertionSort(vetorInsertion, tamanhoVetor);
	final = clock();
	printf("Insertion Ordenado: ");
	imprimeVetor(vetorInsertion, tamanhoVetor);
	printf("Tempo de ordenacao Insertion: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetorInsertion);

	printf("Merge Gerado: ");
	imprimeVetor(vetorMerge, tamanhoVetor);
	inicio = clock();
	mergeSort(vetorMerge, 0, tamanhoVetor-1);
	final = clock();
	printf("Merge Ordenado: "); 
	imprimeVetor(vetorMerge, tamanhoVetor);
	printf("Tempo de ordenacao Merge: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetorMerge);

	printf("Bubble Gerado: ");
	imprimeVetor(vetorBubble, tamanhoVetor);
	inicio = clock();
	bubbleSort(vetorBubble, tamanhoVetor);
	final = clock();
	printf("Bubble Ordenado: "); 
	imprimeVetor(vetorBubble, tamanhoVetor);
	printf("Tempo de ordenacao Bubble: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetorBubble);
	
	return 0;	
}


/*
	Função de eficiência/recorrência:
	- Vantagem: análise mais precisa
	- Desvantagem: custosa para obter

	Tempo de execução:
	- Vantagem: mais simples (medir o tempo)
	- Desvantagem: não é tão precisa

	Ter resultados mais consistentes (tempo de execução):
	- executar o mesmo experimento k vezes
	- obter a média dos valores
	- calcular o desvio padrão (expressa a divergencia dos resultados):
		- desvio padrão pequeno -> grande parte dos meus resultados são próximos da média
		- desvio padrão grande -> grande parte dos meus resultados estão distantes da média

	Aleatório (Merge < Insertion < Bubble):
	tamanho		Insertion	Merge		Bubble
	10000		0,078125	0,00		 0,1875
	100000		5,906250	0,015625	32,421875

	Ordenado (Insertion < Merge < Bubble):
	tamanho		Insertion	Merge		Bubble
	10000		0,00		0,00		 0,109375
	100000		0,00		0,015625	10,890625

	Invertido (Merge < Insertion < Bubble):
	tamanho		Insertion	Merge		Bubble
	10000		 0,109375	0,015625	 0,156250
	100000		12,812500	0,015625	20,375000

	Parcialmente Ordenado (Merge < Insertion < Bubble):
	tamanho		Insertion	Merge		Bubble
	10000		0,00		0,00		0,093750
	100000		0,015625	0,00		13,890625

	Interpretação dos resultados:
	- De forma geral, o Merge se sobressai aos demais
	- Bubble Sort é o pior em todos os casos
	- Insertion Sort se comporta melhor quando os dados estão ordenados
	- Bubble Sort é altamente influenciado pelo tamanho da entrada (taxa de crescimento é mais alta: complexidade, 			gráficos)
	- Merge Sort não é tão influenciado pelo tamanho da entrada

	**segundo resultado, fica claro que precisamos executar k vezes e obter a média
*/
