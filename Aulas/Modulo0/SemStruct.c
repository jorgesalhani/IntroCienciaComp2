# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void entrada_livro(char* etitulo, char* eautor, unsigned short* eano) {
    printf("Titulo: ");
    fgets(etitulo, 120, stdin); 
    etitulo[ strlen(etitulo) - 1 ] = '\0';

    printf("Ano: ");
    scanf("%hu", eano);
    getchar();

    printf("Autor: ");
    fgets(eautor, 120, stdin);
    eautor[ strlen(eautor) - 1 ] = '\0';

}

int main (void) {

    unsigned short ano; // 2 bytes na memoria stack - cada byte tem um endereco
                        // Os enderecos sao transparentes ao programador que utiliza a stack

    unsigned short* end_varus;
    char titulo[120]; // 120 bytes, todos interpretados como char, ou seja, de 1 em 1 byte
    char autor[60]; 

    entrada_livro(titulo, autor, &ano);

    printf("Informacao Digitada:\n");
    end_varus = &ano;
    printf("Ano: %hu (esta no endereco iniciando em %p)\n", ano, end_varus);
    printf("Titulo: %s (esta no endereco iniciando em %p)\n", titulo, &titulo);
    printf("Autor: %s (esta no endereco iniciando em %p)\n", autor, &autor);

    return 0;
}