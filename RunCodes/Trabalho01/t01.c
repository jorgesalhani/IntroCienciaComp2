#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_selected_option() {
    int selected_option;
    scanf("%d ", &selected_option);

    return selected_option;
}

FILE* read_mine_from_file() {
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

int main(void) {

    int selected_option = get_selected_option();

    FILE* mine_file = read_mine_from_file();

    char** mine_map = NULL;
    int M, N;
    M = 0;
    N = 0;

    mine_map = store_mine_map_from_file(mine_file, &M, &N);
    print_mine_map(&mine_map, &M, &N);

    free_mine_map(mine_map, &M);
    fclose(mine_file);
    return 0;
}