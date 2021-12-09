#include <stdio.h>
#include <stdlib.h>

typedef struct reg {
    int key;
    float value;
    char *bla;
} Reg;

typedef struct node
{
    Reg elem;
    struct node *next;
} Node;

typedef struct bucket
{
    Node *begin;
    Node *end;
} Bucket;

void bucketsort(Reg *v, int N) {
    int i;

    // 1 - Encontrar a maior chave, considerando que sao positivas
    int max = v[0].key;
    for(i = 1; i < N; i++) {
        if (v[i].key > max) max = v[i].key;
    }

    // 2 - Criar vetor auxiliar contendo listas (buckets)
    //     Cada bucket possui um ponteiro para o inicio e outro
    //          para o fim da lista
    Bucket *B = (Bucket*)calloc((max+1), sizeof(Bucket));

    // 3 - Preencher buckets com as chaves do vetor de entrada
    for (i = 0; i < N; i++) {
        int key = v[i].key;

        Node *new_node = malloc(sizeof(Node));
        new_node->elem = v[i];
        new_node->next = NULL;

        if (B[key].begin == NULL) {
            B[key].begin = new_node;
        } else {
            (B[key].end)->next = new_node;
        }

        B[key].end = new_node;
    }

    // 4 - Percorre cada bucket, removendo os elementos do inicio
    //     da fila e inserindo na posicao correta
    int j;
    i = 0;
    for (j = 0; j < max+1; j++){
        Node *pos;
        pos = B[j].begin;
        while (pos != NULL) {
            v[i] = pos->elem;
            i++;

            Node *del = pos;
            pos = pos->next;
            B[j].begin = pos;
            free(del);
        }
    }
    free(B);
}

int main(int argc, char *argv[]) {
    Reg A[] = 
    {
        {2, 8.3, NULL},
        {1, 1.3, NULL},
        {5, 9.9, NULL},
        {0, 1.3, NULL},
        {2, 10.3, NULL}
    };

    int N = 5;
    
    bucketsort(A, N);

    int i;
    for (i = 0; i < N; i++) {
        printf("(%d %f) ", A[i].key, A[i].value);
    }
    printf("\n\n");
}

