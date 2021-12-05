/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Trabalho 03: Escalonador de processos
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int** store_list(int* N) {
    int** process_list = NULL;
    process_list = malloc(sizeof(int*));

    int file_item, line_cursor, column_cursor;
    file_item = 0;
    line_cursor = 0;
    column_cursor = 0;

    process_list[0] = malloc(sizeof(int)*4);

    while (!feof(stdin)) {
        fscanf(stdin, "%d", &file_item);
        process_list[line_cursor][column_cursor] = file_item;

        column_cursor = (column_cursor + 1) % 4;
        if (column_cursor == 0 && !feof(stdin)) {
            line_cursor++;
            process_list = realloc(process_list, sizeof(int*)*(line_cursor+1));
            process_list[line_cursor] = malloc(sizeof(int)*4);
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
        for (int j = 0; j < 4; j++) {
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

void round_robin(int*** ptr_process_list, int* N, int* init_process) {
    int** process_list = *ptr_process_list;

    int time_quantum = 1;

    int total = 0, x, counter = 0;
    int wait_time = 0, turnaround_time = 0;
    int process_index, time_recognized, time_execution, priority;
    int total_time = 0;

    int total_process = *N;
    int i = 0;
    while (total_process != 0) {
        process_index = process_list[i][0];
        time_recognized = process_list[i][1];
        time_execution = process_list[i][2];
        priority = process_list[i][3];

        if (time_recognized <= time_quantum && time_recognized > 0) {
            total_time = total_time + time_recognized;
            time_recognized = 0;
            counter = 1;
        }

        if (time_recognized > 0) {
            time_recognized = time_recognized - time_quantum;
            total_time = total_time + time_quantum;
        }

        if (time_recognized == 0 && counter == 1) {
            printf("\nProcess[%d]\t\t%d\t\t%d\t\t\t%d", i + 1, time_execution, total_time - time_recognized, total_time - time_recognized - time_execution);

            wait_time = wait_time + total_time - time_recognized - time_execution;
            turnaround_time = turnaround_time + total_time - time_recognized;
            counter = 0;
            total_process--;
        }

        if (i == *N - 1) {
            i = 0;
        } else if (process_list[i+1][1] <= total_time) {
            i++;
        } else {
            i = 0;
        }
    }
}

void select_scheduler_algorithm(int*** ptr_process_list, int* N, int process_priority_i, int process_priority_j) {
    int init_process;
    if (process_priority_i == process_priority_j) {
        init_process = 0;
        round_robin(ptr_process_list, N, &init_process);
    }

    if (process_priority_i > process_priority_j) {
        init_process = 1;
        round_robin(ptr_process_list, N, &init_process);
    }
}


void process_by_scheduler_algorithm(int*** ptr_process_list, int* N) {
    int** process_list = *ptr_process_list;

    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++) {
            if (i != j) {
                select_scheduler_algorithm(ptr_process_list, N, process_list[i][3], process_list[j][3]);
            }
        }
    }

}

int main(void) {
    // int** process_list = NULL;
    int N = 4;

    // process_list = store_list(&N);

    int** process_list = malloc(sizeof(int*)*4);
    for (int i = 0; i < 4; i++) {
        process_list[i] = calloc(4, sizeof(int));
    }
    process_list[0][0] = 333;
    process_list[0][1] = 1;
    process_list[0][2] = 5;
    process_list[0][3] = 4;
    process_list[1][0] = 1571;
    process_list[1][1] = 1;
    process_list[1][2] = 3;
    process_list[1][3] = 3;
    process_list[2][0] = 1571;
    process_list[2][1] = 2;
    process_list[2][2] = 1;
    process_list[2][3] = 2;
    process_list[3][0] = 227;
    process_list[3][1] = 5;
    process_list[3][2] = 2;
    process_list[3][3] = 1;

    made_code_unique_recursively(&process_list, &N, true);

    process_by_scheduler_algorithm(&process_list, &N);

    print_process_list(process_list, &N);

    free_matrix(process_list, &N);
    return 0;
}