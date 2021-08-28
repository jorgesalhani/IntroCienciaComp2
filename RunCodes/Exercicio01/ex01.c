#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int main(void) {

    FILE* maze_file = read_labyrinth_from_file();

    int M, N, init_x, init_y;
    read_maze_dimensions(maze_file, &M, &N, &init_x, &init_y);

    char** maze = NULL;
    maze = store_maze_in_matrix(maze_file, &M, &N);

    print_maze(&maze, &M, &N);


    free_maze(maze, &M);
    fclose(maze_file);

    return 0;
}