/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Exercicio 2: Compressao de imagem com quadtree
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void get_image_dimensions(int* M, int* N){
    // scanf("%d ", M);
    // scanf("%d ", N);
    *M = 4;
    *N = 4;
}

int** store_image(int* M, int* N) {
    int** image_matrix = NULL;
    image_matrix = (int**)malloc(sizeof(int*)*(*M));
    // int mock_matrix[16][16] = {
    //     {1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5}, 
    //     {2, 2, 1, 1, 2, 2, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5}, 
    //     {2, 2, 1, 1, 2, 2, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5}, 
    //     {2, 2, 3, 4, 2, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5}, 
    //     {1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5}, 
    //     {2, 2, 1, 1, 2, 2, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5}, 
    //     {2, 2, 1, 1, 2, 2, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5}, 
    //     {2, 2, 3, 4, 2, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5}, 
    //     {1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 6, 7, 7, 7, 7}, 
    //     {2, 2, 1, 1, 2, 2, 1, 1, 6, 6, 6, 6, 7, 7, 7, 7}, 
    //     {2, 2, 1, 1, 2, 2, 1, 1, 6, 6, 6, 6, 7, 7, 7, 7}, 
    //     {2, 2, 3, 4, 2, 2, 3, 4, 6, 6, 6, 6, 7, 7, 7, 7}, 
    //     {1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 9, 9, 9, 9, 9, 9}, 
    //     {2, 2, 1, 1, 2, 2, 1, 1, 8, 8, 9, 9, 9, 9, 9, 9}, 
    //     {2, 2, 1, 1, 2, 2, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9}, 
    //     {2, 2, 3, 4, 2, 2, 3, 4, 9, 9, 9, 9, 9, 9, 9, 9}, 
    // };

    int mock_matrix[4][4] = {
        {1, 1, 1, 1}, 
        {2, 2, 1, 1}, 
        {2, 2, 1, 1}, 
        {2, 2, 3, 4}, 
    };
    
    
    // int mock_matrix[8][8] = {
    //     {1, 1, 1, 1, 1, 1, 1, 1}, 
    //     {1, 1, 1, 1, 1, 1, 1, 1}, 
    //     {1, 1, 1, 1, 1, 1, 1, 1}, 
    //     {1, 1, 1, 1, 1, 1, 1, 1}, 
    //     {2, 2, 2, 2, 2, 2, 2, 2}, 
    //     {2, 2, 2, 2, 2, 2, 2, 2}, 
    //     {2, 2, 2, 2, 2, 2, 2, 2}, 
    //     {2, 2, 2, 2, 2, 2, 2, 2}, 
    // };
    
    for (int i = 0; i < *M; i++) {
        image_matrix[i] = (int*)malloc(sizeof(int)*(*N));
        for (int j = 0; j < *N; j++) {
            // scanf("%d ", &image_matrix[i][j]);
            image_matrix[i][j] = mock_matrix[i][j];
        }
    }

    return image_matrix;
}

void free_matrix(int*** image_matrix_pointer, int* M) {
    int** image_matrix = *image_matrix_pointer;
    for (int i = 0; i < *M; i++) {
        free(image_matrix[i]);
    }
    free(image_matrix);
}

void print_matrix(int*** image_matrix_pointer, int* M, int* N) {
    int** image_matrix = *image_matrix_pointer;
    for (int i = 0; i < *M; i++) {
        for (int j = 0; j < *N; j++) {
            printf("%d ", image_matrix[i][j]);
        }
        printf("\n");
    }
}

int* get_image_limits(int* M, int* N) {
    int* limits = NULL;
    limits = malloc(sizeof(int) * 2);
    limits[0] = (*M);
    limits[1] = (*N);
    return limits;
}

int** get_centers(int* M, int* N) {
    int** center = malloc(sizeof(int*) * 1);
    int* center[0] = malloc(sizeof(int) * 2);
    int m, n;
    m = (*M) / 2;
    n = (*N) / 2;
    center[0][0] = m;
    center[0][1] = n;
    return center;
}

void move_center(int** image_center_pointer, int** cursor_pointer) {
    int* center = *image_center_pointer;
    int* cursor = *cursor_pointer;

    if (cursor[0] < center[0]) {
        center[0] /= 2;
    } else {
        center[0] *= 2;
    }

    if (cursor[1] < center[1]) {
        center[1] /= 2;
    } else {
        center[1] *= 2;
    }
}

int quadtree(int*** image_matrix_pointer, int*** image_centers_pointer, int** image_limits_pointer, int* leafs) {
    int** matrix = *image_matrix_pointer;
    int** centers = *image_centers_pointer;
    int* limits = *image_limits_pointer;

    int col, line;
    int* cursor = NULL;
    cursor = malloc(sizeof(int) * 2);
    cursor[0] = 0;
    cursor[1] = 0;
    
    line = 0;
    while (line < limits[1]) {
        col = 0;
        while (col < limits[0]) {
            printf("%d\n", matrix[line][col]);
            if (matrix[line][col] != matrix[cursor[0]][cursor[1]]) {
                int leafs_ = (*leafs) + 1;
                (*leafs) = leafs_;
                move_center(image_center_pointer, &cursor);
                quadtree(image_matrix_pointer, image_center_pointer, image_limits_pointer, leafs);
            }
            col++;
        }
        line++;
    }

    free(cursor);
    return (*leafs);
}

int main(void) {
    int M, N;
    get_image_dimensions(&M, &N);
    int* image_limits = NULL;
    image_limits = get_image_limits(&M, &N);

    int** image_matrix = NULL;
    image_matrix = store_image(&M, &N);

    print_matrix(&image_matrix, &M, &N);

    int** image_center = NULL;
    image_center = get_centers(&M, &N);

    int leafs = -1;
    printf("%d\n", leafs);
    quadtree(&image_matrix, &image_center, &image_limits, &leafs);

    printf("\n");

    free_matrix(&image_center, &leafs);
    free_matrix(&image_matrix, &M);

    return 0;
}