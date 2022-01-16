#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int busca_sequencial(int* vetor, int tamanhoVetor, int numero){
	if (vetor[tamanhoVetor-1] == numero) return tamanhoVetor-1; //valor encontrado
	if (tamanhoVetor == 0) return -1; //valor n�o encontrado; chegamos ao final do vetor
	return busca_sequencial(vetor, tamanhoVetor-1, numero); //ainda n�o encontramos o valor
}

int busca_binaria(int* vetor, int posicaoInicial, int posicaoFinal, int numero){
	int centro = (int)((posicaoInicial+posicaoFinal)/2);
	//printf("valor inicial %i; valor final %i; valor central %i\n", vetor[posicaoInicial], vetor[posicaoFinal], vetor[centro]);
	
	if (numero == vetor[centro]) //valor encontrado
		return centro; 
	if (posicaoInicial > posicaoFinal) //valor n�o encontrado
		return -1; 
	if (numero < vetor[centro]) //se existir, primeira metade
		return busca_binaria(vetor, posicaoInicial, centro-1, numero);
	if (numero > vetor[centro]) //se existir, segunda metade
		return busca_binaria(vetor, centro+1, posicaoFinal, numero); 
}

int* insertionSort(int* vetor, int tamanho);

void mergeSort(int* vetor, int inicio, int fim);
void intercala(int* vetor, int inicio, int centro, int fim);

