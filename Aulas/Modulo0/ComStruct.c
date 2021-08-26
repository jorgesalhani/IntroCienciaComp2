# include <stdio.h>
# include <stdlib.h>
# include <string.h>


// Nao é uma variável
// Como se (struct livro) fosse um novo tipo
typedef struct livro {
    char titulo[120];
    unsigned short ano;
    char autor[60];
    float preco;
    unsigned int n_pag;
    unsigned char edicao;
} LIVRO;


void entrada_livro(struct livro* eliv) {
    
    // eliv é tipo struct livro*:  endereco de um struct livro
    // (*eliv) : derreferencia  :  tipo struct livro, com acesos aos campos da struct
    // (*eliv).titulo : eliv -> titulo são equivalentes
    
    printf("Titulo: ");
    fgets((*eliv).titulo, 120, stdin); 
    (*eliv).titulo[ strlen((*eliv).titulo) - 1 ] = '\0';

    printf("Ano: ");
    scanf("%hu", &(eliv -> ano));
    getchar();

    printf("Autor: ");
    fgets((eliv -> autor), 120, stdin);
    (eliv -> autor)[ strlen((eliv -> autor)) - 1 ] = '\0';

    printf("Preco: ");
    scanf("%f", &(eliv -> preco));
}

void exibe_livro(struct livro eliv) { // Nessa, eliv é uma copia da struct armazenada na memoria stack
    
    printf("\nLIVRO\n");
    printf("Titulo: %s\n", (eliv.titulo));
    printf("Ano: %hu\n", (eliv.ano));
    printf("Autor: %s\n", (eliv.autor));
    printf("Preco: %.2f\n", (eliv.preco));
}

void exibe_livro_end(const struct livro* eliv) { // Nessa, o endereco passado ocupa 8 bytes (MELHOR!!)
    
    printf("\nLIVRO\n");
    printf("Titulo: %s\n", (eliv->titulo));
    printf("Ano: %hu\n", (eliv->ano));
    printf("Autor: %s\n", (eliv->autor));
    printf("Preco: %.2f\n", (eliv->preco));
}



int main (void) {

    struct livro l1;
    // Cria uma variável que agrupa 6 blocos de tipos distintos 
    // l1 é o id da variável
    // seu conteúdo está dividido em partes:
    //  l1.titulo é char [120]
    //  l1.ano é unsigned shor

    entrada_livro(&l1);

    exibe_livro_end(&l1);

    return 0;
}