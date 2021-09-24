/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Trabalho 01: Campo Minado
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int get_selected_option(void) {
    int selected_option;
    scanf("%d ", &selected_option);
    // selected_option = 3;

    return selected_option;
}

FILE* read_mine_from_file(void) {
    char mine_filename[100];
    scanf("%s ", mine_filename);

    FILE* mine_file = fopen(mine_filename, "r");
    if (mine_filename == NULL) {
        perror("Error opening file!\n");
        exit(-1);
    }

    return mine_file;    
}

char** store_mine_map_from_file(FILE* mine_file, int* M, int* N) {
    char** mine_map = NULL;
    mine_map = malloc(sizeof(char*));
    
    char mine_item; 
    mine_item = fgetc(mine_file);
    
    int i = 0;
    int j_global = 0;
    while (mine_item != EOF)
    {
        mine_map = realloc(mine_map, sizeof(char*)*(i+1));
        mine_map[i] = malloc(sizeof(char));
        int j = 0;
        while (mine_item != '\n')
        {
            mine_map[i] = realloc(mine_map[i], sizeof(char)*(j+1));
            mine_map[i][j] = mine_item;
            mine_item = fgetc(mine_file);
            j++;
        }
        if (i == 0) {
            j_global = j;
        }
        mine_item = fgetc(mine_file);
        i++;
    }
    
    *M = i;
    *N = j_global; 

    return mine_map;
}

void free_mine_map(char** mine_map, int* M) {
    for (int i = 0; i < *M; i++) {
        free(mine_map[i]);
    }
    free(mine_map);
}

void print_mine_map(char*** pointer_to_mine_map, int* M, int* N) {
    char** mine_map = *pointer_to_mine_map;
    for (int i = 0; i < *M; ++i) {
        for (int j = 0; j < *N; ++j) {
            printf("%c", mine_map[i][j]);
        }
        printf("\n");
    }
}

bool position_has_no_mines(char*** pointer_to_mine_map, int pos_i, int pos_j) {
    char** mine_map = *pointer_to_mine_map;
    if (mine_map[pos_i][pos_j] == '*') {
        return false;
    }
    return true;
}

bool position_already_counted(char*** pointer_to_mine_map, int i, int j) {
    char** mine_map = *pointer_to_mine_map;
    if (mine_map[i][j] == '.') {
        return false;
    }
    return true;
}

void top_left_corner_edge_limits(int* edge_limits) {
        edge_limits[0] = 0;
        edge_limits[1] = 2;
        edge_limits[2] = 0;
        edge_limits[3] = 2;
}

void top_right_corner_edge_limits(int* edge_limits){
    edge_limits[0] = 0;
    edge_limits[1] = 2;
    edge_limits[2] = -1;
    edge_limits[3] = 1;
}

void top_edge_limits(int* edge_limits) {
    edge_limits[0] = 0;
    edge_limits[1] = 2;
    edge_limits[2] = -1;
    edge_limits[3] = 2;
}

void bottom_right_corner_edge_limits(int* edge_limits) {
    edge_limits[0] = -1;
    edge_limits[1] = 1;
    edge_limits[2] = -1;
    edge_limits[3] = 1;
}

void bottom_left_corner_edge_limits(int* edge_limits) {
    edge_limits[0] = -1;
    edge_limits[1] = 1;
    edge_limits[2] = 0;
    edge_limits[3] = 2;
}

void bottom_edge_limits(int* edge_limits) {
    edge_limits[0] = -1;
    edge_limits[1] = 1;
    edge_limits[2] = -1;
    edge_limits[3] = 2;
}

void left_edge_limits(int* edge_limits) {
    edge_limits[0] = -1;
    edge_limits[1] = 2;
    edge_limits[2] = 0;
    edge_limits[3] = 2;
}

void right_edge_limits(int* edge_limits) {
    edge_limits[0] = -1;
    edge_limits[1] = 2;
    edge_limits[2] = -1;
    edge_limits[3] = 1;
}

