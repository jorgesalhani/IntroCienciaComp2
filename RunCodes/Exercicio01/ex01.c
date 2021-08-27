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

int main(void) {

    FILE* maze_file = read_labyrinth_from_file();

    char ch = 'a';

    while (ch != EOF) {
        ch = fgetc(maze_file);
        printf("%c", ch);
    }

    fclose(maze_file);

    return 0;
}