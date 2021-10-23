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

int main (int argc, char* argv[]){
	int m;
	// scanf("%d", &m);
	
	int vetor[m*m];
	int** matriz = alloc_matrix(m);

    /**
     * CONTAGEM DE OPERACOES
     * a: operacoes aritmeticas
     * c: comparacoes
    */
	
	int i, j, k = 0;                    
                                        // Sendo m o tamanho da matriz
                                        // Essa parte do codigo ocorrera
	for (i=0; i<m; i++)                 // -- m-1 vezes
		for (j=0; j<m; j++)             // --- m-1 vezes
			vetor[k++] = matriz[i][j];  // a

                                        // Teremos:
                                        // ((m-1)^2)a
                                        

                                        // Essa parte do codigo ocorrera
	for(i = 0; i < m*m-1; i++){         // -- (m^2)-1 vezes
                                        // O vetor contera todos os elementos da matriz
                                        // Considerando que m=3, i=0 -> i=8
		for(j = 0; j < m*m-1-i; j++){   //
                                        // | i=0               | i=1
                                        // | j=0 -> 9-1        | j=0 -> 9-2 ..

                                        // | i=2               | i=3
                                        // | j=0 -> 9-3        | j=0 -> 9-4 ..

                                        // | i=4               
                                        // | j=0 -> 9-5        ...

                                        // Isso significa que, a cada incremento em i, o segundo
                                        // loop percorrera menos elementos em j, ate que i=8
                                        // Assim, podemos assumir que o vetor percorrera
                                        // o segundo loop de 0 a ((m^2)-1)/2
                                        //
			if (vetor[j] > vetor[j+1]){ // c + a
				int aux = vetor[j];     //
				vetor[j] = vetor[j+1];  // a
				vetor[j+1] = aux;		// a
			}                           // 3a + c
		}
	}                                   // Teremos assim:
                                        // (3a + c).(((m^2)-1)^2)/2
    
    /**
     * Assim, considerando as duas equacoes obtidas:
     * f(m) = ((m-1)^2)a + (3a + c).(((m^2)-1)^2)/2
     * f(m) = (m^2 - 2m + 1)a + (3a + c).(((m^2)-1)^2)/2
     * 
     * Sendo n = m^2
     * f(n) = (n - 2sqrt(n) + 1)a + ((3a + c)/2)(n - 1)^2
    */

	k = 0;
	for (i=0; i<m; i++){
		for (j=0; j<m; j++){
			matriz[i][j] = vetor[k++];
			printf("%i ", matriz[i][j]);
		}
		printf("\n");
	}

	free(matriz);

	return 0;
}