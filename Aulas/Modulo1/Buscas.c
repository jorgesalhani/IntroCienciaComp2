#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FAIL -1

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
Busca binaria
Assume que o vetor esteja ordenado
@param v (int*) vetor a realizar a busca
@param ini (int) posicao inicial do vetor
@param fim (int) posicao final do vetor a ser buscada
@param chave (int) valor aencontrar
@return (int) posicao da chave no vetor ou FAIL caso busca sem sucesso
*/
int busca_binaria(int* v, int ini, int fim, int chave){
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

    int* v = NULL;
    v = aloca_e_preenche_vetor(n, max, ord, verb);

    if (v == NULL) {
        printf("Nao foi possivel alocar memoria\n");
        return 3;
    }

    int chave;
    printf("Chave: "); scanf("%d", &chave);

    clock_t t1, t2;
    t1 = clock();
    int ps = busca_sequencial(v, n, chave);
    t2 = clock();
    double time_s = (t2-t1)/(double)CLOCKS_PER_SEC;

    t1 = clock();
    int pb = busca_binaria(v, 0, n-1, chave);
    t2 = clock();
    double time_b = (t2-t1)/(double)CLOCKS_PER_SEC;

    if (ps >= 0) printf("Sequencial: chave encontrada em %d\n", ps);
    else if (ps == FAIL) printf("Sequencia: busca sem sucesso\n");

    if (pb >= 0) printf("Binaria: chave encontrada em %d\n", pb);
    else if (pb == FAIL) printf("Binaria: busca sem sucesso\n");

    printf("Tempo execucao sequencial: %lf seg.\n", time_s);
    printf("Tempo execucao binaria: %lf seg.\n", time_b);

    free(v);
    return 0;
}