#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	M�todos de busca estudados at� agora (Compara��o de chaves)
	- Ordena��o (o): O(n^2) at� O(n)
	- Busca (b): O(n) at� O(log(log(n)))
	Ent�o, o processo completo �: O(o) + k*O(b)

	Em cen�rios mais pr�ticos, temos outras opera��es:
	- Inser��o
	- Remo��o

	Hashing:
	- utiliza uma estrutura chamada de Tabela Hash ou Tabela de Espalhamento ou Tabela de Dispers�o;
	- a ideia � mapear a chave em uma posi��o na tabela, assim O(1)
	- a fun��o Hash 'h(chave)' calcula o �ndice (endere�o) onde a chave deve (ou pelo menos deveria) ser armazenada

	Fun��o (n�o h� garantias que seja uma fun��o injetora):
	- ou seja, a fun��o pode direcionar diferentes chaves para o mesmo �ndice
	- assim, o maior problema em Hashing s�o as colis�es
	- exemplo: h(x) = x % 3
		- x =  9 -> h(x) = 0
		- x = 10 -> h(x) = 1
		- x = 11 -> h(x) = 2
		- x = 12 -> h(x) = 0
		- Tabela Hash [0 1 2]
	- a vantagem principal � que a mesma fun��o � utilizada para buscar e inserir elementos

	Formalizando:
	- h: X -> [0, .., m-1], em que m � a quantidade de posi��es poss�veis
	- desejavelmente, queremos que a distribui��o das chaves seja uniforme, ou seja, P(h(x) = i) = i/m
	- desejavelmente, a fun��o deve gerar baixa taxa de colis�es
	- desejavelmente, a fun��o deve ser facilmente computada
	- exemplo: Tabela de tamanho 10, chaves {3, 8, 17} e h(x) = x % 10
			    0  1  2  3  4  5  6  7  8  9  posi��es
			  [-1 -1 -1 -1 -1 -1 -1 -1 -1 -1] vetor
			  [-1 -1 -1  3 -1 -1 -1 -1 -1 -1] inserindo a chave 3
			  [-1 -1 -1  3 -1 -1 -1 -1  8 -1] inserindo a chave 8
			  [-1 -1 -1  3 -1 -1 -1 17  8 -1] inserindo a chave 17
			  [-1 -1 -1  3 -1 -1 -1 17  8 -1] buscando a chave 3 -> h(x) = x % 10 = 3 (valor 3) retorna a chave 3
	- algumas observa��es:
		- o tamanho da tabela deve ser maior que a quantidade de chaves a serem inseridas
		- s� funciona para valores num�ricos inteiros (mapeamento de texto para inteiro, por exemplo)
		- quantidade de espa�os vazios
		- frequ�ncia de atualiza��es (remo��o, novas inser��es, colis�es, chaves que n�o existem)

	Fun��o Hash (Mapeamento de Compress�o ou Divis�o): 
	- h(x) = x % m (como definir m?)
	- se m = b^e (base b elevado ao expoente e):
		- todas as chaves com mesmo valor do % ser�o mapeados para o mesmo �ndice
	- se m for um n�mero primo:
		- ajuda a distribuir uniformemente as chaves
		- o produto de um primo com outro n�mero tem maior chance de ser �nico
		- M�todo de Sedgewick: considerando a quantidade de chaves, buscar o n�mero primo mais pr�ximo

		15 chaves -> 16 -> 13

	Fun��o Hash (Chaves n�o inteiras):
	- Integer cast: para n�meros de 32 bits ou menos, reinterpretar os bits como inteiro
		- 70.20 -> 702
		- 36.33 -> 363
	- Soma de componentes: para n�meros de 32 bits ou mais, soma ponderada dos componentes
		- 1100100001100011110001110011111111010001010000111011100011110000 (64 bits)
		- a: 11001000011000111100011100111111 (32 bits mais significativos)
		- b: 11010001010000111011100011110000 (32 bits menos significativos)
		- chave = 0.5 a + 0.5 b (forma ponderada)
		- permuta��es s�o um problema 
			- chave 'abc' possuir� o mesmo mapeamento da chave 'cba'
			- chave 'ad' posuir� o mesmo mapeamento da chave 'cb'
	- Acumula��o polinomial para caracteres: x pode ser um n�mero primo e as letras na tabela ASCII
		- 'abc' -> a + x(b + x(c))
		- 'cba' -> c + x(b + x(a))

	Resolvendo colis�es com sondagem:
	- retomando nosso exemplo: Tabela de tamanho 10, chaves {3, 8, 17, 13, 23} e h(x) = x % 10
		    0  1  2  3  4  5  6  7  8  9  posi��es
		  [-1 -1 -1 -1 -1 -1 -1 -1 -1 -1] vetor
		  [-1 -1 -1  3 -1 -1 -1 -1 -1 -1] inserindo a chave 3
		  [-1 -1 -1  3 -1 -1 -1 -1  8 -1] inserindo a chave 8
		  [-1 -1 -1  3 -1 -1 -1 17  8 -1] inserindo a chave 17
		  [-1 -1 -1  3 -1 -1 -1 17  8 -1] inserindo a chave 13 (posi��o 3 j� ocupada!!!!)
	- modificando nossa fun��o h(x) = (x+i) % 10  -> i � a quantidade de colis�es
	  		0  1  2  3  4  5  6  7  8  9  posi��es
		  [-1 -1 -1 -1 -1 -1 -1 -1 -1 -1] vetor
		  [-1 -1 -1  3 -1 -1 -1 -1 -1 -1] inserindo a chave 3
		  [-1 -1 -1  3 -1 -1 -1 -1  8 -1] inserindo a chave 8
		  [-1 -1 -1  3 -1 -1 -1 17  8 -1] inserindo a chave 17
		  [-1 -1 -1  3 -1 -1 -1 17  8 -1] inserindo a chave 13 (posi��o 3 j� ocupada!!!!)
		  [-1 -1 -1  3 13 -1 -1 17  8 -1] inserindo a chave 13 (13+1)
		  [-1 -1 -1  3 13 -1 -1 17  8 -1] inserindo a chave 23 (posi��o 3 j� ocupada!!!!)
		  [-1 -1 -1  3 13 -1 -1 17  8 -1] inserindo a chave 23 (23+1)(posi��o 4 j� ocupada!!!!)
		  [-1 -1 -1  3 13 23 -1 17  8 -1] inserindo a chave 23 (23+2)
		  [-1 -1 -1  3 13 23 -1 17  8 -1] inserindo a chave 25 (posi��o 5 j� ocupada!!!!)
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

//chave 10 -> posicao 10 (colis�o!)
//chave 10 -> posicao 11 (se estiver vazio, posicao 11 para a chave 10)

//poss�veis melhorias:
//	- tratamento de chaves identicas na inser��o
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
	//m = 13 (pr�ximo valor da base 2 = 16, menor primo = 13)
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