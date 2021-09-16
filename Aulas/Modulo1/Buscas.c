#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FAIL -404

/*
aloca_e_preenche_vetor
Funcao que aloca na memoria heap um vetor de inteiros
positivos obtidos aleatoriamente e retorna seu endereco

@param tot (int): numero com o tamanho do vetor a ser alocado
@param max (int): valor maximo aleatorio no vetor
@param ordenado (int): 1 para vetor ordenado, 0 nao ordenado
@param verb (int): 1 para verboso, 0 para nao verboso
#return (int*) endereco da primeira posicao na heap contendo o vetor alocado
*/
int* aloca_e_preenche_vetor(int tot, int max, int ordenado, int verb) {
    int* aux = NULL;
    aux = (int*) malloc(tot*sizeof(int));

    if (ordenado) aux[0] = (rand()%2);
    else aux[0] = (rand()%(max+1));
    for (int i = 1; i < tot; i++) {
        if (!ordenado) {
            aux[i] = rand()%(max+1);
        } else {
            aux[i] = aux[i-1] + rand()%4;
        }
        if (verb) printf("%d ", aux[i]);
    }
    if (verb) printf("\n");
    return aux;
}

/*
Funcao que realiza busca sequencial em vetor inteiro
@param v (int*): vetor de inteiros
@param n (int): tamanho do vetor
@param chave (int): valor a ser buscado
@return (int) posiciao em que foi encontrado ou FAIL caso busca sem sucesso
*/
int busca_sequencial(int* vet, int n, int chave) {

    // operacoes:
    // a - aritmeticas
    // b - acesso a pointeiro
    // c - comparacoes
    // d - retorno de funcao
    // e - atribuicao
    // 
    // em alguns casos, consideramos: a == b == c == d == e

                                            // Contagem de pior caso
    for (int i = 0; i < n; i++) {           // 1.  e + c                <- (1) vez
                                            // 2.+ (a + e) + c          <- (n) vezes
        if (vet[i] == chave) return i;      // (b + c)                  <- (n) vezes
    }                                       // -------------
                                            // (e + c) + n(c + a + e + b + c)

    return FAIL;                            // d
                                            // (2c + a + e + b)n + (e + d + c) 
                                            // a == b == d == e = x
                                            // f(n) = (2c + 3x)n + (c + 3x)  <- funcao de eficiencia
                                            // 
}

/*
Busca binaria iterativa
Assume que o vetor esteja ordenado
@param v (int*) vetor a realizar a busca
@param ini (int) posicao inicial do vetor
@param fim (int) posicao final do vetor a ser buscada
@param chave (int) valor aencontrar
@return (int) posicao da chave no vetor ou FAIL caso busca sem sucesso
*/
int busca_binaria_iterativa(int* v, int ini, int fim, int chave){
    int c;
    // operacoes:
    // c - comparacao
    // x - restante
    //                               ex:    16
    // 1. busca nas n posicoes              16
    // 2. busca em n/2 posicoes             8
    // 2. busca em n/4 posicoes             4
    // 2. busca em n/8 posicoes             2
    // 2. busca em n/16 posicoes            1

                                        //              Pior caso: chave na ultima posicao
    while (ini <= fim) {                // c
        c = (int)((fim + ini)/2.0);     // 3x
        if (v[c] == chave) return c;    // c + x        < False
        else if (v[c] < chave) {        // c + x        < False
            ini = c + 1;                // 2x
        } else if (v[c] > chave) {      // c + x
            fim = c - 1;                // 2x
        }                               // -----
                                        // 4c + 8x      < (n) vezes
                                        // f(n) = log2(n) * (4c + 8x)
    }
    return FAIL;
}

/*
Busca sequencial recursiva
@param v (int*):    vetor de inteiros para realizar a busca
@param chave (int): chave a ser buscada
@param N (int):     tamanho do vetor
@param i (int):     posicao a ser verificada
@return (int):      posicao em que a chave foi encontrada, ou FAIL caso contrario
*/
int busca_sequencial_recursiva(int* v, int chave, int N, int i) {
    
    // Contagem:
    // Comparacoes - c
    // chamada de funcao - b
    // aritmeticas - a

    if (i >= N) return FAIL;                                // c
    if (v[i] == chave) return i;                            // c

    return busca_sequencial_recursiva(v, chave, N, i+1);    // a + b
                                                            // -----
                                                            // (2c + a + b)*N

                                                            // f(0) = c
                                                            // f(N) = (2c + a + b) + f(N-1) <- funcao recorrencia

                                                            // f(K) = (2c + a + b)*K + f(N-K)
                                                            // Quando N - K = 0, acaba => N = K
                                                            // f(N) = (2c + a + b)*N + f(0)     <- forma fechada
                                                            // f(N) = (2c + a + b)*N + c
}

