/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Trabalho 03: Escalonador de processos
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COLUMNS 4

int** store_list(int* N) {
    int** process_list = NULL;
    process_list = malloc(sizeof(int*));

    int file_item, line_cursor, column_cursor;
    file_item = 0;
    line_cursor = 0;
    column_cursor = 0;

    process_list[0] = malloc(sizeof(int)*COLUMNS);

    while (!feof(stdin)) {
        fscanf(stdin, "%d", &file_item);
        process_list[line_cursor][column_cursor] = file_item;

        column_cursor = (column_cursor + 1) % COLUMNS;
        if (column_cursor == 0 && !feof(stdin)) {
            line_cursor++;
            process_list = realloc(process_list, sizeof(int*)*(line_cursor+1));
            process_list[line_cursor] = malloc(sizeof(int)*COLUMNS);
        }
    }

    (*N) = line_cursor+1;

    return process_list;
}

void free_matrix(int** process_list, int* N) {
    for (int i = 0; i < *N; i++) {
        free(process_list[i]);
    }
    free(process_list);
}

void print_process_list(int** process_list, int* N) {
    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("%d ", process_list[i][j]);
        }
        printf("\n");
    }
}

void made_code_unique_recursively(int*** ptr_process_list, int* N, bool changes_ocurred) {
    int** process_list = *ptr_process_list;
    changes_ocurred = false;
    int max = process_list[0][0];
    int index_process_with_same_code = 0;
    for (int i = 1; i < *N; i++) {
        if (process_list[i][0] > max) max = process_list[i][0];
        for (int j = *N-1; j >= 0; j--) {
            if (i != j && process_list[i][0] == process_list[j][0]) {
                process_list[j][0]++;
                changes_ocurred = true;
            }
        }
    }
    if (changes_ocurred) {
        made_code_unique_recursively(ptr_process_list, N, changes_ocurred);
    }
}

int** order_by_priority(int*** ptr_process_list, int* N) {
    int** process_list = *ptr_process_list;
    int** ordered_list = NULL;
    ordered_list = (int**)malloc(sizeof(int*)*(*N));
    for (int i = 0; i < *N; i++) {
        ordered_list[i] = (int*)calloc(COLUMNS, sizeof(int));
    }

    for (int i = 0; i < *N; i++) {
        int cursor = i;
        int cursor_priority = process_list[i][3];
        for (int j = i+1; j < *N; j++) {
            if (process_list[j][3] > cursor_priority) {
                cursor = j;
            }
        }

        for (int k = 0; k < COLUMNS; k++) {
            ordered_list[i][k] = process_list[cursor][k];
            process_list[cursor][k] = process_list[i][k];
        }
    }
    return ordered_list;
}

void add_new_process_by_time(int ***ptr_ordered_process, int *process_i, int *total_time) {
    int** ordered_list = *ptr_ordered_process;

    for (int i = 0; i < *process_i; i++) {
        if (ordered_list[i][1] == *total_time) {
            *process_i = i;
        }
    }
}

void execute_process(int ***ptr_ordered_process, int *N, int process_i, int *total_time, bool *must_increment_time) {
    int** ordered_list = *ptr_ordered_process;

    if (ordered_list[process_i][1] <= *total_time && ordered_list[process_i][2] > 0){
        ordered_list[process_i][2]--;
        if (ordered_list[process_i][2] == 0) {
            int N_ = *N;
            N_--;
            *N = N_;
            printf("%d %d\n", ordered_list[process_i][0], *total_time);
        }
        *must_increment_time = true;
    }
}

void increment_time(int *total_time, bool *must_increment_time) {
    if (must_increment_time) {
        int total_time_ = *total_time;
        total_time_++;
        *total_time = total_time_;
    }
}

void process_events(int ***ptr_ordered_process, int process_i, int *N, int* total_processes, int* total_time) {
    int** ordered_list = *ptr_ordered_process;

    if (*N == 0) return;

    add_new_process_by_time(ptr_ordered_process, &process_i, total_time);

    bool must_increment_time = false;

    execute_process(ptr_ordered_process, N, process_i, total_time, &must_increment_time);

    process_i = (process_i + 1)%(*total_processes);

    increment_time(total_time, &must_increment_time);

    process_events(ptr_ordered_process, process_i, N, total_processes, total_time);
}

void select_scheduler_algorithm(int*** ptr_process_list, int* N, int* total_processes) {
    int** process_list = *ptr_process_list;

    int **ordered_by_priority = order_by_priority(ptr_process_list, N);

    int process_i = 0;
    int total_time = 1;

    process_events(&ordered_by_priority, process_i, N, total_processes, &total_time);
    free_matrix(ordered_by_priority, total_processes);
}


void process_by_scheduler_algorithm(int*** ptr_process_list, int* N, int* total_processes) {
    int** process_list = *ptr_process_list;
    select_scheduler_algorithm(ptr_process_list, N, total_processes);

}

int main(void) {
    int** process_list = NULL;
    int N = 0;

    process_list = store_list(&N);

    made_code_unique_recursively(&process_list, &N, true);

    int total_processes = N;
    process_by_scheduler_algorithm(&process_list, &N, &total_processes);

    free_matrix(process_list, &total_processes);
    return 0;
}