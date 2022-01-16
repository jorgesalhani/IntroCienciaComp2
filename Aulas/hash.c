#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	Métodos de busca estudados até agora (Comparação de chaves)
	- Ordenação (o): O(n^2) até O(n)
	- Busca (b): O(n) até O(log(log(n)))
	Então, o processo completo é: O(o) + k*O(b)

	Em cenários mais práticos, temos outras operações:
	- Inserção
	- Remoção

	Hashing:
	- utiliza uma estrutura chamada de Tabela Hash ou Tabela de Espalhamento ou Tabela de Dispersão;
	- a ideia é mapear a chave em uma posição na tabela, assim O(1)
	- a função Hash 'h(chave)' calcula o índice (endereço) onde a chave deve (ou pelo menos deveria) ser armazenada

	Função (não há garantias que seja uma função injetora):
	- ou seja, a função pode direcionar diferentes chaves para o mesmo índice
	- assim, o maior problema em Hashing são as colisões
	- exemplo: h(x) = x % 3
		- x =  9 -> h(x) = 0
		- x = 10 -> h(x) = 1
		- x = 11 -> h(x) = 2
		- x = 12 -> h(x) = 0
		- Tabela Hash [0 1 2]
	- a vantagem principal é que a mesma função é utilizada para buscar e inserir elementos

	Formalizando:
	- h: X -> [0, .., m-1], em que m é a quantidade de posições possíveis
	- desejavelmente, queremos que a distribuição das chaves seja uniforme, ou seja, P(h(x) = i) = i/m
	- desejavelmente, a função deve gerar baixa taxa de colisões
	- desejavelmente, a função deve ser facilmente computada
	- exemplo: Tabela de tamanho 10, chaves {3, 8, 17} e h(x) = x % 10
			    0  1  2  3  4  5  6  7  8  9  posições
			  [-1 -1 -1 -1 -1 -1 -1 -1 -1 -1] vetor
			  [-1 -1 -1  3 -1 -1 -1 -1 -1 -1] inserindo a chave 3
			  [-1 -1 -1  3 -1 -1 -1 -1  8 -1] inserindo a chave 8
			  [-1 -1 -1  3 -1 -1 -1 17  8 -1] inserindo a chave 17
			  [-1 -1 -1  3 -1 -1 -1 17  8 -1] buscando a chave 3 -> h(x) = x % 10 = 3 (valor 3) retorna a chave 3
	- algumas observações:
		- o tamanho da tabela deve ser maior que a quantidade de chaves a serem inseridas
		- só funciona para valores numéricos inteiros (mapeamento de texto para inteiro, por exemplo)
		- quantidade de espaços vazios
		- frequência de atualizações (remoção, novas inserções, colisões, chaves que não existem)

	Função Hash (Mapeamento de Compressão ou Divisão): 
	- h(x) = x % m (como definir m?)
	- se m = b^e (base b elevado ao expoente e):
		- todas as chaves com mesmo valor do % serão mapeados para o mesmo índice
	- se m for um número primo:
		- ajuda a distribuir uniformemente as chaves
		- o produto de um primo com outro número tem maior chance de ser único
		- Método de Sedgewick: considerando a quantidade de chaves, buscar o número primo mais próximo

		15 chaves -> 16 -> 13

	Função Hash (Chaves não inteiras):
	- Integer cast: para números de 32 bits ou menos, reinterpretar os bits como inteiro
		- 70.20 -> 702
		- 36.33 -> 363
	- Soma de componentes: para números de 32 bits ou mais, soma ponderada dos componentes
		- 1100100001100011110001110011111111010001010000111011100011110000 (64 bits)
		- a: 11001000011000111100011100111111 (32 bits mais significativos)
		- b: 11010001010000111011100011110000 (32 bits menos significativos)
		- chave = 0.5 a + 0.5 b (forma ponderada)
		- permutações são um problema 
			- chave 'abc' possuirá o mesmo mapeamento da chave 'cba'
			- chave 'ad' posuirá o mesmo mapeamento da chave 'cb'
	- Acumulação polinomial para caracteres: x pode ser um número primo e as letras na tabela ASCII
		- 'abc' -> a + x(b + x(c))
		- 'cba' -> c + x(b + x(a))

	Resolvendo colisões com sondagem:
	- retomando nosso exemplo: Tabela de tamanho 10, chaves {3, 8, 17, 13, 23} e h(x) = x % 10
		    0  1  2  3  4  5  6  7  8  9  posições
		  [-1 -1 -1 -1 -1 -1 -1 -1 -1 -1] vetor
		  [-1 -1 -1  3 -1 -1 -1 -1 -1 -1] inserindo a chave 3
		  [-1 -1 -1  3 -1 -1 -1 -1  8 -1] inserindo a chave 8
		  [-1 -1 -1  3 -1 -1 -1 17  8 -1] inserindo a chave 17
		  [-1 -1 -1  3 -1 -1 -1 17  8 -1] inserindo a chave 13 (posição 3 já ocupada!!!!)
	- modificando nossa função h(x) = (x+i) % 10  -> i é a quantidade de colisões
	  		0  1  2  3  4  5  6  7  8  9  posições
		  [-1 -1 -1 -1 -1 -1 -1 -1 -1 -1] vetor
		  [-1 -1 -1  3 -1 -1 -1 -1 -1 -1] inserindo a chave 3
		  [-1 -1 -1  3 -1 -1 -1 -1  8 -1] inserindo a chave 8
		  [-1 -1 -1  3 -1 -1 -1 17  8 -1] inserindo a chave 17
		  [-1 -1 -1  3 -1 -1 -1 17  8 -1] inserindo a chave 13 (posição 3 já ocupada!!!!)
		  [-1 -1 -1  3 13 -1 -1 17  8 -1] inserindo a chave 13 (13+1)
		  [-1 -1 -1  3 13 -1 -1 17  8 -1] inserindo a chave 23 (posição 3 já ocupada!!!!)
		  [-1 -1 -1  3 13 -1 -1 17  8 -1] inserindo a chave 23 (23+1)(posição 4 já ocupada!!!!)
		  [-1 -1 -1  3 13 23 -1 17  8 -1] inserindo a chave 23 (23+2)
		  [-1 -1 -1  3 13 23 -1 17  8 -1] inserindo a chave 25 (posição 5 já ocupada!!!!)
		  [-1 -1 -1  3 13 23 25 17  8 -1] inserindo a chave 25 (25+1)
		  [-1 -1 -1  3 13 23 25 17  8 26] inserindo a chave 36 