/*
Busca binaria recursiva
Assume que o vetor esteja ordenado
@param v (int*) vetor a realizar a busca
@param ini (int) posicao inicial do vetor
@param fim (int) posicao final do vetor a ser buscada
@param chave (int) valor aencontrar
@return (int) posicao da chave no vetor ou FAIL caso busca sem sucesso
*/
int busca_binaria(int* v, int chave, int ini, int fim) {
    
    // Contagem:
    // Comparacoes - c
    // chamada de funcao - b
    // aritmeticas - a


    // Caso base 1: parada
    if (ini > fim) return FAIL; // Criterio de parada   // c

    int c = (int)((ini + fim) / 2.0);                   // 2a

    // Caso base 2: chave encontrada
    if (v[c] == chave) return c;                        // c

    if (chave < v[c]) {                                 // c
        return busca_binaria(v, chave, ini, c-1);       // a + b
    }

    if (chave > v[c]) {                                 // c
        return busca_binaria(v, chave, c+1, fim);       // a + b
                                                        // -----
                                                        // c + 2a + c + c + c + a + b
                                                        // 4c + 3a + b
                                                        // f(0) = c
                                                        // f(N) = (4c + 3a + b) + f((N-1)/2)   <- funcaorecorrencia (pior caso)
                                                        // f(N) = (4c + 3a + b) + f(N/2) ~
                                                        // f(N) = (4c + 3a + b)*2 + f(N/(2*2)) ~

                                                        // f(K) = (4c + 3a + b)K + f(N/2^K)
                                                        // Quando N/2^K = 1, acaba  => N = 2^K
                                                        //                          => K = log2(N)
                                                        // f(N) = (4c + 3a + b) log2(N) + f(1)
                                                        // Com f(1) = 3a + b + 5c   <- 1 exec + f(0)
    }
}

/*
Insertion sort
    Metodo de insercao na posicao correta
    Metodo de ordenacao inplace (altera o vetor)
@param v (int*):    vetor a ser ordenado
@param n (int):     tamanho do vetor
*/
void insertion_sort(int* v, int N) {

    // vetor
    // [ LO | LD ]
    // [ 8 | 7 0 1 ]
    // [ 7 8 | 0 1 ]
    // [ 0 7 8 | 1 ]
    // [ 0 1 7 8 | ]

    int i = 1;

    while (i < N) {
        int el = v[i]; // fixa elemento a ser comparado com anteriores
        int j = i - 1; // indice para percorrer elementos anteriores

        while (j >= 0 && el < v[j]) {
            v[j + 1] = v[j];    // Movimenta valor para frente
            j--;                // indice retorna uma posicao
        }
        v[i-1] = el; // Encontrei a posicao correta

        i++;
    }
}

int main (int argc, char* argv[]) {

    if (argc < 5) {
        printf("Uso: %s <N> <MAX> <VER> <ORD>\n\tN: tamanho do vetor a ser gerado\n", argv[0]);
        printf("\tMAX: maior numero no vetor\n");
        printf("\tORD: 1 vetor ordenado, 0 nao ordenado\n");
        printf("\tVER: 1 modo verboso, 0 modo nao verboso\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int max = atoi(argv[2]);
    int ord = atoi(argv[3]);
    int verb = atoi(argv[4]);

    if ((n < 1 || n > 50000000) || max < 0) {
        printf("N deve ser entre 1 e 50.000.000\nMAX deve ser maior do que 0\n");
        return 2;
    }

    printf("Vetor de tamanho: %d, maximo = %d\n", n, max);

    srand(0);
    int* v1 = NULL;
    v1 = aloca_e_preenche_vetor(n, max, ord, verb);
    
    srand(0);
    int* v2 = NULL;
    v2 = aloca_e_preenche_vetor(n, max, 0, verb);

    clock_t t1, t2;

    t1 = clock();
    insertion_sort(v2, n);
    t2 = clock();
    double time_is = (t2-t1)/(double)CLOCKS_PER_SEC;

    if (v1 == NULL) {
        printf("Nao foi possivel alocar memoria\n");
        return 3;
    }

    int chave;
    printf("Chave: "); scanf("%d", &chave);

    t1 = clock();
    int ps = busca_sequencial(v1, n, chave);
    t2 = clock();
    double time_s = (t2-t1)/(double)CLOCKS_PER_SEC;

    t1 = clock();
    int pb = busca_binaria_iterativa(v1, 0, n-1, chave);
    t2 = clock();
    double time_b = (t2-t1)/(double)CLOCKS_PER_SEC;

    t1 = clock();
    int pbr = busca_sequencial_recursiva(v1, 0, n-1, chave);
    t2 = clock();
    double time_sr = (t2-t1)/(double)CLOCKS_PER_SEC;

    if (ps >= 0) printf("Sequencial: chave encontrada em %d\n", ps);
    else if (ps == FAIL) printf("Sequencial: busca sem sucesso\n");

    if (pb >= 0) printf("Binaria: chave encontrada em %d\n", pb);
    else if (pb == FAIL) printf("Binaria: busca sem sucesso\n");

    if (pb >= 0) printf("Sequencial recursiva: chave encontrada em %d\n", pbr);
    else if (pb == FAIL) printf("Sequencial recursiva: busca sem sucesso\n");

    printf("Tempo execucao sequencial: %lf seg.\n", time_s);
    printf("Tempo execucao binaria: %lf seg.\n", time_b);
    printf("Tempo execucao sequencial recursiva: %lf seg.\n", time_sr);
    printf("Tempo execucao insertion sort: %lf seg.\n", time_is);

    free(v1);
    return 0;
}
