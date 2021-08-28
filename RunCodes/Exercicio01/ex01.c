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

int main(void) {

    FILE* maze_file = read_labyrinth_from_file();

    int M, N, init_x, init_y;
    read_maze_dimensions(maze_file, &M, &N, &init_x, &init_y);



    fclose(maze_file);

    return 0;
}