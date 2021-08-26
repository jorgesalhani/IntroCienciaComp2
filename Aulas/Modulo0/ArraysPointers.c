# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main (void) {

    unsigned short ano; // 2 bytes na memoria stack - cada byte tem um endereco
                        // Os enderecos sao transparentes ao programador que utiliza a stack

    unsigned short* end_varus;

    char titulo[120]; // 120 bytes, todos interpretados como char, ou seja, de 1 em 1 byte


    printf("Ano: ");
    scanf("%hu", &ano);
    getchar(); // Consume o '\n' antes do fgets

    printf("Titulo: ");
    fgets(titulo, 120, stdin); // 120 bytes - 1 : 119 caracteres validos e em 120 temos o '\0'
    
    titulo[strlen(titulo) - 1] = '\0';

    printf("Informacao Digitada:\n");
    end_varus = &ano;
    printf("Ano: %hu (esta no endereco iniciando em %p)\n", ano, end_varus);
    printf("Titulo: %s (esta no endereco iniciando em %p)\n", titulo, &titulo);

    return 0;
}