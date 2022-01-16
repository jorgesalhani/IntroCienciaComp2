#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	B(Sequencial - n) > B(Binaria - log n)
	Bs(n) < Bb(log n) + T(n.n) : � verdadeiro e quando � verdadeiro

	O diferencial � a quantidade de vezes que eu fa�o a busca!!! (k)
	Bs(n).k > Bb(log n).k + T(n.n) 
	--> quando k � "pequeno" � mais vantajoso usar Busca Sequencial
	--> quando k � "grande" � mais vantajoso usar Busca Bin�ria

	Observa��o:
	- Precisamos estudar o cen�rio por completo!!!
	- Quando olhamos os m�todos separadamente, sabemos que Busca Bin�ria � menos complexa
	- Quando incluimos a ordena��o, a Busca Sequencial passa a ser menos complexa
	- Quando vamos executar este cen�rio k vezes, depende do valor de k

	Exemplo:
	f(n) = n + 3
	g(n) = n + 4
	Qual � melhor? f(n)
		-> n = 1 -> f(1) = 4; g(1) = 5 --- 20%
		-> n = 100000 -> f(100000) = 100003; g(100000) = 100004 -- 0.000..%
*/



/*
	Busca Sequencial: percorre todo o vetor para tentar encontrar o elemento desejado
	Par�metros:
		- int* vetor: dado de entrada
		- int tamanhoVetor: indica a parte do vetor a ser percorrida
		- int numero: elemento a ser buscado
	Retorno:
		- int (posicao): posi��o do elemento buscado
*/

int busca_sequencial(int* vetor, int tamanhoVetor, int numero){
	if (vetor[tamanhoVetor-1] == numero) return tamanhoVetor-1; //valor encontrado
	if (tamanhoVetor == 0) return -1; //valor n�o encontrado; chegamos ao final do vetor
	return busca_sequencial(vetor, tamanhoVetor-1, numero); //ainda n�o encontramos o valor
}

/*
	Busca Bin�ria: percorre todo o vetor para tentar encontrar o elemento desejado
	Par�metros:
		- int* vetor: dado de entrada
		- int tamanhoVetor: indica a parte do vetor a ser percorrida
		- int numero: elemento a ser buscado
	Retorno:
		- int (posicao): posi��o do elemento buscado
	Requisitos:
		- o vetor deve estar ordenado
*/

int busca_binaria(int* vetor, int posicaoInicial, int posicaoFinal, int numero){
	int centro = (int)((posicaoInicial+posicaoFinal)/2);
	printf("valor inicial %i; valor final %i; valor central %i\n", 
		vetor[posicaoInicial], vetor[posicaoFinal], vetor[centro]);
	
	if (numero == vetor[centro]) //valor encontrado
		return centro; 
	if (posicaoInicial > posicaoFinal) //valor n�o encontrado
		return -1; 
	if (numero < vetor[centro]) //se existir, primeira metade
		return busca_binaria(vetor, posicaoInicial, centro-1, numero);
	if (numero > vetor[centro]) //se existir, segunda metade
		return busca_binaria(vetor, centro+1, posicaoFinal, numero); 

	//Quantas compara��es (opera��o mais importante na busca)? 4 compara��es
	//f(n) = 4 + f(n/2^1)				//4.1 + f(n/2^1)
	//	   = 4 + [4 + f(n/2^2)]			//4.2 + f(n/2^2)
	//	   = 4 + [4 + [4 + f(n/2^3)]]]	//4.3 + f(n/2^3)
	//....
	//	   = 2 + n/2^k

	//Matematicamente, n�s temos que n = 2^k --> k = log(2) n

	//f(n) = 4. log(2) n 
}

int* insertionSort(int* vetor, int tamanho);

int main(void){
	//gera��o dos elementos
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
	� medida que avan�a vai deixando os elementos � esquerda ordenados
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
	for(j = 1; j < tamanho; j++){//o elemento na posi��o 0 n�o precisa analisar
		int chave = vetor[j]; //vari�vel auxiliar, tempor�ria para armazenar o valor do momento
		int i = j - 1; //armazenar a posi��o de an�lise do momento
		while (i >= 0 && vetor[i] > chave){//final do vetor ; valor do vetor � maior que a chave de an�lise
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
