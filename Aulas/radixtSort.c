#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	int key;
	int value;
	//outros atributos
} Record;

typedef struct node{
	Record elem;
	struct node* next;
} Node;

typedef struct bucket{
	Node* begin;
	Node* end;
} Bucket;

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
	De forma geral, os melhores algoritmos de comparação são n.log(n)
	Bucket Sort é fundamentado em listas encadeadas chamadas de bucket
	Cada lista esta associada a uma chave específica
	O ganho na complexidade f(n) < n.log(n) vem com o custo adicional de alocação de memória auxiliar.
	
	Exemplo : [1 5 0 0 5 1 2 5 3 1]
	
	1) Percorrer as chaves e verificar o mínimo e máximo (mínimo = 0; máximo = 5)
	2) Criação de um vetor adicional de listas (buckets):
		 0 1 2 3 4 5
		[           ]
	3) Percorrer o vetor e preencher os buckets de acordo com as chaves:
		 0 1 2 3 4 5
		[           ]
		 | | | | | |
		 0 1 2 3   5
		 0 1       5
		   1       5
	4) Posicionar os elementos no vetor original, retirando elementos da lista:
		original			 bucket
	 0 1 2 3 4 5 6 7 8 9       0      1       2   3   4  5
	[1 5 0 0 5 1 2 5 3 1]	 [(0, 0) (1 1 1) (2) (3) () (5 5 5)]
	[0 5 0 0 5 1 2 5 3 1]	 [(0)    (1 1 1) (2) (3) () (5 5 5)]
	[0 0 0 0 5 1 2 5 3 1]	 [()     (1 1 1) (2) (3) () (5 5 5)]
	[0 0 1 0 5 1 2 5 3 1]	 [()     (1 1)   (2) (3) () (5 5 5)]
	[0 0 1 1 5 1 2 5 3 1]	 [()     (1)     (2) (3) () (5 5 5)]
	[0 0 1 1 1 1 2 5 3 1]	 [()     ()      (2) (3) () (5 5 5)]
	[0 0 1 1 1 2 2 5 3 1]	 [()     ()      ()  (3) () (5 5 5)]
	[0 0 1 1 1 2 3 5 3 1]	 [()     ()      ()  ()  () (5 5 5)]
	[0 0 1 1 1 2 3 5 3 1]	 [()     ()      ()  ()  () (5 5)  ]
	[0 0 1 1 1 2 3 5 5 1]	 [()     ()      ()  ()  () (5)    ]
	[0 0 1 1 1 2 3 5 5 5]	 [()     ()      ()  ()  () ()     ]
	
	Complexidade:
	- 1) n
	- 2) 
	- 3) n
	- 4) k + n
	
	Então: f(n) = 3n + k; O(n+k)
	
	Observação:
	- chaves discretas e desejavelmente inteiros
	- alocação de memória auxiliar
	- em termos de memória gastamos um pouco mais, pois temos uma lista encadeada com ponteiros
*/

void bucketSort(Record* vetor, int tamanho){
	//1) Percorrer as chaves e verificar o mínimo e máximo
	int max, min;
	max = min = vetor[0].key;
	int i = 0;
	for(i = 0; i<tamanho; i++){
		if (vetor[i].key > max) max = vetor[i].key;
		if (vetor[i].key < min) min = vetor[i].key;
	}
	
	//2) Criação de um vetor adicional de listas (buckets)
	Bucket* B = (Bucket*) calloc(max-min+1, sizeof(Bucket));
	
	//3) Percorrer o vetor e preencher os buckets de acordo com as chaves
	for(i = 0; i<tamanho; i++){
		int posicaoKey = vetor[i].key - min;
		
		//criando novo nó
		Node* novo = malloc(sizeof(Node));
		novo->elem = vetor[i];
		novo->next = NULL;
		
		//inserindo na fila
		if (B[posicaoKey].begin == NULL)
			B[posicaoKey].begin = novo;
		else
			(B[posicaoKey].end)->next = novo;
		B[posicaoKey].end = novo;
	}
	
	//4) Posicionar os elementos no vetor original, retirando elementos da lista
	int j = 0;
	for(i = 0; i<=(max-min); i++){
		Node* posicao;
		posicao = B[i].begin;
		while(posicao != NULL){
			vetor[j] = posicao->elem;
			j++;
			
			Node *deletar = posicao;
			posicao = posicao->next;
			B[i].begin = posicao;
			free(deletar);
		}
	}
	free(B);
}

