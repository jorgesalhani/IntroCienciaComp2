#include <hashing.h>

int *create_hash_table(int m) {
    int *t = malloc(sizeof(int)*m);
    for (int i = 0; i < m; i++) {
        t[i] = FREE;
    }
    return t;
}

void destroy_hash_table(int **t) {
    free(*t);
    *t = NULL;
}

int insert(int *t, int key, int m) {
    // Apenas chaves positivas
    if (key < 0) return -1; 

    double A = (sqrt(5)-1)/2.0;

    // Posicao e numero de colisoes
    int pos, c = 0;

    // Tratar colisao com enderecamento aberto por sondagem linear
    do {
        // Calcular funcao hash
        // ----- DIVISION ------
        // pos = hash_division(key, m, c);

        // ----- MULTIPLI ------
        pos = hash_multi(key, m, c, A);

        // Verificar se houve colisao
        if (t[pos] != FREE && t[pos] != DEL) {
            c++;
            printf("-colisao %d (%d)\n", c, t[pos]);
        }
    } while (t[pos] != FREE && t[pos] != DEL);

    // Inserir chave na posicao
    t[pos] = key;
}

int search(int *t, int key, int m) {
    // Apenas chaves positivas
    if (key < 0) return -1;

    double A = (sqrt(5)-1)/2.0;

    // Numero de colisoes
    int c = 0;
    int pos;

    do {
        // Calcular funcao hash
        // ----- DIVISION ------
        // pos = hash_division(key, m, c);

        // ----- MULTIPLI ------
        pos = hash_multi(key, m, c, A);

        // Caso posicao livre, SEM SUCESSO
        if (t[pos] == FREE) break;

        // Caso colisao, INCREMENTA CONTADOR
        if (t[pos] != key) c++;

        // Caso percorreu toda tabela, SEM SUCESSO
        if (c >= m) break;
    } while (t[pos] != key);

    // Verificar se posicao possui a chave, SUCESSO
    if (t[pos] == key) {
        return pos;
    } else {
        return FREE;
    }
}

int remove_hash(int *t, int key, int m) {
    int pos = search(t, key, m);
    if (pos < 0) return pos;
    t[pos] = DEL;
    return 1;
}

void print_table(int *t, int m) {
    for (int i = 0; i < m; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");
}

int hash_division(int key, int m, int c) {
    return (int) ((key+c)%m);
}

int hash_multi(int key, int m, int c, double A) {
    double val = (key+c)*A;
    val = val - ((int)val);
    return (int)(val*m);
}