/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Trabalho 03: Escalonador de processos
*/

#include <stdio.h>
#include <stdlib.h>

FILE* read_file(void) {
    char filename[50] = "1.in";
    // scanf("%s ", filename);
    
    FILE* process_file = fopen(filename, "r");
    if (process_file == NULL) {
        perror("Error opening file!\n");
        exit(-1);
    }
    return process_file;
}

int** store_list(int* N) {
    int** process_list = NULL;
    process_list = malloc(sizeof(int*));

    FILE* process_file = read_file();

    int file_item, line_cursor, column_cursor;
    file_item = 0;
    line_cursor = 0;
    column_cursor = 0;

    process_list[0] = malloc(sizeof(int)*4);

    while (!feof(process_file)) {
        fscanf(process_file, "%d", &file_item);
        process_list[line_cursor][column_cursor] = file_item;

        column_cursor = (column_cursor + 1) % 4;
        if (column_cursor == 0 && !feof(process_file)) {
            line_cursor++;
            process_list = realloc(process_list, sizeof(int*)*(line_cursor+1));
            process_list[line_cursor] = malloc(sizeof(int)*4);
        }
    }

    (*N) = line_cursor+1;
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", process_list[i][j]);
        }
        printf("\n");
    }

    fclose(process_file);
    return process_list;
}

void free_matrix(int** process_list, int* N) {
    for (int i = 0; i < *N; i++) {
        free(process_list[i]);
    }
    free(process_list);
}

int main(void) {
    int** process_list = NULL;
    int N = 0;

    process_list = store_list(&N);

    free_matrix(process_list, &N);
    return 0;
}