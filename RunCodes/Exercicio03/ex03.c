/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Exercicio 3: Busca Indexada com Lista Encadeada
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define WORD_MAX_LENGTH 100

void free_word_list(char*** ptr_to_word_list, int* N) {
    char** word_list = *ptr_to_word_list;
    for (int i = 0; i < *N; i++) {
        free(word_list[i]);
    }
    free(word_list);
}

void copy_word(int* cursor, char*** ptr_word_list, char*** ptr_word_list_copy) {
    char** word_list = *ptr_word_list;
    char** word_list_copy = *ptr_word_list_copy;

    int word_length = strlen(word_list[*cursor]);
    word_list_copy[*cursor] = (char*)malloc(sizeof(char*)*(word_length+1));
    for (int i = 0; i < word_length; i++) {
        word_list_copy[*cursor][i] = word_list[*cursor][i];
    }
    word_list_copy[*cursor][word_length] = '\0';
}

void order_word_list(char*** ptr_word_list, int* N) {
    char** word_list = *ptr_word_list;
    int max, min, key;

    char** word_list_copy = NULL;
    word_list_copy = (char**)malloc(sizeof(char*)*(*N));
    printf("COPY:\n\n");

    max = min = (int)word_list[0][0];
    for (int i = 0; i < *N; i++) {
        key = (int)word_list[i][0];
        if (key > max) max = key;
        if (key < min) min = key;
        
        copy_word(&i, ptr_word_list, &word_list_copy);
    }
    printf("\n");


    free_word_list(&word_list_copy, N);
}

void store_word_list(FILE* file_, int* N, char*** ptr_word_list) {
    char** word_list = NULL;
    int word_count = 0;
    char letter_ = fgetc(file_);

    word_list = (char**)malloc(sizeof(char*));
    while (!feof(file_)) {
        word_list = (char**)realloc(word_list, sizeof(char*)*(word_count+1));

        int cursor = 0;
        word_list[word_count] = (char*)malloc(sizeof(char));
        while (letter_ != '\n' && !feof(file_)) {
            word_list[word_count] = (char*)realloc(word_list[word_count], sizeof(char)*(cursor+1));
            word_list[word_count][cursor] = letter_;
            letter_ = fgetc(file_);
            cursor++;
        }
        word_list[word_count] = (char*)realloc(word_list[word_count], sizeof(char)*(cursor+1));
        word_list[word_count][cursor] = '\0';

        printf("%s\n", word_list[word_count]);
        word_count++;
        letter_ = fgetc(file_);
    }
    printf("\n");
    *N = word_count; 
    *ptr_word_list = word_list;

    order_word_list(ptr_word_list, N);
}

void read_file(int* N, char*** ptr_word_list) {
    char file_name[50];
    scanf("%s", file_name);
    // char file_name[50] = "words1.txt";

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

void read_file_and_create_list(void) {
    int N = 0;
    char** word_list = NULL;

    read_file(&N, &word_list);

    create_list();

    free_word_list(&word_list, &N);
}

void create_update_index_vector() {
}

void read_query_word(void) {
    char word_query[WORD_MAX_LENGTH];
    scanf("%s ", word_query);
    printf("%s\n", word_query);
}

void search() {
    read_query_word();
    
}

void process_command(int* command) {
    if (*command == 1) read_file_and_create_list();

    if (*command == 2) create_update_index_vector();

    if (*command == 3) search();

    if (*command == 0) exit(1);
}

void read_command(int* end_command) {
    int command = *end_command;
    scanf("%d ", &command);
    // command = 1;
    *end_command = command;
}


void process_all_commands(void) {
    int command = 0;
    while (!feof(stdin)) {
        read_command(&command);
        process_command(&command);
    }
}

int main(void) {
    process_all_commands();

    return 0;
}