void middle_edge_limits(int* edge_limits) {
    edge_limits[0] = -1;
    edge_limits[1] = 2;
    edge_limits[2] = -1;
    edge_limits[3] = 2;
}

void get_edge_limits(char*** pointer_to_mine_map, int* edge_limits, int* pos_i, int* pos_j, int* M, int* N) {
    int i = *pos_i;
    int j = *pos_j;

    if (i == 0) {
        if (j == 0) {
            top_left_corner_edge_limits(edge_limits);
            return;
        }

        if (j == (*N - 1)) {
            top_right_corner_edge_limits(edge_limits);
            return;
        }

        top_edge_limits(edge_limits);
        return;
    }

    if (i == (*M - 1)) {
        if (j == (*N - 1)) {
            bottom_right_corner_edge_limits(edge_limits);
            return;
        }

        if (j == 0) {
            bottom_left_corner_edge_limits(edge_limits);
            return;
        }

        bottom_edge_limits(edge_limits);
        return;
    }

    if (j == 0) {
        left_edge_limits(edge_limits);
        return;
    }

    if (j == (*N - 1)) {
        right_edge_limits(edge_limits);
        return;
    }

    middle_edge_limits(edge_limits);
    return;
}

void add_one_near_mine(char*** pointer_to_mine_map, int* pos_i, int* pos_j, int* M, int* N) {
    char** mine_map = *pointer_to_mine_map;

    int* edge_limits = NULL;
    edge_limits = calloc(4, sizeof(int));

    get_edge_limits(pointer_to_mine_map, edge_limits, pos_i, pos_j, M, N);

    int i = *pos_i;
    int j = *pos_j;

    for (int x = edge_limits[0]; x < edge_limits[1]; x++) {
        for (int y = edge_limits[2]; y < edge_limits[3]; y++) {
            if (position_has_no_mines(pointer_to_mine_map, (i + x), (j + y))) {
                if (position_already_counted(pointer_to_mine_map, (i+x), (j+y))) {
                    mine_map[i+x][j+y] += 1;
                } else {
                    mine_map[i+x][j+y] = 0 + '0';
                    mine_map[i+x][j+y] += 1;
                }
            }
        }
    }

    free(edge_limits);
}

void fill_mine_map_with_hints(char*** pointer_to_mine_map, int* M, int* N) {
    char** mine_map = *pointer_to_mine_map;

    for (int i = 0; i < (*M); i++) {
        for (int j = 0; j < (*N); j++) {
            char mine_item = mine_map[i][j];
            if (mine_item == '*') {
                add_one_near_mine(pointer_to_mine_map, &i, &j, M, N);
            }
        }
    }
}

void print_mine_map_with_hints(char*** pointer_to_mine_map, int* M, int* N) {
    fill_mine_map_with_hints(pointer_to_mine_map, M, N);
    print_mine_map(pointer_to_mine_map, M, N);
}

void hide_map(char*** pointer_to_mine_map, int* cursor_x, int* cursor_y, int* M, int* N) {
    char** mine_map = *pointer_to_mine_map;
    for (int i = 0; i < (*M); i++) {
        for (int j = 0; j < (*N); j++) {
            if (i == *cursor_x && j == *cursor_y) {
            } else {
                mine_map[i][j] = 'X';
            }
        }
    }
}

void fill_known_mine_map(char*** pointer_to_mine_map, int* M, int* N) {
    char** mine_map = *pointer_to_mine_map;
    for (int i = 0; i < *M; i++) {
        for (int j = 0; j < *N; j++) {
            if (mine_map[i][j] == 'X') mine_map[i][j] = '0';
        }
    }
}

void print_mine_map_formated(char*** pointer_to_mine_map, int* M, int* N) {
    char** mine_map = *pointer_to_mine_map;
    for (int i = 0; i < *M; i++) {
        for (int j = 0; j < *N; j++) {
            if (mine_map[i][j] == '0') mine_map[i][j] = '.';
            printf("%c", mine_map[i][j]);
        }
        printf("\n");
    }
}