int main(int argc, char* argv[]){
	int tamanhoVetor = atoi(argv[1]);
	char tipoBusca = argv[2][0];
	char tipoOrdenacao = argv[3][0];

	//gera��o dos elementos
	int *vetor = malloc(tamanhoVetor * sizeof(int));
	srand(time(NULL));
	
	int i;
	for (i=0; i<tamanhoVetor; i++){
		vetor[i] = rand() % 1000;
		printf("%i ", vetor[i]);
	}

	//ordena��o do vetor
	if (tipoOrdenacao == 'I')
		vetor = insertionSort(vetor, tamanhoVetor);
	else if (tipoOrdenacao == 'M')
		mergeSort(vetor, 0, tamanhoVetor-1);

	printf("\nOrdenado: ");
	for (i=0; i<tamanhoVetor; i++){
		printf("%i ", vetor[i]);
	}
	
	//leitura do elemento de busca
	int numero;
	printf("\nDigite o numero a ser buscado no vetor: ");
	scanf("%d", &numero);

	//busca do elemento desejado
	int posicao = -1;
	if (tipoBusca == 'S')
		posicao = busca_sequencial(vetor, tamanhoVetor, numero);
	else if (tipoBusca == 'B')
		posicao = busca_binaria(vetor, 0, tamanhoVetor-1, numero);
	
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

/*
	
	Fun��o de efici�ncia:
		- tempo de execu��o?
		- contagem de compara��es?
		- consumo de mem�ria?

	M�todo de ordena��o baseado em divis�o e conquista
	Exemplo:
		| [8 7 9 2 0 3 5 3] -> primeiro est�gio
		| [8 7 9 2] [0 3 5 3] -> mergeSort(0 a 3)
		| [8 7] [9 2] [0 3 5 3] -> mergeSort(0 a 1)
		| [8] [7] [9 2] [0 3 5 3] -> mergeSort(0 a 0)
		| [7 8] [9 2] [0 3 5 3] -> primeira conquista!!!
		[7 8] | [9 2] [0 3 5 3] -> intercala��o (0 a 1)
		[7 8] | [9] [2] [0 3 5 3] -> mergeSort(2 a 3)
		[7 8] | [2 9] [0 3 5 3] -> intercala��o(2 a 3)
		[2 7 8 9 ] | [0 3 5 3] -> intercala��o(0 a 3)
		...
		   i                   j
		[2 7 8 9 ] | [0 3 3 5] -> intercala��o(4 a 7)
		[0 2 3 3 5 7 8 9]
		   k
		[0 2 3 3 5 7 8 9] | -> intercala��o(0 a 7)

	Ideia para vetores impares
	[3 6 2] --> [3 6][2] ou [3] [6 2]
	[3 6] <-> [2] []
	[3][6]
	 i       j
	[3 6][2]
	[2 3 6]
*/

void mergeSort(int* vetor, int inicio, int fim){
	//caso base
	if (fim <= inicio) return;

	//processo de divis�o
	int centro = (int)((inicio+fim)/2.0);
	mergeSort(vetor, inicio, centro);
	mergeSort(vetor, centro+1, fim);

	//processo de conquista
	intercala(vetor, inicio, centro, fim);

	//f(n) = 1 + 3 + f(n/2) + 1 + f(n/2) + g(n)
}


void intercala(int* vetor, int inicio, int centro, int fim){
	//intercala��o
	int* vetorAux = (int*)malloc(sizeof(int) * (fim-inicio)+1);

	int i = inicio;	// indice da primeira lista ordenada
	int j = centro+1; //indice da segunda lista ordenada
	int k = 0; //indice do vetor auxiliar

	//compara e intercala os elementos do menor para o maior
	while(i <= centro && j <= fim){
		if (vetor[i] <= vetor[j]){ //verifica qual � o elemento menor entre as duas listas
			vetorAux[k] = vetor[i];
			i++; //proximo elemento da primeira metade
		}
		else{
			vetorAux[k] = vetor[j];
			j++; //proximo elemento da segunda metade
		}
		k++;
	}

	while(i <= centro){//h� elementos na primeira metade ainda?
		vetorAux[k] = vetor[i];
		i++;
		k++;
	}

	while(j <= fim){//h� elementos na segunda metade ainda?
		vetorAux[k] = vetor[j];
		j++;
		k++;
	}

	//atualizando o vetor original com o vetor auxiliar(ordenado)
	for(i = inicio, k = 0; i <= fim; i++,k++)
		vetor[i] = vetorAux[k];
	free(vetorAux);
}


/*
	MergeSort: encontrar a fun��o de efici�ncia
		- Opera��o mais relevante: compara��es
		- Definir o caso base (n�o � necess�rio executar novamente, ou seja, vetor unit�rio)
		- recorr�ncia

	Caso base:				1
	Recorr�ncia:			f(n) = 1 + f(n/2) + f(n/2) + g(n)
	Intercala��o: 			g(n) = 3n + 2 + (n + 1) = 4n + 3
	
	Ent�o:					f(n) = 1 + f(n/2) + f(n/2) + g(n)
							f(n) = 1 + f(n/2) + f(n/2) + 4n + 3
				(1.vez)		f(n) = 2f(n/2) + 4(n) + 4
				(2.vez)		f(n) = 2f[2f(n/4) + 4(n/2) + 4] + 4n + 4 
								 = 4f(n/4) + 8(n/2) + 8 + 4n + 4 
								 = 4f(n/4) + 8(n/2) + 4n + 12
				(3.vez)		f(n) = 4f[2f(n/8) + 4(n/4) + 4] + 8(n/2) + 4n + 12
								 = 8f(n/8) + 16(n/4) + 16 + 8(n/2) + 4n + 12
								 = 8f(n/8) + 16(n/4) + 8(n/2) + 4n + 28
								 = 8f(n/8) + 4n + 4n + 4n + 28
								 = 8f(n/8) + 12n + 28						* 28 = 16 + 8 + 4
				(k.vez)		f(n) = 2^k.f(n/2^k) + 4kn + somatorio(2^i)
							**observa��o: somatorio(2^i) para i = 2 at� k+1

	Caso base: 				f(1) = 1 
				at�			f(1) = f(n/2^k)
				ent�o		n/2^k = 1  				--> n = 2^k
				com log		log2(n) = log2(2^k) 		
				assim, 		k = log2(n)

	Voltando:				f(n) = 2^k.f(n/2^k) + 4kn + somatorio(2^i)
								 = 2^log2(n).f(1) + 4log2(n)n + somatorio(2^i)		***f(1) = 1
								 = 2^log2(n) + 4log2(n)n + somatorio(2^i)
							
							**observa��o: somatorio(2^i) para i = 2 at� log2(n)+1
							**Por Progress�o Geom�trica: 4n-4

				assim, 		f(n) = 2^log2(n) + 4log2(n)n + soma(2^i)
								 = n + 4n.log2(n) + 4n - 4
								 = 4n.log2(n) + 5n - 4

	Fun��o de recorr�ncia:
		- quais opera��es ser�o analisadas (compara��es? atribui��es e opera��es aritm�ticas?)
		- definir os termos constantes e a recursividade (quanto o espa�o reduz)
		- definir o caso base - condi��o de parada
		- encontrar a forma gen�rica da fun��o de recorr�ncia (k.vez)
		- definir o valor real de k, baseando-se no caso base
		- reescrever a forma gen�rica somente em fun��o de n (tamanho da entrada) e constantes
		----> fun��o de recorr�ncia final

		** Assumimos que todas as opera��es primitivas s�o equivalentes em sua execu��o
*/