*/

void imprimeVetor(int* tabela, int tamanho){
	if (tamanho <= 100){
		int i;
		for (i=0; i<tamanho; i++){
			printf("%i  ", tabela[i]);
		}
	}
	printf("\n");
}

int hash(int key, int colisao, int tamanho){
	return (key+colisao) % tamanho;
}

//chave 10 -> posicao 10 (colisão!)
//chave 10 -> posicao 11 (se estiver vazio, posicao 11 para a chave 10)

//possíveis melhorias:
//	- tratamento de chaves identicas na inserção
//	- controle da quantidade de itens a serem inseridos

void insereHash(int* tabela, int tamanho, int key){
	printf("Inserindo a chave %i\n", key);

	int colisao = 0;
	do {
		int posicao = hash(key, colisao, tamanho);
		if (tabela[posicao] == -1){
			tabela[posicao] = key;
			break;
		}
		else{
			printf("Colisao na posicao %i\n", posicao);
			colisao++;
		}
	}while(1);
	
	imprimeVetor(tabela, tamanho);
}

void buscaHash(int* tabela, int key, int tamanho){
	int colisao = 0;
	int posicao = hash(key, colisao, tamanho);
	
	while(tabela[posicao]!=-1){
		if (tabela[posicao] == key){
			printf("Elemento encontrado na posicao: %i\n", posicao);
			break;
		}
		posicao = hash(key, colisao++, tamanho);
	}
}


int main(int argc, char* argv[]){
	//n = 10
	//m = 13 (próximo valor da base 2 = 16, menor primo = 13)
	int tamanho = 13;
	int tabela[13];

	//inicializando a tabela Hash
	int i;
	for (i = 0; i < tamanho; i++)
   		tabela[i] = -1;

   	//inserindo elementos na tabela Hash
	for (i=0; i<10; i++){
		int key = rand() % 100;
		insereHash(tabela, tamanho, key);
	}

	//buscando um elemento na tabela Hash
	int key;
	printf("\n\nDigite uma chave a ser buscada:");
	scanf("%i", &key);
	buscaHash(tabela, key, tamanho);

	return 0;	
}