void print_partially_hide_map(char*** pointer_to_mine_map, int* M, int* N) {
    char** mine_map = *pointer_to_mine_map;
    int* edge_limits = NULL;

    fill_known_mine_map(pointer_to_mine_map, M, N);

    bool mine_frontier = false;;
    for (int i = 0; i < *M; i++) {
        for (int j = 0; j < *N; j++) {

            if (mine_map[i][j] == 'X') {
                mine_map[i][j] = '0';
            }

            mine_frontier = false;

            if (mine_map[i][j] != '0') {
                edge_limits = calloc(4, sizeof(int));
                get_edge_limits(pointer_to_mine_map, edge_limits, &i, &j, M, N);

                for (int x = edge_limits[0]; x < edge_limits[1]; x++) {
                    for (int y = edge_limits[2]; y < edge_limits[3]; y++) {
                        if (mine_map[i+x][j+y] == '0') {
                            mine_frontier = true;
                            break;
                        }
                    }
                    if (mine_frontier) break;
                }

                if (!mine_frontier) mine_map[i][j] = 'X';
                if (mine_map[i][j] == '0') mine_map[i][j] = '.';

                free(edge_limits);
            }
        }
    }

    print_mine_map_formated(pointer_to_mine_map, M, N);
}

void partially_hide_map(char*** pointer_to_mine_map, int* cursor_x, int* cursor_y, int* M, int* N) {
    char** mine_map = *pointer_to_mine_map;

    int* edge_limits = NULL;
    edge_limits = calloc(4, sizeof(int));
    get_edge_limits(pointer_to_mine_map, edge_limits, cursor_x, cursor_y, M, N);
    // printf("%d %d\n", *cursor_x, *cursor_y);
    // print_mine_map(pointer_to_mine_map, M, N);
    // printf("\n\n");

    if (edge_limits[0] == -1) {
        if (!position_already_counted(pointer_to_mine_map, *cursor_x - 1, *cursor_y)) {
            mine_map[*cursor_x - 1][*cursor_y] = 0 + '0';
            *cursor_x = *cursor_x - 1;
            partially_hide_map(pointer_to_mine_map, cursor_x, cursor_y, M, N);
            *cursor_x = *cursor_x + 1;
        }

        if (edge_limits[2] == -1) {
            if (!position_already_counted(pointer_to_mine_map, *cursor_x - 1, *cursor_y - 1)) {
                mine_map[*cursor_x - 1][*cursor_y - 1] = 0 + '0';
                *cursor_x = *cursor_x - 1;
                *cursor_y = *cursor_y - 1;
                partially_hide_map(pointer_to_mine_map, cursor_x, cursor_y, M, N);
                *cursor_x = *cursor_x + 1;
                *cursor_y = *cursor_y + 1;
            }
        }

        if (edge_limits[3] == 2) {
            if (!position_already_counted(pointer_to_mine_map, *cursor_x - 1, *cursor_y + 1)) {
                mine_map[*cursor_x - 1][*cursor_y + 1] = 0 + '0';
                *cursor_x = *cursor_x - 1;
                *cursor_y = *cursor_y + 1;
                partially_hide_map(pointer_to_mine_map, cursor_x, cursor_y, M, N);
                *cursor_x = *cursor_x + 1;
                *cursor_y = *cursor_y - 1;
            }
        }
    }

    if (edge_limits[3] == 2) {
        if (!position_already_counted(pointer_to_mine_map, *cursor_x, *cursor_y + 1)) {
            mine_map[*cursor_x][*cursor_y + 1] = 0 + '0';
            *cursor_y = *cursor_y + 1;
            partially_hide_map(pointer_to_mine_map, cursor_x, cursor_y, M, N);
            *cursor_y = *cursor_y - 1;
        }

        if (edge_limits[1] == 2) {
            if (!position_already_counted(pointer_to_mine_map, *cursor_x + 1, *cursor_y + 1)) {
                mine_map[*cursor_x + 1][*cursor_y + 1] = 0 + '0';
                *cursor_x = *cursor_x + 1;
                *cursor_y = *cursor_y + 1;
                partially_hide_map(pointer_to_mine_map, cursor_x, cursor_y, M, N);
                *cursor_x = *cursor_x - 1;
                *cursor_y = *cursor_y - 1;
            }
        }
    }

    if (edge_limits[1] == 2) {
        if (!position_already_counted(pointer_to_mine_map, *cursor_x + 1, *cursor_y)) {
            mine_map[*cursor_x + 1][*cursor_y] = 0 + '0';
            *cursor_x = *cursor_x + 1;
            partially_hide_map(pointer_to_mine_map, cursor_x, cursor_y, M, N);
            *cursor_x = *cursor_x - 1;
        }

        if (edge_limits[2] == -1) {
            if (!position_already_counted(pointer_to_mine_map, *cursor_x + 1, *cursor_y - 1)) {
                mine_map[*cursor_x + 1][*cursor_y - 1] = 0 + '0';
                *cursor_x = *cursor_x + 1;
                *cursor_y = *cursor_y - 1;
                partially_hide_map(pointer_to_mine_map, cursor_x, cursor_y, M, N);
                *cursor_x = *cursor_x - 1;
                *cursor_y = *cursor_y + 1;
            }
        }
    } 


    if (edge_limits[2] == -1 && 
        !position_already_counted(pointer_to_mine_map, *cursor_x, *cursor_y - 1)) {
        mine_map[*cursor_x][*cursor_y - 1] = 0 + '0';
        *cursor_y = *cursor_y - 1;
        partially_hide_map(pointer_to_mine_map, cursor_x, cursor_y, M, N);
        *cursor_y = *cursor_y + 1;
    }

    mine_map[*cursor_x][*cursor_y] = 'X';

    // printf("%d %d\n", *cursor_x, *cursor_y);
    // print_mine_map(pointer_to_mine_map, M, N);
    // printf("\n\n");
    

    free(edge_limits);
    
}


