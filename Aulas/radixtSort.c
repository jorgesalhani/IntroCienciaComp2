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
	De forma geral, os melhores algoritmos de compara��o s�o n.log(n)
	Bucket Sort � fundamentado em listas encadeadas chamadas de bucket
	Cada lista esta associada a uma chave espec�fica
	O ganho na complexidade f(n) < n.log(n) vem com o custo adicional de aloca��o de mem�ria auxiliar.
	
	Exemplo : [1 5 0 0 5 1 2 5 3 1]
	
	1) Percorrer as chaves e verificar o m�nimo e m�ximo (m�nimo = 0; m�ximo = 5)
	2) Cria��o de um vetor adicional de listas (buckets):
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
	
	Ent�o: f(n) = 3n + k; O(n+k)
	
	Observa��o:
	- chaves discretas e desejavelmente inteiros
	- aloca��o de mem�ria auxiliar
	- em termos de mem�ria gastamos um pouco mais, pois temos uma lista encadeada com ponteiros
*/

void bucketSort(Record* vetor, int tamanho){
	//1) Percorrer as chaves e verificar o m�nimo e m�ximo
	int max, min;
	max = min = vetor[0].key;
	int i = 0;
	for(i = 0; i<tamanho; i++){
		if (vetor[i].key > max) max = vetor[i].key;
		if (vetor[i].key < min) min = vetor[i].key;
	}
	
	//2) Cria��o de um vetor adicional de listas (buckets)
	Bucket* B = (Bucket*) calloc(max-min+1, sizeof(Bucket));
	
	//3) Percorrer o vetor e preencher os buckets de acordo com as chaves
	for(i = 0; i<tamanho; i++){
		int posicaoKey = vetor[i].key - min;
		
		//criando novo n�
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

/*
	Etapas:
	- divide a chave em partes segundo uma base (8, 10, 256, ...	)
	- para cada parte aplica CountigSort ou BucketSort

	Exemplo: [70 9 25 105 472 371 290 230 41 36 99 101 76 6]
	- para bucket ou counting ter�amos (472-6+1= 467) chaves, ou seja, 467 filas ou espa�o em um vetor de contagem
	- com radix, o tamanho de k passa a ser o valor da base
	- a ideia � fazer alinhamentos considerando d�gitos menos significativos para os mais significativos

	[070 009 025 105 472 371 290 230 041 036 099 101 076 006] para a base 10
	- considerar somente o d�gito menos significativo (unidade):  
		[070 290 230 371 041 101 472 025 105 036 076 006 009 099] -> com Counting ou Bucket
	- considerar somente o segundo d�gito menos significativo (dezena):  
		[101 105 006 009 025 230 036 041 070 371 472 076 290 099] -> com Counting ou Bucket
	- considerar somente o terceiro d�gito menos significativo (centena):  
		[006 009 025 036 041 070 076 099 101 105 230 290 371 472] -> com Counting ou Bucket
			   0 1 2 3 4 5 6 7 8 9
	Counting: [3 3 1 0 0 2 3 0 0 2]

	[070 290 230 371 041 101 472 025 105 036 076 006 009 099]

	Assim, no RadixSort:
	- o tamanho de k � fixo para Counting ou Bucket
	- o tamanho da base indica quantas itera��es ser�o necess�rias
	- com a entrada pequena, Radix n�o � favor�vel, pois tem todo o controle das parti��es
	- tamb�m, se a amplitude das chaves for pequena
	- ideal para entradas grandes e chaves esparsadas

	Na pr�tica � muito comum utilizar 256 como base, pois:
	- inteiros geralmente possuem 32 bits, gerando 4 parti��es de 8 bits cada (1 byte), ou seja, 4 itera��es
	- cada parti��o varia de 0 a 255, ou seja, 1 d�gito!
	- extremos, base 2^1, executa-se 32 vezes
	- extremos, base 2^32, executa-se 1 vez, ou seja, Counting e Bucket originais
*/
void radixSort(Record* vetor, int tamanho){
	//particionar em d�gitos com a base 256 e CountingSort

	//aloca��o dos vetores e vetor de c�pia
	int contagem[256] = {0};
	int acumulada [256];
	Record* copia = (Record*) malloc(tamanho * sizeof(Record));

	//particionar a chave em d�gitos seguindo a base

	//primeira itera��o
	//qqqqqqqqwwwwwwwweeeeeeeerrrrrrrr (entrada)
	//                        &&&&&&&& (operador)
	//00000000000000000000000011111111 (modificador)
	//000000000000000000000000rrrrrrrr (sa�da)

	//segunda itera��o
	//qqqqqqqqwwwwwwwweeeeeeeerrrrrrrr (entrada)
	//00000000qqqqqqqqwwwwwwwweeeeeeee (deslocamento)
	//                        &&&&&&&& (operador)
	//00000000000000000000000011111111 (modificador)
	//000000000000000000000000eeeeeeee (sa�da)

	//terceira itera��o
	//qqqqqqqqwwwwwwwweeeeeeeerrrrrrrr (entrada)
	//0000000000000000qqqqqqqqwwwwwwww (deslocamento)
	//                        &&&&&&&& (operador)
	//00000000000000000000000011111111 (modificador)
	//000000000000000000000000wwwwwwww (sa�da)

	int i, shift;
	for (shift = 0; shift <= 24; shift += 8){ //controle do radix
		//Counting Sort: contagem + c�pia
		for (i = 0; i < tamanho; i++){
			short k = (vetor[i].key >> shift) & 255;
			contagem[k]++;
			copia[i] = vetor[i];
		}

		//Counting Sort: contagem acumulada
		acumulada[0] = 0;
		for (i = 1; i < 256; i++){
			acumulada[i] = acumulada[i-1] + contagem[i-1];
			contagem[i-1] = 0; //zerando a posi��o para a pr�xima itera��o
		
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
	Ordena��o: tornar a busca de dados mais eficiente
	- chaves (tipo, distribui��o)
	- estrutura dos dados (vetores, listas, filas, �rvores)
	- localiza��o dos dados (mem�ria secund�ria ou prim�ria)
	- restri��es (mem�ria, tempo de processamento)


	Busca Sequencial:
	- praticamente for�a bruta
	- complexidade linear O(n)
	- total: k . O(n)

	Busca Sequencial Indexada: objetivo (ser melhor que k . O(n))
	- poss�vel de implementar quando o vetor est� ordenado entre blocos
	- Percorrer o vetor para encontrar o vetor de �ndices: 
		- O(n) de constru��o e O(i) para mem�ria, com i sendo quantidade de blocos (i = n/tamanho_bloco)
	- Ao buscar uma chave consulta o vetor de �ndice (log2(i)) e percorre o bloco (n/i)

	- Exemplo:
		[3 6 4 9 | 13 11 16 19 | 22 21 29 27 | ...] vetor ordenado entre os blocos
		[3 11 21 ...] vetor de �ndices com o menor valor dos blocos
		[0  4  7 ...] posi��o inicial de cada bloco
	
	- Complexidade:
		- constru��o do �ndice: O(n)
		- buscas: k * (log2(i) + n/i)
		- ent�o: k * O(n) > O(n) + k * (log2(i) + n/i)
	- Assim, para k = 1000 (buscas), n = 1000 (tamanho do vetor) e i = 10 (blocos)
		- sequencial = k * n = 1000 * 1000 = 1000000
		- indexada = 1000 + 1000 (4 + 100) = 1000 + 104000 = 105000
		- neste exemplo, quase 90% de ganho na performance
	
	Busca Bin�ria:
	- dados est�o previamente ordenados
	- complexidade final (ordena��o + busca)
	- total: O(x) + k * O(log(n)), x sendo a complexidade da ordena��o
	- compara a chave com o valor central, selecionando uma das metades para continuar a busca
	- exemplo: buscar 9
		[3 4 6 8 9 10 11 13 15 16] -> valor central 10
		[3 4 6 8 9] -> valor central 6
		[8 9] -> valor 9, retorna o valor

	Busca Bin�ria com Interpola��o:
	- conhecimento pr�vio: distribui��o das chaves com crescimento linear
	- interpola��o: (inicio + (chave - vetor[inicio]) * (fim - inicio)) / (vetor[fim] - vetor[inicio])

	- Exemplo 1:
	     0 1 2 3 4  5  6  7  8  9
		[3 4 6 8 9 10 11 13 15 16] vetor ordenado com varia��o do valor das chaves entre 1 e 2
		buscar o valor 9:
		interpola��o = (0 + (9 - 3) * (9 - 0)) / (16-3)
					 = (0 + 6*9) / 13
					 = 54 / 13
					 = 4.15 -> posi��o 4

	- Exemplo 2:
	     0 1 2 3 4  5  6  7  8  9
		[3 4 6 8 9 10 11 13 15 99] vetor ordenado com varia��o do valor das chaves entre 1 e 2
		interpola��o = (0 + (9 - 3) * (9 - 0)) / (99-3)
					 = (0 + 6*9) / 96
					 = 54 / 96
					 = 0.56 -> posi��o 0

	- Complexidade = O(log2(log2(n)))
*/