/*
	De forma geral, os melhores algoritmos de comparação são n.log(n)
	Counting Sort é fundamentado em contagens e não comparações
	O ganho na complexidade f(n) < n.log(n) vem com o custo adicional de alocação de memória auxiliar.
	
	Exemplo com structs: [1 5 0 0 5 1 2 5 3 1] - keys
	
	- 1) Cópia completa dos dados originais.
	- 2) Alocação de memória: (referência das chaves a serem ordenadas)
		2.1) Percorrer as chaves e verificar o mínimo e máximo (mínimo = 0; máximo = 5)
		2.2) Criação de um vetor adicional de contagem:
			[0 0 0 0 0 0]
		2.3) Percorrer o vetor de contagem com o somatório por chave:
			[2 3 1 1 0 3]
	- 3) Contagem acumulada de frequências (chaves discretas)
			[0 2 5 6 7 7]
	- 4) Posicionamento de chaves (forma ordenada): cópia: [1 5 0 0 5 1 2 5 3 1] 
		original			  contagem acumulada
	 0 1 2 3 4 5 6 7 8 9      0 1 2 3 4 5
	[1 5 0 0 5 1 2 5 3 1]	 [0 2 5 6 7 7] - chave 1 (cópia) para a posição 2 (contagem); posiciona e soma posição;
	[1 5 1 0 5 1 2 5 3 1]	 [0 3 5 6 7 7] - chave 5 (cópia) para a posição 7 (contagem); posiciona e soma posição;
	[1 5 1 0 5 1 2 5 3 1]	 [0 3 5 6 7 8] - chave 0 (cópia) para a posição 0 (contagem); posiciona e soma posição;
	[0 5 1 0 5 1 2 5 3 1]	 [1 3 5 6 7 8] - chave 0 (cópia) para a posição 1 (contagem); posiciona e soma posição;
	[0 0 1 0 5 1 2 5 5 1]	 [2 3 5 6 7 8] - chave 5 (cópia) para a posição 8 (contagem); posiciona e soma posição;
	[0 0 1 1 5 1 2 5 5 1]	 [2 3 5 6 7 9] - chave 1 (cópia) para a posição 3 (contagem); posiciona e soma posição;
	[0 0 1 1 5 2 2 5 5 1]	 [2 4 5 6 7 9] - chave 2 (cópia) para a posição 5 (contagem); posiciona e soma posição;
	[0 0 1 1 5 2 2 5 5 1]	 [2 4 6 6 7 9] - chave 5 (cópia) para a posição 9 (contagem); posiciona e soma posição;
	[0 0 1 1 5 2 2 5 5 5]	 [2 4 6 6 7 10] - chave 3 (cópia) para a posição 6 (contagem); posiciona e soma posição;
	[0 0 1 1 5 2 3 5 5 5]	 [2 4 6 7 7 10] - chave 1 (cópia) para a posição 4 (contagem); posiciona e soma posição;
	[0 0 1 1 1 2 3 5 5 5]	 [2 5 6 7 7 10] - fim
	
	Complexidade:
	- 1.1 - malloc)
	- 2.1 - copia,max,min ) n
	- 2.2 - calloc)
	- 2.3 - contagem) n
	-   3 - cont. acumulada) k
	-   4 - posicionamento) n
	
	Então: f(n) = 3n + k; O(n+k)
	
	Observação:
	- a ordem relativa dos elementos de uma mesma chave é perservada (algoritmo estável)
	- requer dois vetores auxiliares: um de tamanho n e outro de tamanho k
	- a função de eficiência é totalmente dependente da quantidade de chaves (k)
	- se todas as chaves são diferentes e sequenciais, então k=n e O(2n)
*/

