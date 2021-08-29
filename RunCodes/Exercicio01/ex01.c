#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

FILE* read_labyrinth_from_file(void) {
    char maze_file_name[100];
    scanf("%s ", maze_file_name);
    
    FILE* maze_file = fopen(maze_file_name, "r");
    if (maze_file == NULL) {
        perror("Error opening file!\n");
        exit(-1);
    }

    return maze_file;
}

void read_maze_dimensions(FILE* maze_file, int* M, int* N, int* init_x, int* init_y) {
    char dimensions_line[50];
    fgets(dimensions_line, 50, maze_file);

    *M = atoi(dimensions_line);
    *N = atoi(dimensions_line+2);

    char init_position_line [50];
    fgets(init_position_line, 50, maze_file);

    *init_x = atoi(init_position_line);
    *init_y = atoi(init_position_line+2);
}

char** store_maze_in_matrix(FILE* maze_file, int* M, int* N) {
    
    char** maze = NULL;
    maze = malloc(sizeof(char*)*(*M));
    char ch;
    for (int i = 0; i < *M; i++) {
        maze[i] = malloc(sizeof(char)*(*N));
        for (int j = 0; j < *N; j++) {
            ch = fgetc(maze_file);
            maze[i][j] = ch;
        }
        ch = fgetc(maze_file);
    }

    return maze;

}

void print_maze(char*** e_maze, int* M, int* N) {
    char** maze = *e_maze;
    for (int i = 0; i < *M; i++) {
        for (int j = 0; j < *N; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

void free_maze(char** maze, int* M) {
    for (int i = 0; i < *M; i++) {
        free(maze[i]);
    }
    free(maze);
}

bool found_egress(int* eM, int* eN, int* ex_pos, int* ey_pos) {
    if ((*ex_pos == 0 || *ex_pos == *eM-1) || (*ey_pos == 0 || *ey_pos == *eN-1)) {
        return true;
    }
    return false;
}

int next_step(char*** emaze, int* ex_pos, int* ey_pos) {
    char** maze = *emaze;
    int x = *ex_pos;
    int y = *ey_pos;

    char up = maze[x-1][y];
    char right = maze[x][y+1];
    char down = maze[x+1][y];
    char left = maze[x][y-1];

    if (up == '.') {
        *ex_pos -= 1;
        return 0;
    } else {
        if (right == '.') {
            *ey_pos += 1;
            return 0;
        } else {
            if (down == '.') {
                *ex_pos += 1;
                return 0;
            } else {
                if (left == '.') {
                    *ey_pos -= 1;
                    return 0;
                }
            }
        }
    }

    return 1;
}

bool found_endpoint(int *enext) {
    if (*enext == 1) {
        return true;
    }
    return false;
}

int breadcrumbs_fallback(char*** emaze, int* ex_pos, int* ey_pos) {
    char** maze = *emaze;
    int x = *ex_pos;
    int y = *ey_pos;

    char up = maze[x-1][y];
    char right = maze[x][y+1];
    char down = maze[x+1][y];
    char left = maze[x][y-1];

    if (up == '*') {
        *ex_pos -= 1;
        return 0;
    } else {
        if (right == '*') {
            *ey_pos += 1;
            return 0;
        } else {
            if (down == '*') {
                *ex_pos += 1;
                return 0;
            } else {
                if (left == '*') {
                    *ey_pos -= 1;
                    return 0;
                }
            }
        }
    }

    return 1;
}

char*** search_for_egress(char*** emaze, int* eM, int* eN, int* ex_pos, int* ey_pos) {

    char** maze = *emaze;
    bool egress = found_egress(eM, eN, ex_pos, ey_pos);
    if (egress) {
        maze[*ex_pos][*ey_pos] = '*';  
        return emaze;
    }

    maze[*ex_pos][*ey_pos] = '*';   
    // printf("%d %d\n", *ex_pos, *ey_pos);

    int next = next_step(emaze, ex_pos, ey_pos);
    bool endpoint = found_endpoint(&next);

    if (endpoint) {
        maze[*ex_pos][*ey_pos] = 'x'; 
        next = breadcrumbs_fallback(emaze, ex_pos, ey_pos);
    }
     
    // print_maze(emaze, eM, eN);
    // printf("\n\n");

    return search_for_egress(emaze, eM, eN, ex_pos, ey_pos);;
}

void calculate_maze_metrics(char*** emaze, int* eM, int* eN, int* en_barriers, int* en_paths) {
    char** maze = *emaze;
    int n_paths = 0;
    int n_barriers = 0;
    for (int i = 0; i < *eM; i++) {
        for (int j = 0; j < *eN; j++) {
            if (maze[i][j] == '.') {
                n_paths++;
            } else {
                if (maze[i][j] == '#') {
                    n_barriers++;
                }
            }
        }
    }

    *en_barriers = n_barriers;
    *en_paths = n_paths;

}

void calculate_maze_metrics_after_egress(char*** emaze, int* eM, int* eN, int* en_visited_paths, int* en_paths, double* efract_visited) {
    char** maze = *emaze;
    int n_visited_paths = 0;

    for (int i = 0; i < *eM; i++) {
        for (int j = 0; j < *eN; j++) {
            if (maze[i][j] == 'x') maze[i][j] = '*';
            if (maze[i][j] == '*') {
                n_visited_paths++;
            }
        }
    }
    *en_visited_paths = n_visited_paths;

    double fract_visited = ((double) n_visited_paths / (double) *en_paths) * 100;
    
    *efract_visited = fract_visited; 
}

void print_formated_results(int* en_barriers, int* en_paths,  int* en_visited_paths, double* efract_visited) {
    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", *en_barriers);
    printf("----Numero total de caminhos validos: %d\n", *en_paths);
    printf("----Numero total de caminhos visitados: %d\n", *en_visited_paths);
    printf("----Exploracao total do labirinto: %.1lf%%\n", *efract_visited);
}

int main(void) {

    FILE* maze_file = read_labyrinth_from_file();

    int M, N, init_x, init_y;
    read_maze_dimensions(maze_file, &M, &N, &init_x, &init_y);

    char** maze = NULL;
    maze = store_maze_in_matrix(maze_file, &M, &N);

    int n_barriers, n_paths;
    calculate_maze_metrics(&maze, &M, &N, &n_barriers, &n_paths);

    char*** egress = NULL;
    egress = search_for_egress(&maze, &M, &N, &init_x, &init_y); 

    int n_visited_paths;
    double fract_visited;
    calculate_maze_metrics_after_egress(&maze, &M, &N, &n_visited_paths, &n_paths, &fract_visited);

    print_maze(egress, &M, &N);

    // printf("%d\n", n_barriers);

    print_formated_results(&n_barriers, &n_paths, &n_visited_paths, &fract_visited);


    free_maze(maze, &M);
    fclose(maze_file);

    return 0;
}