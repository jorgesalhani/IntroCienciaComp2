/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Exercicio 3: Busca Indexada com Lista Encadeada
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void read_command(int* end_command) {
    int command = *end_command;
    scanf("%d ", &command);
    *end_command = command;
}

void read_file() {

}

void create_list() {

}

void read_file_and_create_list(void) {
    read_file();

    create_list();
}

void create_update_index_vector() {

}

void search() {
    
}

void process_command(int* command) {
    if (*command == 1) read_file_and_create_list();

    if (*command == 2) create_update_index_vector();

    if (*command == 3) search();

}

int main(void) {

    int command = 0;
    read_command(&command);

    process_command(&command);


    return 0;
}