void countingSort(Record* vetor, int tamanho){
	//1) Cópia completa dos dados originais.
	Record* vetorAux = (Record*) malloc(tamanho * sizeof(Record));
	
	//2.1) Percorrer as chaves e verificar o mínimo e máximo
	int max, min;
	max = min = vetor[0].key;
	int i = 0;
	for(i = 1; i<tamanho; i++){
		if (vetor[i].key > max) max = vetor[i].key;
		if (vetor[i].key < min) min = vetor[i].key;
		vetorAux[i] = vetor[i];
	}

	//2.2) Criação de um vetor adicional de contagem [0 - 5] -> 6 posições [5-0+1]
	int* vetorContagem = (int*) calloc(max-min+1, sizeof(int));
	
	//2.3) Percorrer o vetor de contagem com o somatório por chave
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

/*
	Etapas:
	- divide a chave em partes segundo uma base (8, 10, 256, ...	)
	- para cada parte aplica CountigSort ou BucketSort

	Exemplo: [70 9 25 105 472 371 290 230 41 36 99 101 76 6]
	- para bucket ou counting teríamos (472-6+1= 467) chaves, ou seja, 467 filas ou espaço em um vetor de contagem
	- com radix, o tamanho de k passa a ser o valor da base
	- a ideia é fazer alinhamentos considerando dígitos menos significativos para os mais significativos

	[070 009 025 105 472 371 290 230 041 036 099 101 076 006] para a base 10
	- considerar somente o dígito menos significativo (unidade):  
		[070 290 230 371 041 101 472 025 105 036 076 006 009 099] -> com Counting ou Bucket
	- considerar somente o segundo dígito menos significativo (dezena):  
		[101 105 006 009 025 230 036 041 070 371 472 076 290 099] -> com Counting ou Bucket
	- considerar somente o terceiro dígito menos significativo (centena):  
		[006 009 025 036 041 070 076 099 101 105 230 290 371 472] -> com Counting ou Bucket
			   0 1 2 3 4 5 6 7 8 9
	Counting: [3 3 1 0 0 2 3 0 0 2]

	[070 290 230 371 041 101 472 025 105 036 076 006 009 099]

	Assim, no RadixSort:
	- o tamanho de k é fixo para Counting ou Bucket
	- o tamanho da base indica quantas iterações serão necessárias
	- com a entrada pequena, Radix não é favorável, pois tem todo o controle das partições
	- também, se a amplitude das chaves for pequena
	- ideal para entradas grandes e chaves esparsadas

	Na prática é muito comum utilizar 256 como base, pois:
	- inteiros geralmente possuem 32 bits, gerando 4 partições de 8 bits cada (1 byte), ou seja, 4 iterações
	- cada partição varia de 0 a 255, ou seja, 1 dígito!
	- extremos, base 2^1, executa-se 32 vezes
	- extremos, base 2^32, executa-se 1 vez, ou seja, Counting e Bucket originais
*/
void radixSort(Record* vetor, int tamanho){
	//particionar em dígitos com a base 256 e CountingSort

	//alocação dos vetores e vetor de cópia
	int contagem[256] = {0};
	int acumulada [256];
	Record* copia = (Record*) malloc(tamanho * sizeof(Record));

	//particionar a chave em dígitos seguindo a base

	//primeira iteração
	//qqqqqqqqwwwwwwwweeeeeeeerrrrrrrr (entrada)
	//                        &&&&&&&& (operador)
	//00000000000000000000000011111111 (modificador)
	//000000000000000000000000rrrrrrrr (saída)

	//segunda iteração
	//qqqqqqqqwwwwwwwweeeeeeeerrrrrrrr (entrada)
	//00000000qqqqqqqqwwwwwwwweeeeeeee (deslocamento)
	//                        &&&&&&&& (operador)
	//00000000000000000000000011111111 (modificador)
	//000000000000000000000000eeeeeeee (saída)

	//terceira iteração
	//qqqqqqqqwwwwwwwweeeeeeeerrrrrrrr (entrada)
	//0000000000000000qqqqqqqqwwwwwwww (deslocamento)
	//                        &&&&&&&& (operador)
	//00000000000000000000000011111111 (modificador)
	//000000000000000000000000wwwwwwww (saída)

	int i, shift;
	for (shift = 0; shift <= 24; shift += 8){ //controle do radix
		//Counting Sort: contagem + cópia
		for (i = 0; i < tamanho; i++){
			short k = (vetor[i].key >> shift) & 255;
			contagem[k]++;
			copia[i] = vetor[i];
		}

		//Counting Sort: contagem acumulada
		acumulada[0] = 0;
		for (i = 1; i < 256; i++){
			acumulada[i] = acumulada[i-1] + contagem[i-1];
			contagem[i-1] = 0; //zerando a posição para a próxima iteração
		
		}

		//Counting Sort: posicionar os elementos
		for (i = 0; i < tamanho; i++){
			short k = (copia[i].key >> shift) & 255;
			vetor[acumulada[k]] = copia[i];
			acumulada[k]++;
		}
	}

	free(copia);
}

int main(int argc, char* argv[]){
	int geracaoVetor = atoi(argv[1]);
	int tamanhoVetor = atoi(argv[2]);
	clock_t inicio, final;
	
	//geração dos elementos
	Record* vetor = (Record*) malloc(tamanhoVetor * sizeof(Record));
	srand(time(NULL));
	
	int i;
	for (i=0; i<tamanhoVetor; i++){
		if (geracaoVetor == 0) //aleatório
			vetor[i].key = rand() % 1000;
		else if (geracaoVetor == 1) //ordenado
			vetor[i].key = i;
		else if (geracaoVetor == 2) //invertido
			vetor[i].key = tamanhoVetor - i;
		else if (geracaoVetor == 3 && i<=tamanhoVetor/2) //primeira metade ordenada e o restante aleatório
			vetor[i].key = i;
		else if (geracaoVetor == 3) //primeira metade ordenada e o restante aleatório
			vetor[i].key = (rand() % 1000) + i;
		vetor[i].value = -(rand() % 1000);
	}
	
	printf("Radix Gerado: ");
	imprimeVetor(vetor, tamanhoVetor);
	inicio = clock();
	radixSort(vetor, tamanhoVetor);
	final = clock();
	printf("Radix Ordenado: "); 
	imprimeVetor(vetor, tamanhoVetor);
	printf("Tempo de ordenacao Radix: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetor);

	return 0;	
}

/*
	Ordenação: tornar a busca de dados mais eficiente
	- chaves (tipo, distribuição)
	- estrutura dos dados (vetores, listas, filas, árvores)
	- localização dos dados (memória secundária ou primária)
	- restrições (memória, tempo de processamento)


	Busca Sequencial:
	- praticamente força bruta
	- complexidade linear O(n)
	- total: k . O(n)

	Busca Sequencial Indexada: objetivo (ser melhor que k . O(n))
	- possível de implementar quando o vetor está ordenado entre blocos
	- Percorrer o vetor para encontrar o vetor de índices: 
		- O(n) de construção e O(i) para memória, com i sendo quantidade de blocos (i = n/tamanho_bloco)
	- Ao buscar uma chave consulta o vetor de índice (log2(i)) e percorre o bloco (n/i)

	- Exemplo:
		[3 6 4 9 | 13 11 16 19 | 22 21 29 27 | ...] vetor ordenado entre os blocos
		[3 11 21 ...] vetor de índices com o menor valor dos blocos
		[0  4  7 ...] posição inicial de cada bloco
	
	- Complexidade:
		- construção do índice: O(n)
		- buscas: k * (log2(i) + n/i)
		- então: k * O(n) > O(n) + k * (log2(i) + n/i)
	- Assim, para k = 1000 (buscas), n = 1000 (tamanho do vetor) e i = 10 (blocos)
		- sequencial = k * n = 1000 * 1000 = 1000000
		- indexada = 1000 + 1000 (4 + 100) = 1000 + 104000 = 105000
		- neste exemplo, quase 90% de ganho na performance
	
	Busca Binária:
	- dados estão previamente ordenados
	- complexidade final (ordenação + busca)
	- total: O(x) + k * O(log(n)), x sendo a complexidade da ordenação
	- compara a chave com o valor central, selecionando uma das metades para continuar a busca
	- exemplo: buscar 9
		[3 4 6 8 9 10 11 13 15 16] -> valor central 10
		[3 4 6 8 9] -> valor central 6
		[8 9] -> valor 9, retorna o valor

	Busca Binária com Interpolação:
	- conhecimento prévio: distribuição das chaves com crescimento linear
	- interpolação: (inicio + (chave - vetor[inicio]) * (fim - inicio)) / (vetor[fim] - vetor[inicio])

	- Exemplo 1:
	     0 1 2 3 4  5  6  7  8  9
		[3 4 6 8 9 10 11 13 15 16] vetor ordenado com variação do valor das chaves entre 1 e 2
		buscar o valor 9:
		interpolação = (0 + (9 - 3) * (9 - 0)) / (16-3)
					 = (0 + 6*9) / 13
					 = 54 / 13
					 = 4.15 -> posição 4

	- Exemplo 2:
	     0 1 2 3 4  5  6  7  8  9
		[3 4 6 8 9 10 11 13 15 99] vetor ordenado com variação do valor das chaves entre 1 e 2
		interpolação = (0 + (9 - 3) * (9 - 0)) / (99-3)
					 = (0 + 6*9) / 96
					 = 54 / 96
					 = 0.56 -> posição 0

	- Complexidade = O(log2(log2(n)))
*/