#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	Relembrando os v�deos:
	- Algoritmo: 
	--- uma sequ�ncia de passos l�gicos;
	--- � correto se, e somente se, para toda inst�ncia de entrada a sa�da � correta
	--- diferentes solu��es podem ser implementadas, cada uma com sua complexidade
	--- uma solu��o perfeita, pode n�o ser a "melhor solu��o" (solu��es aproximadas)
	
	- Como calcular a efici�ncia de um algoritmo (baseado no tamanho da entrada):
	--- tempo de execu��o: mesma m�quina e no mesmo estado
	--- contagem de passos:
		-- opera��es aritm�ticas e atribui��es;
		-- compara��es;
		-- resolver um ponteiro ou acesso �s indexa��es;
		-- acesso e retorno �s fun��es.
		
	- Vamos fixar estes conceitos por meio da Busca Sequencial e Busca Bin�ria:
	--- requisito b�sico para motores de busca na internet, base de dados, etc
*/

/*
	Descri��o: gera valores aleat�rios para um vetor de tamanho qtdade com valores entre minimo e maximo
	Par�metros:
		- int qtdade: tamanho do vetor a ser gerado
		- int minimo: valor minimo que pode ser gerado
		- int maximo: valor maximo que pode ser gerado
	Retorno:
		- int* vetorGerado: vetor de tamanho qtdade preenchido pela fun��o
	Observa��es:
		- vetor n�o tem controle de ordena��o e pode ter valores repetidos.
*/
int* gerarVetorNaoOrdenado(int qtdade, int minimo, int maximo){
	//srand()

	int* vetorGerado = malloc(qtdade * sizeof(int));
	
	int i;
	for (i = 0; i < qtdade; i++){ //gera valores aleat�rios entre mimino e maximo
		vetorGerado[i] = rand() % (maximo-minimo+1) + minimo; //rand() % (20 - 11 + 1) + 11
		printf("%i ", vetorGerado[i]);
	}
	
	return vetorGerado;
}

int* gerarVetor(int qtdade, int minimo, int maximo){
	//srand()

	int* vetorGerado = malloc(qtdade * sizeof(int));

	vetorGerado[0] = minimo;
	printf("%i ", vetorGerado[0]);

	int i;
	for (i = 1; i < qtdade; i++){ //gera valores aleat�rios entre mimino e maximo
		vetorGerado[i] = rand() % (maximo-minimo+1) + minimo + vetorGerado[i-1]; //rand() % (20 - 11 + 1) + 11
		printf("%i ", vetorGerado[i]);
	}
	
	return vetorGerado;
}


/*
	Descri��o: c�digo pequeno; basicamente � uma busca por for�a bruta; fazendo a busca sem nenhuma estrat�gia mais elaborada
	Par�metros:
		- int* vetor: conjunto de dados de busca
		- int tamanho: tamanho do vetor de busca
		- int chave: valor a ser buscado
	Retorno:
		- int (posicao): localiza��o do elemento buscado
	Contagem de opera��es:
		- (A) atribui��o e aritm�ticas
		- (C) compara��o
		- (V) acesso ao vetor
		- (F) acesso ou retorno de fun��o
	N�s consideramos que todas as opera��es levam aproximadamente o tempo de execu��o
	Quando n�s temos fluxos exclusivos, considera-se o pior caso!!!
	De termos gerais, a busca Sequencial � totalmente dependente do tamanho "n"
		- quanto mais n aumenta, maior � a quantidade de opera��es realizadas
	- Qual � o melhor caso? o n�mero buscado � o primeiro
	- Qual � o pior caso? o n�mero buscado n�o existe
	- Ser� que se eu usar o while / do while no lugar do for, a fun��o de efici�ncia ser� a mesma? 
*/
int buscaSequencial(int* vetor, int tamanho, int chave){
	int i;
	for (i = 0; i < tamanho; i++)	//1 vez (A + C); outras vezes (2A + C).(n - 1)
		if (vetor[i] == chave)		//n(V + C) 
			return i;				//F
	return -1;						//F (n�o � executada) -> descartar
	//i++ <==> i = i + 1 (soma e atribui��o) = 2A

	//f(n) = A + C + (2A + C).(n - 1) + n(V + C) + F
	//f(n) = A + C + 2An - 2A + Cn - C + Vn + Cn + F
	//f(n) = 

	//n = 1: vamos ter 5 opera��es
}

/*
	Descri��o: busca bin�ria realiza a divis�o do vetor em partes (metades) baseando-se no c�lculo do elemento central
		- requisito: o vetor precisa estar ordenado
		- especifica um espa�o de busca, ou seja, regi�es reduzidas como entrada da fun��o
	Par�metros:
		- int* vetor: vetor de entrada
		- int posicaoInicial: posi��o do primeiro elemento do vetor
		- int posicaoFinal: posica��o do �ltimo elemento do vetor
		- int chave: elemento a ser buscado
	Retorno:
		- int (posicao): posi��o do elemento buscado
	Se o vetor estiver ordenado, com certeza a buscaBinaria � mais eficiente que a buscaSequencial (tempo) - no pior caso
	Se o vetor n�o ordenado � necess�rio fazer a ordena��o
*/
int buscaBinaria(int* vetor, int posicaoInicial, int posicaoFinal, int chave){
	while(posicaoInicial <= posicaoFinal){ //log n
		int centro = (int)((posicaoInicial+posicaoFinal)/2);
		printf("valor inicial %i; valor final %i; valor central %i\n", 
			vetor[posicaoInicial], vetor[posicaoFinal], vetor[centro]);
		
		if (chave == vetor[centro]) return centro; //valor encontrado 
		
		if (chave < vetor[centro]) //se o n�mero existir estar� na primeira metade
			posicaoFinal = centro - 1;
		if (chave > vetor[centro]) //se o n�mero existir estar� na segunda metade
			posicaoInicial = centro + 1;
	}
	return -1;//valor n�o encontrado
}

int main(int argc, char* argv[]){
	//lendo par�metros iniciais
	int qtdade = atoi(argv[1]);
	int minimo = atoi(argv[2]);
	int maximo = atoi(argv[3]);
	
	//gerando o vetor de dados
	int* vetor = gerarVetor(qtdade, minimo, maximo);
	
	//buscando um valor informado
	int chave;
	printf("\nDigite a chave a ser buscada: ");
	scanf("%i", &chave);
	
	clock_t inicio = clock();
	//int posicao = buscaSequencial(vetor, qtdade, chave);
	int posicao = buscaBinaria(vetor, 0, qtdade-1, chave);
	clock_t final = clock();
	double tempo = (final-inicio)/(double)CLOCKS_PER_SEC;
	printf("Tempo de busca: %lf a\n", tempo);
	
	//informando a sa�da ao usu�rio
	if (posicao >= 0 )
		printf("Valor encontrado na posicao %i\n", posicao);
	else
		printf("Valor nao encontrado\n");
	
	//desalocando o vetor din�mico
	free(vetor);
	
	return 0;
}
