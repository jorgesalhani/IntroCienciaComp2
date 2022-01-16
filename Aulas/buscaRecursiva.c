#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	B(Sequencial - n) > B(Binaria - log n)
	Bs(n) < Bb(log n) + T(n.n) : é verdadeiro e quando é verdadeiro

	O diferencial é a quantidade de vezes que eu faço a busca!!! (k)
	Bs(n).k > Bb(log n).k + T(n.n) 
	--> quando k é "pequeno" é mais vantajoso usar Busca Sequencial
	--> quando k é "grande" é mais vantajoso usar Busca Binária

	Observação:
	- Precisamos estudar o cenário por completo!!!
	- Quando olhamos os métodos separadamente, sabemos que Busca Binária é menos complexa
	- Quando incluimos a ordenação, a Busca Sequencial passa a ser menos complexa
	- Quando vamos executar este cenário k vezes, depende do valor de k

	Exemplo:
	f(n) = n + 3
	g(n) = n + 4
	Qual é melhor? f(n)
		-> n = 1 -> f(1) = 4; g(1) = 5 --- 20%
		-> n = 100000 -> f(100000) = 100003; g(100000) = 100004 -- 0.000..%
*/



/*
	Busca Sequencial: percorre todo o vetor para tentar encontrar o elemento desejado
	Parâmetros:
		- int* vetor: dado de entrada
		- int tamanhoVetor: indica a parte do vetor a ser percorrida
		- int numero: elemento a ser buscado
	Retorno:
		- int (posicao): posição do elemento buscado
*/

int busca_sequencial(int* vetor, int tamanhoVetor, int numero){
	if (vetor[tamanhoVetor-1] == numero) return tamanhoVetor-1; //valor encontrado
	if (tamanhoVetor == 0) return -1; //valor não encontrado; chegamos ao final do vetor
	return busca_sequencial(vetor, tamanhoVetor-1, numero); //ainda não encontramos o valor
}

/*
	Busca Binária: percorre todo o vetor para tentar encontrar o elemento desejado
	Parâmetros:
		- int* vetor: dado de entrada
		- int tamanhoVetor: indica a parte do vetor a ser percorrida
		- int numero: elemento a ser buscado
	Retorno:
		- int (posicao): posição do elemento buscado
	Requisitos:
		- o vetor deve estar ordenado
*/

int busca_binaria(int* vetor, int posicaoInicial, int posicaoFinal, int numero){
	int centro = (int)((posicaoInicial+posicaoFinal)/2);
	printf("valor inicial %i; valor final %i; valor central %i\n", 
		vetor[posicaoInicial], vetor[posicaoFinal], vetor[centro]);
	
	if (numero == vetor[centro]) //valor encontrado
		return centro; 
	if (posicaoInicial > posicaoFinal) //valor não encontrado
		return -1; 
	if (numero < vetor[centro]) //se existir, primeira metade
		return busca_binaria(vetor, posicaoInicial, centro-1, numero);
	if (numero > vetor[centro]) //se existir, segunda metade
		return busca_binaria(vetor, centro+1, posicaoFinal, numero); 

	//Quantas comparações (operação mais importante na busca)? 4 comparações
	//f(n) = 4 + f(n/2^1)				//4.1 + f(n/2^1)
	//	   = 4 + [4 + f(n/2^2)]			//4.2 + f(n/2^2)
	//	   = 4 + [4 + [4 + f(n/2^3)]]]	//4.3 + f(n/2^3)
	//....
	//	   = 2 + n/2^k

	//Matematicamente, nós temos que n = 2^k --> k = log(2) n

	//f(n) = 4. log(2) n 
}

int* insertionSort(int* vetor, int tamanho);

int main(void){
	//geração dos elementos
	int tamanhoVetor = 10;
	int *vetor = malloc(tamanhoVetor * sizeof(int));
	srand(time(NULL));
	
	int i;
	for (i=0; i<tamanhoVetor; i++){
		vetor[i] = rand() % 1000;
		printf("%i ", vetor[i]);
	}
	
	//leitura do elemento de busca
	int numero;
	printf("\nDigite o numero a ser buscado no vetor: ");
	scanf("%d", &numero);

	//busca do elemento desejado
	//int posicao = busca_sequencial(vetor, tamanhoVetor, numero);

	vetor = insertionSort(vetor, tamanhoVetor);
	int posicao = busca_binaria(vetor, 0, tamanhoVetor-1, numero);
	
	//resultado
	printf("O numero %i esta na posicao %i\n", numero, posicao);
	free(vetor);
	
	return 0;	
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
		
		int k;
		for (k=0; k<tamanho; k++) printf("%i ", vetor[k]);
		printf("- analise posicao %i\n", j);
	}
	
	return vetor;
}
