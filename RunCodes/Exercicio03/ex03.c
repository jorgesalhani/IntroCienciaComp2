/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Exercicio 3: Busca Indexada com Lista Encadeada
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define WORD_MAX_LENGTH 100
#define ALPHABET_LETTERS 26

typedef struct index_vector
{
    char letter;
    char** word_block;
} IndexVector;


void free_word_list(char*** ptr_to_word_list, int* N) {
    char** word_list = *ptr_to_word_list;
    for (int i = 0; i < *N; i++) {
        free(word_list[i]);
    }
    free(word_list);
}

void copy_word(int* cursor, char*** ptr_word_list, char*** ptr_word_list_copy) {
    char** word_list = *ptr_word_list;
    char** word_list_copy = *ptr_word_list_copy;

    int word_length = strlen(word_list[*cursor]);
    word_list_copy[*cursor] = (char*)malloc(sizeof(char*)*(word_length+1));
    for (int i = 0; i < word_length; i++) {
        word_list_copy[*cursor][i] = word_list[*cursor][i];
    }
    word_list_copy[*cursor][word_length] = '\0';
}

void build_cumulate_frequency_histogram(int** ptr_keys_vector, int* key_range) {
    int* keys_vector = *ptr_keys_vector;
    int total = 0;
    for (int i = 0; i < *key_range; i++) {
        int count = keys_vector[i];
        keys_vector[i] = total;
        total = total + count;
    }
}

char** order_word_list(char*** ptr_word_list, int* N) {
    char** word_list = *ptr_word_list;
    int max, min, key;

    char** word_list_copy = NULL;
    word_list_copy = (char**)malloc(sizeof(char*)*(*N));

    max = min = (int)word_list[0][0];
    for (int i = 0; i < *N; i++) {
        key = (int)word_list[i][0];
        if (key > max) max = key;
        if (key < min) min = key;
        
        copy_word(&i, ptr_word_list, &word_list_copy);
    }

    int key_range = (max-min) + 1;
    int* keys_vector = (int*)calloc(key_range, sizeof(int));

    for (int i = 0; i < *N; i++) {
        key = (int)word_list[i][0];
        int key_position = key - min;
        keys_vector[key_position]++;
    }

    char** ordered_word_list = (char**)malloc(sizeof(char*)*(*N));
    for (int i = 0; i < *N; i++) {
        ordered_word_list[i] = (char*)calloc(sizeof(char), WORD_MAX_LENGTH);
    }

    build_cumulate_frequency_histogram(&keys_vector, &key_range);

    for (int i = *N-1; i >= 0; i--) {
        key = (int)word_list_copy[i][0];
        int word_correct_position = keys_vector[key - min];

        int word_length = strlen(word_list_copy[i]);
        for (int j = 0; j < word_length; j++) {
            ordered_word_list[word_correct_position][j] = word_list_copy[i][j];
        }

        keys_vector[key - min]++;
    }
    free(keys_vector);
    free_word_list(&word_list_copy, N);

    return ordered_word_list;
}

char** store_word_list(FILE* file_, int* N) {
    char** word_list = NULL;
    int word_count = 0;
    char letter_ = fgetc(file_);


    word_list = (char**)malloc(sizeof(char*));
    while (!feof(file_)) {
        word_list = (char**)realloc(word_list, sizeof(char*)*(word_count+1));

        int cursor = 0;
        word_list[word_count] = (char*)malloc(sizeof(char));
        while (letter_ != '\n' && !feof(file_)) {
            word_list[word_count] = (char*)realloc(word_list[word_count], sizeof(char)*(cursor+1));
            word_list[word_count][cursor] = letter_;
            letter_ = fgetc(file_);
            cursor++;
        }
        word_list[word_count] = (char*)realloc(word_list[word_count], sizeof(char)*(cursor+1));
        word_list[word_count][cursor] = '\0';

        word_count++;
        letter_ = fgetc(file_);
    }
    *N = word_count; 

    char** ordered_word_list = NULL;
    ordered_word_list = order_word_list(&word_list, N);
    free_word_list(&word_list, N);
    return ordered_word_list;
}

char** read_file_and_create_list(int* N) {
    char file_name[50];
    scanf("%s ", file_name);
    // char file_name[50] = "words1.txt";

    FILE* file_ = fopen(file_name, "r");
    if (file_ == NULL) {
        perror("Error opening file!\n");
        exit(-1);
    }

    char** ordered_word_list = NULL;
    ordered_word_list = store_word_list(file_, N);

    fclose(file_);
    return ordered_word_list;
}

char** get_block_words(char*** ptr_ordered_word_list, char letter, int* N, int* non_empty_indexes) {
    char** ordered_word_list = *ptr_ordered_word_list;
    int non_empty_indexes_ = *non_empty_indexes;

    char** block_words = (char**)malloc(sizeof(char*));

    int i = 0;
    for (i = 0; i < *N; i++) {
        int count = 0;
        int j = i;

        while (j < *N && ordered_word_list[j][0] == letter) {
            // printf("%s\n", ordered_word_list[j]);
            block_words[count] = (char*)malloc(sizeof(char)*(WORD_MAX_LENGTH));
            block_words[count] = ordered_word_list[j];
            count++;
            block_words = (char**)realloc(block_words, sizeof(char**)*(count+1));
            j++;
        }

        if (count > 0) {
            block_words = (char**)realloc(block_words, sizeof(char**)*(count+1));
            block_words[count] = (char*)malloc(sizeof(char));
            block_words[count] = "@";
            non_empty_indexes_++;
            *non_empty_indexes = non_empty_indexes_;
            break;
        }
    }

    if (i == *N) {
        free(block_words);
        block_words = NULL;
    }

    return block_words;
}

