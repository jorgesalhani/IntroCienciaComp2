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
    int mock_matrix[4][4] = {
        {1, 1, 1, 1}, 
        {2, 2, 1, 1}, 
        {2, 2, 1, 1}, 
        {2, 2, 3, 4}, 
    };

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

void get_quadrant_limits( int* M, int* N){
    int new_M, new_N;
    new_M = (*M)/2;
    new_N = (*N)/2;
    *M = new_M;
    *N = new_N;
}

bool is_quadrant_leaf(int*** image_matrix_pointer, int* start_M, int* start_N, int* end_M, int* end_N){
    int** image_matrix = *image_matrix_pointer;

    if ((*start_M == *end_M) && (*start_N == *end_N)) {
        return true;
    }

    int first_content = image_matrix[*start_M][*start_N];

    for (int i = *start_M; i < *end_M; i++) {
        for (int j = *start_N; i < *end_M; j++) {
            if (image_matrix[i][j] != first_content) {
                return false;
            }
        }
    }

    return true;
}

void get_new_start_and_end_limits(int* start_M, int* start_N, int* end_M, int* end_N) {
    int new_start_M, new_start_N;
    int new_end_M, new_end_N;

    new_end_M = (*end_M)*2;
    new_end_N = (*end_N)*2;

    new_start_M = (*end_M);
    new_start_N = (*end_N);

    *start_M = new_start_M;
    *start_N = new_start_N;

    *end_M = new_end_M;
    *end_N = new_end_N;
}

void quadtree_divide(int*** image_matrix_pointer, int* start_M, int* start_N, int* end_M, int* end_N, int dim_M, int dim_N) {

    get_quadrant_limits(end_M, end_N);

    bool is_leaf = is_quadrant_leaf(image_matrix_pointer, start_M, start_N, end_M, end_N);

    if (is_leaf) {
        printf("%d\n", *image_matrix_pointer[*start_M][*start_N]);
    }

    get_new_start_and_end_limits(start_M, start_N, end_M, end_N);

    if (*end_M <= dim_M || *end_N <= dim_N){
        return quadtree_divide(image_matrix_pointer, start_M, start_N, end_M, end_N, dim_M, dim_N);
    }

    return;
}

int main(void) {
    int M, N;
    get_image_dimensions(&M, &N);

    int** image_matrix = NULL;
    image_matrix = store_image(&M, &N);

    print_matrix(&image_matrix, &M, &N);

    int start_M, start_N;
    start_M = 0;
    start_N = 0;
    quadtree_divide(&image_matrix, &start_M, &start_N, &M, &N, M, N);

    free_matrix(&image_matrix, &M);

    return 0;
}