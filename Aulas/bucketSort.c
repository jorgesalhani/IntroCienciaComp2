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
	
	printf("Bucket Gerado: ");
	imprimeVetor(vetor, tamanhoVetor);
	inicio = clock();
	bucketSort(vetor, tamanhoVetor);
	final = clock();
	printf("Bucket Ordenado: "); 
	imprimeVetor(vetor, tamanhoVetor);
	printf("Tempo de ordenacao Bucket: %lfs\n\n", (final-inicio)/(double)CLOCKS_PER_SEC);
	free(vetor);

	return 0;	
}