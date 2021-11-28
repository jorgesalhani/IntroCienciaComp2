/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Exercicio 3: Busca Indexada com Lista Encadeada
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define WORD_LENGTH 100

void read_command(int* end_command) {
    int command = *end_command;
    // scanf("%d ", &command);
    command = 1;
    *end_command = command;
}

void store_word_list(FILE* file_, int* N, char*** ptr_word_list) {
    char** word_list = *ptr_word_list;
    int word_count = 0;
    char word[WORD_LENGTH];
    while (fgets(word, sizeof(word), file_) != NULL) {
        word_list[word_count] = word;
        word_count++;
    }
    *N = word_count; // TODO: FIX
}

void read_file(int* N, char*** ptr_word_list) {
    // char file_name[50];
    // scanf("%s", file_name);
    char file_name[50] = "words1.txt";

    FILE* file_ = fopen(file_name, "r");
    if (file_ == NULL) {
        perror("Error opening file!\n");
        exit(-1);
    }

    store_word_list(file_, N, ptr_word_list);

    fclose(file_);
}

void create_list() {

}

void free_word_list(char*** ptr_to_word_list, int* N) {
    char** word_list = *ptr_to_word_list;
    for (int i = 0; i < *N; i++) {
        free(word_list[i]);
    }
    free(word_list);
}

void read_file_and_create_list(void) {
    int N = 0;
    char** word_list = NULL;
    word_list = (char**)malloc(sizeof(char*));

    read_file(&N, &word_list);

    create_list();

    free_word_list(&word_list, &N);
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