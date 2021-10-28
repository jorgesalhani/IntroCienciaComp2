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

void get_unit_leafs(int*** image_matrix_pointer, int* start_M, int* start_N) {
    int** image_matrix = *image_matrix_pointer;

    int top_left = image_matrix[*start_M][*start_N];
    int top_right = image_matrix[*start_M][*start_N + 1];
    int bottom_left = image_matrix[*start_M + 1][*start_N];
    int bottom_right = image_matrix[*start_M + 1][*start_N + 1];

    printf("%d %d %d %d ", top_left, top_right, bottom_left, bottom_right);
}

int is_quadrant_leaf(int*** image_matrix_pointer, int* start_M, int* start_N, int* end_M, int* end_N){
    int** image_matrix = *image_matrix_pointer;

    int first_content = image_matrix[*start_M][*start_N];

    if (((*end_M == 1) && (*end_N == 1)) || ((*end_M == *start_M) && (*end_N == *start_N))) {
        get_unit_leafs(image_matrix_pointer, start_M, start_N);
        return first_content;
    }

    for (int i = *start_M; i < *end_M; i++) {
        for (int j = *start_N; j < *end_N; j++) {
            if (image_matrix[i][j] != first_content) {
                printf("%d ", -1);
                return -1;
            }
        }
    }

    printf("%d ",first_content);
    return first_content;
}

void get_subdivide_quadrant_limits(int* end_M, int* end_N, int* quadrant) {
    int new_M, new_N;

    if (*quadrant == 1) {
        new_M = (*end_M)/2;
        new_N = (*end_N)/2;
    }

    if (*quadrant == 3) {
        new_M = (*end_M)/2;
        new_N = (*end_N)/2;
    }

    if (*quadrant == 2) {
        new_M = (*end_M)/2;
        new_N = (*end_N)/2;
    }
    
    if (*quadrant == 4) {
        new_M = (*end_M)/2;
        new_N = (*end_N)/2;
    }

    *end_M = new_M;
    *end_N = new_N;
}

void get_parent_quadrant_limits(int* start_M, int* start_N, int* end_M, int* end_N, int* quadrant) {
    int new_start_M, new_start_N;
    int new_end_M, new_end_N;

    if (*quadrant == 1) {
        new_start_M = 0;
        new_end_M = (*end_M)*2;

        new_start_N = 0;
        new_end_N = (*end_N)*2;
    }

    if (*quadrant == 3) {
        new_start_M = (*end_M)*2;
        new_end_M = (*end_M)*4;

        new_start_N = 0;
        new_end_N = (*end_N)*2;
    }

    if (*quadrant == 2) {
        new_start_M = 0;
        new_end_M = (*end_N)*2;

        new_start_N = (*end_N);
        new_end_N = (*end_N)*4;
    }

    if (*quadrant == 4) {
        new_start_M = (*start_M);
        new_end_M = (*end_M)*2;

        new_start_N = (*start_M);
        new_end_N = (*end_M)*2;
    }

    *start_M = new_start_M;
    *start_N = new_start_N;

    *end_M = new_end_M;
    *end_N = new_end_N;
}

void quadtree_divide(int*** image_matrix_pointer, int* start_M, int* start_N, int* end_M, int* end_N, int* quadrant) {

    get_subdivide_quadrant_limits(end_M, end_N, quadrant);

    int is_leaf = is_quadrant_leaf(image_matrix_pointer, start_M, start_N, end_M, end_N);

    if (is_leaf == -1) {
        quadtree_divide(image_matrix_pointer, start_M, start_N, end_M, end_N, quadrant);
    } else {
        int quadrant_ = *quadrant + 1;
        if (quadrant_ <= 4) {
            *quadrant = quadrant_;
            get_parent_quadrant_limits(start_M, start_N, end_M, end_N, quadrant);
            quadtree_divide(image_matrix_pointer, start_M, start_N, end_M, end_N, quadrant);
        }
    }

    // if (*end_M <= ((*end_M)*2) || *end_N <= ((*end_N)*2)){
    //     return quadtree_divide(image_matrix_pointer, start_M, start_N, end_M, end_N);
    // }

}

int main(void) {
    int M, N, original_M;
    get_image_dimensions(&M, &N);
    original_M = M;

    int** image_matrix = NULL;
    image_matrix = store_image(&M, &N);

    // print_matrix(&image_matrix, &M, &N);

    int start_M, start_N, quadrant;
    start_M = 0;
    start_N = 0;
    quadrant = 1;
    int is_leaf = -1;
    printf("%d ", is_leaf);
    quadtree_divide(&image_matrix, &start_M, &start_N, &M, &N, &quadrant);
    printf("\n");

    free_matrix(&image_matrix, &original_M);

    return 0;
}