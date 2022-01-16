#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	Relembrando os vídeos:
	- Algoritmo: 
	--- uma sequência de passos lógicos;
	--- é correto se, e somente se, para toda instância de entrada a saída é correta
	--- diferentes soluções podem ser implementadas, cada uma com sua complexidade
	--- uma solução perfeita, pode não ser a "melhor solução" (soluções aproximadas)
	
	- Como calcular a eficiência de um algoritmo (baseado no tamanho da entrada):
	--- tempo de execução: mesma máquina e no mesmo estado
	--- contagem de passos:
		-- operações aritméticas e atribuições;
		-- comparações;
		-- resolver um ponteiro ou acesso às indexações;
		-- acesso e retorno às funções.
		
	- Vamos fixar estes conceitos por meio da Busca Sequencial e Busca Binária:
	--- requisito básico para motores de busca na internet, base de dados, etc
*/

/*
	Descrição: gera valores aleatórios para um vetor de tamanho qtdade com valores entre minimo e maximo
	Parâmetros:
		- int qtdade: tamanho do vetor a ser gerado
		- int minimo: valor minimo que pode ser gerado
		- int maximo: valor maximo que pode ser gerado
	Retorno:
		- int* vetorGerado: vetor de tamanho qtdade preenchido pela função
	Observações:
		- vetor não tem controle de ordenação e pode ter valores repetidos.
*/
int* gerarVetorNaoOrdenado(int qtdade, int minimo, int maximo){
	//srand()

	int* vetorGerado = malloc(qtdade * sizeof(int));
	
	int i;
	for (i = 0; i < qtdade; i++){ //gera valores aleatórios entre mimino e maximo
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
	for (i = 1; i < qtdade; i++){ //gera valores aleatórios entre mimino e maximo
		vetorGerado[i] = rand() % (maximo-minimo+1) + minimo + vetorGerado[i-1]; //rand() % (20 - 11 + 1) + 11
		printf("%i ", vetorGerado[i]);
	}
	
	return vetorGerado;
}


/*
	Descrição: código pequeno; basicamente é uma busca por força bruta; fazendo a busca sem nenhuma estratégia mais elaborada
	Parâmetros:
		- int* vetor: conjunto de dados de busca
		- int tamanho: tamanho do vetor de busca
		- int chave: valor a ser buscado
	Retorno:
		- int (posicao): localização do elemento buscado
	Contagem de operações:
		- (A) atribuição e aritméticas
		- (C) comparação
		- (V) acesso ao vetor
		- (F) acesso ou retorno de função
	Nós consideramos que todas as operações levam aproximadamente o tempo de execução
	Quando nós temos fluxos exclusivos, considera-se o pior caso!!!
	De termos gerais, a busca Sequencial é totalmente dependente do tamanho "n"
		- quanto mais n aumenta, maior é a quantidade de operações realizadas
	- Qual é o melhor caso? o número buscado é o primeiro
	- Qual é o pior caso? o número buscado não existe
	- Será que se eu usar o while / do while no lugar do for, a função de eficiência será a mesma? 
*/
int buscaSequencial(int* vetor, int tamanho, int chave){
	int i;
	for (i = 0; i < tamanho; i++)	//1 vez (A + C); outras vezes (2A + C).(n - 1)
		if (vetor[i] == chave)		//n(V + C) 
			return i;				//F
	return -1;						//F (não é executada) -> descartar
	//i++ <==> i = i + 1 (soma e atribuição) = 2A

	//f(n) = A + C + (2A + C).(n - 1) + n(V + C) + F
	//f(n) = A + C + 2An - 2A + Cn - C + Vn + Cn + F
	//f(n) = 

	//n = 1: vamos ter 5 operações
}

/*
	Descrição: busca binária realiza a divisão do vetor em partes (metades) baseando-se no cálculo do elemento central
		- requisito: o vetor precisa estar ordenado
		- especifica um espaço de busca, ou seja, regiões reduzidas como entrada da função
	Parâmetros:
		- int* vetor: vetor de entrada
		- int posicaoInicial: posição do primeiro elemento do vetor
		- int posicaoFinal: posicação do último elemento do vetor
		- int chave: elemento a ser buscado
	Retorno:
		- int (posicao): posição do elemento buscado
	Se o vetor estiver ordenado, com certeza a buscaBinaria é mais eficiente que a buscaSequencial (tempo) - no pior caso
	Se o vetor não ordenado é necessário fazer a ordenação
*/
int buscaBinaria(int* vetor, int posicaoInicial, int posicaoFinal, int chave){
	while(posicaoInicial <= posicaoFinal){ //log n
		int centro = (int)((posicaoInicial+posicaoFinal)/2);
		printf("valor inicial %i; valor final %i; valor central %i\n", 
			vetor[posicaoInicial], vetor[posicaoFinal], vetor[centro]);
		
		if (chave == vetor[centro]) return centro; //valor encontrado 
		
		if (chave < vetor[centro]) //se o número existir estará na primeira metade
			posicaoFinal = centro - 1;
		if (chave > vetor[centro]) //se o número existir estará na segunda metade
			posicaoInicial = centro + 1;
	}
	return -1;//valor não encontrado
}

int main(int argc, char* argv[]){
	//lendo parâmetros iniciais
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
	
	//informando a saída ao usuário
	if (posicao >= 0 )
		printf("Valor encontrado na posicao %i\n", posicao);
	else
		printf("Valor nao encontrado\n");
	
	//desalocando o vetor dinâmico
	free(vetor);
	
	return 0;
}
