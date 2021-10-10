/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Avaliacao 01: Contagem de operacoes e algoritmo de ordenacao
*/


#include <stdio.h>
#include <stdlib.h>

void imprimeVetor(int* vetor, int tamanho){
	int i;
	printf("Vetor: ");
	for (i=0; i<tamanho; i++) printf("%i ", vetor[i]);
	printf("\n");
}

int** alloc_matrix(int m) {
	int **mat = malloc(sizeof(int*)*m);
	srand(m);
	
	int in = 0;
	// aloca matriz ordenada
	for (int i = 0; i < m; i++) {
		mat[i] = malloc(sizeof(int)*m);
	    	for (int j = 0; j < m; j++) {
			if (i == j) in+= (rand()%3)+1;
			else in += rand()%3;
			mat[i][j] = in;
		}
	}
	// desordena matriz triangular superior
	for (int i = 0; i < m-2; i++) {
	    	for (int j = i+1; j < m-1; j++) {
			int swaps = (int)((m-j)/2.0)+1;
			for (int t = 1; t <= swaps; t++) {
				int a = (rand()%(m-j))+j;
				int b = (rand()%(m-j))+j;
				int tmp = mat[i][a];
				mat[i][a] = mat[i][b];
				mat[i][b] = tmp;
			}
		}

	}
	return mat;
}

void insertion_sort(int* vetor, int content_length)
{
	/**
	 * CONTAGEM DE OPERACOES
	 * a: operacoes aritmeticas
	 * c: comparacoes
	*/
	int previous_cursor = 0;
	int cursor_content = 0;
    for (int i = 1; i < content_length; i++) {						// Loop percorrido (m^2)-1 vezes	
        cursor_content = vetor[i];
        previous_cursor = i - 1;									// a

																	// No pior caso, o conteudo na posicao
																	// previous_cursor sera sempre maior, e portanto,
																	// deve ser adicionada ao fim do vetor.
																	// Assim, o proximo valor sera inserido na penultima posicao do vetor
																	// o proximo, na antepenultima, e assim sucessivamente
																	//
																	// Desse modo, a cada insercao ao fim do vetor, este contera
																	// o maior dos elementos, fazendo com que, em media, 
																	// (tal como consideramos para a forca bruta), o vetor sera 
																	// percorrido um total de ((m^2)-1)/2 vezes

        while (vetor[previous_cursor] > cursor_content) {			// c (esta comparacao e importante)
            vetor[previous_cursor + 1] = vetor[previous_cursor]; 	// a
            previous_cursor = previous_cursor - 1;					// a
        }															// w(m) = (2a + c)(((m^2)-1)/2) <-- while
        vetor[previous_cursor + 1] = cursor_content;				// a
    }
}																	// f(m) = (2a + w(m))((m^2)-1)

	/**
	 * Assim, sendo w(m) = ((2a + c)/2).((m^2)-1) e n = m^2
	 * f(n) = (2a + (a + c/2)(n-1)).(n-1)
	 * f(n) = (3a + c/2)(n-1)^2
	*/

void free_matrix(int** matrix, int content_length) {
	for (int i = 0; i < content_length; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

int main (int argc, char* argv[]){
	int m;
	scanf("%d", &m);
	
	int vetor[m*m];
	int** matriz = alloc_matrix(m);
	
	int i, j, k = 0;
	for (i=0; i<m; i++)
		for (j=0; j<m; j++)
			vetor[k++] = matriz[i][j];			

	// ORDENACAO POR FORCA BRUTA
	//
	// for(i = 0; i < m*m-1; i++){
	// 	for(j = 0; j < m*m-1-i; j++){
	// 		if (vetor[j] > vetor[j+1]){
	// 			int aux = vetor[j];
	// 			vetor[j] = vetor[j+1];
	// 			vetor[j+1] = aux;		
	// 		}
	// 	}
	// }

	// k = 0;
	// for (i=0; i<m; i++){
	// 	for (j=0; j<m; j++){
	// 		matriz[i][j] = vetor[k++];
	// 		printf("%i ", matriz[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");

	insertion_sort(vetor, m*m);

	k = 0;
	for (i=0; i<m*m; i++){
		printf("%d ", vetor[i]);
		if ((i+1)%m == 0) printf("\n");
	}

	free_matrix(matriz, m);


	return 0;
}