void user_flow_after_chosen_position(char*** pointer_to_mine_map, int* M, int* N, int* cursor_x, int* cursor_y) {
    char** mine_map = *pointer_to_mine_map;
    int x = *cursor_x;
    int y = *cursor_y;

    fill_mine_map_with_hints(pointer_to_mine_map, M, N);

    if (mine_map[x][y] == '*') {
        print_mine_map(pointer_to_mine_map, M, N);
        return;
    }

    if (position_already_counted(pointer_to_mine_map, x, y)) {
        hide_map(pointer_to_mine_map, cursor_x, cursor_y, M, N);
        print_mine_map(pointer_to_mine_map, M, N);
        return;
    } else {
        partially_hide_map(pointer_to_mine_map, cursor_x, cursor_y, M, N);
        print_partially_hide_map(pointer_to_mine_map, M, N);
        return;
    }
}

void user_control(char*** pointer_to_mine_map, int* M, int* N) {
    int cursor_x = 0;
    int cursor_y = 0;
    scanf("%d ", &cursor_x);
    scanf("%d ", &cursor_y);
    
    user_flow_after_chosen_position(pointer_to_mine_map, M, N, &cursor_x, &cursor_y);
}

void option_one(char*** pointer_to_mine_map, int* M, int* N, int* selected_option) {
    if (*selected_option == 1) print_mine_map(pointer_to_mine_map, M, N);
}

void option_two(char*** pointer_to_mine_map, int* M, int* N, int* selected_option) {
    if (*selected_option == 2) print_mine_map_with_hints(pointer_to_mine_map, M, N);
}

void option_three(char*** pointer_to_mine_map, int* M, int* N, int* selected_option) {
    if (*selected_option == 3) user_control(pointer_to_mine_map, M, N);
}

int main(void) {

    int selected_option = get_selected_option();

    FILE* mine_file = read_mine_from_file();

    char** mine_map = NULL;
    int M, N;
    M = 0;
    N = 0;

    mine_map = store_mine_map_from_file(mine_file, &M, &N);

    option_one(&mine_map, &M, &N, &selected_option);
    option_two(&mine_map, &M, &N, &selected_option);
    option_three(&mine_map, &M, &N, &selected_option);

    free_mine_map(mine_map, &M);
    fclose(mine_file);
    return 0;
}