IndexVector* create_update_index_vector(char*** ptr_ordered_word_list, int* N, int* non_empty_indexes) {
    char** ordered_word_list = *ptr_ordered_word_list;

    IndexVector* index_vector = NULL;
    index_vector = (IndexVector*)malloc(sizeof(IndexVector)*ALPHABET_LETTERS);

    char letter_ = 'a';
    for (int i = 0; i < ALPHABET_LETTERS; i++) {
        index_vector[i].letter = letter_;

        char** word_block_list = get_block_words(ptr_ordered_word_list, letter_, N, non_empty_indexes);
        index_vector[i].word_block = word_block_list;
        letter_++;

        if (word_block_list != NULL) {
            int j = 0;
            char* word = word_block_list[j];
            while (word != "@") {
                // printf("(%c, %s)", index_vector[i].letter, (index_vector[i].word_block)[j]);
                word = word_block_list[j++];
            }
            // printf("\n");
            // free(word_block_list);
        }
    }

    return index_vector;
}


void search(IndexVector** ptr_index_vector, char*** ptr_ordered_word_list, int* N, int* non_empty_indexes) {
    if (*non_empty_indexes == 0) {
        printf("Vetor de indices nao atualizado.\n");
        return;
    }
    IndexVector* index_vector = *ptr_index_vector;
    char** ordered_word_list = *ptr_ordered_word_list;

    char query_word[WORD_MAX_LENGTH];
    scanf("%s", query_word);

    char key = query_word[0];
    // printf("QUERY: %s\n", query_word);

    int i = 0;
    for (i = 0; i < ALPHABET_LETTERS; i++) {
        char letter = index_vector[i].letter;
        if (letter == key) break;
    }
    // printf("INDEX i: %d\n\n", i);

    if (index_vector[i].word_block == NULL) {
            printf("Palavra nao existe na lista.\n");
    } else {
        for (int k = 0; k < *N; k++) {
            // printf("%s %s\n", ordered_word_list[k], index_vector[i].word_block[0]);
            if (strcmp(ordered_word_list[k], index_vector[i].word_block[0]) == 0) {
                int l = 0;
                char cursor_letter = key;
                int j = k;
                while (strcmp(ordered_word_list[j], query_word) != 0) {
                    cursor_letter = ordered_word_list[j++][0];
                    if (cursor_letter != key) {
                        printf("Palavra nao existe na lista.\n");
                        break;
                    }
                    l++;
                }
                if (strcmp(ordered_word_list[j], query_word) == 0) {
                    printf("%d\n", l);
                }
                break;
            }
            // printf("%s\n", index_vector[i].word_block[0]);
        }
    }

    // printf("(%c, %s) ", index_vector[i].letter, (index_vector[i].word_block)[0]);
}

void read_command(int* end_command) {
    int command = *end_command;
    scanf("%d ", &command);
    // command = 1;
    *end_command = command;
}

void print_three_first_words(char*** ptr_ordered_word_list) {
    char** word_list = *ptr_ordered_word_list;
    for (int i = 0; i < 3; i++) {
        printf("%s\n", word_list[i]);
    }
}


void process_all_commands(void) {
    int command = 0;

    char** ordered_word_list = NULL;
    int N = 0;
    int non_empty_indexes = 0;
    IndexVector* index_vector = NULL;

    while (!feof(stdin)) {
        read_command(&command);

        if (command == 1) {
            ordered_word_list = read_file_and_create_list(&N);
            print_three_first_words(&ordered_word_list);
        } else {
            if (command == 2) {
                index_vector = create_update_index_vector(&ordered_word_list, &N, &non_empty_indexes);
                printf("%d\n", non_empty_indexes);
            } else {
                if (command == 3) {
                    // char query_word[WORD_MAX_LENGTH];
                    // scanf("%s", query_word);

                    search(&index_vector, &ordered_word_list, &N, &non_empty_indexes);
                }
            }
        }

        if (command == 0) {
            for (int i = 0; i < ALPHABET_LETTERS; i++) {
                if (index_vector[i].word_block != NULL) {
                    int j = 0;
                    char* words = index_vector[i].word_block[j];
                    while (words != "@") {
                    //     printf("%p\t%s\n", &(index_vector[i].word_block[j]), (index_vector[i].word_block[j]));
                    //     // free(index_vector[i].word_block[j]);
                        words = index_vector[i].word_block[j++];
                    }
                    // printf("aAAA\n");
                    // printf("%p\t%s\n", &(index_vector[i].word_block[j-1]), (index_vector[i].word_block[j-1]));
                    // free(index_vector[i].word_block[0]);
                    // printf("aaa\n");

                    // j--;
                    // while (j >= 0) {
                    //     printf("%p\t%s\n", &(index_vector[i].word_block[j]), (index_vector[i].word_block[j]));
                    //     free(index_vector[i].word_block[j]);
                    //     j--;
                    // }
                    // free_word_list(&index_vector[i].word_block, &j);
                    // printf("%p\n", index_vector[i].word_block);
                    free(index_vector[i].word_block);
                }
            }
            // printf("%d\n", N);
            free_word_list(&ordered_word_list, &N);
            // printf("AAAA\n");
            free(index_vector);

            exit(1);
        }
    }
}

int main(void) {
    process_all_commands();

    return 0;
}