/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Trabalho 04: Hash Table
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char ADD[4] = "add";
const char GET[4] = "get";
const char CHECK[6] = "check";
const char DEL[4] = "del";

#define X 263
#define P 1000000007

typedef struct Chain_List
{
    char *word;
    struct Chain_List *chain_list;
} ChainList;



void read_list_and_instructions_number(int *list_number, int *instructions_number) {
    scanf("%d ", list_number);
    scanf("%d ", instructions_number);
}

char *read_input_word(void) {
    char *instruction = NULL;
    
    char instruction_letter;
    instruction_letter = fgetc(stdin);
    int letter_count = 0;
    while (!feof(stdin) && instruction_letter != ' ' && instruction_letter != '\n') {
        instruction = (char*)realloc(instruction, sizeof(char)*(letter_count+1));
        instruction[letter_count] = instruction_letter;
        instruction_letter = fgetc(stdin);
        letter_count++;
    }
    instruction = (char*)realloc(instruction, sizeof(char)*(letter_count+1));
    instruction[letter_count] = '\0';
    return instruction;
}

long int calculate_power(int base, int exponent, int result) {
    if (exponent == 0) return result;
    result = result * base;
    exponent--;
    calculate_power(base, exponent, result);
}

int calculate_hash_position(char *word, int *list_number) {
    int word_length = strlen(word);
    int hash_sum = 0;
    int hash_sum_i = 0;
    int ascii_code = 0;
    long int x_pow_i = 0;

    for (int i = 0; i < word_length; i++) {
        ascii_code = (int)word[i];
        x_pow_i = calculate_power(X, i, 1);

        hash_sum_i = (ascii_code * x_pow_i)%P;
        hash_sum = hash_sum + hash_sum_i;
    }

    hash_sum = hash_sum%(*list_number);

    return hash_sum;
}

void read_int_parameter(int *int_parameter) {
    scanf("%d ", int_parameter);
}

bool check_position_availability(ChainList **ptr_chain_list, int *word_position) {
    ChainList *chain_list = *ptr_chain_list;
    if (chain_list[*word_position].word == NULL) return true;
    return false;
}

bool check_word_existence(ChainList **ptr_chain_list, int *word_position, char* word) {
    ChainList *chain_list = *ptr_chain_list;
    char *word_content = chain_list[*word_position].word;
    ChainList *new_chain = chain_list[*word_position].chain_list;
    while (new_chain != NULL) {
        if (strcmp(new_chain[0].word, word) == 0) return true;
        new_chain = new_chain->chain_list;
    }
    return false;
}

void add_word_to_list_beginning(ChainList **ptr_chain_list, int *word_position, char *word) {
    // ChainList *chain_list = *ptr_chain_list;
    // ChainList *new_chain = NULL;
    // strcpy(new_chain->word, word);
    
    // chain_list[*word_position].chain_list = new_chain->chain_list;
    // new_chain->chain_list = 

}

void execute_add(char *word, ChainList **ptr_chain_list, int *list_number) {
    ChainList *chain_list = *ptr_chain_list;
    int word_position = calculate_hash_position(word, list_number);
    bool is_position_available = check_position_availability(ptr_chain_list, &word_position);
    
    if (is_position_available) {
        int word_length = strlen(word);
        chain_list[word_position].word = (char*)malloc(sizeof(char)*(word_length+1));
        chain_list[word_position].word[word_length] = '\0';
        strcpy(chain_list[word_position].word, word);
        return;
    }

    bool is_word_in_list = check_word_existence(ptr_chain_list, &word_position, word);
    if (!is_word_in_list) {
        add_word_to_list_beginning(ptr_chain_list, &word_position, word);
    }

}

void execute_get() {

}

void execute_check() {

}

void execute_del() {

}

// void free_chain_lists(ChainList **ptr_chain_list, int *list_number) {
//     ChainList *chain_list = *ptr_chain_list;
//     for (int i = 0; i < *list_number; i++) {
//         if (chain_list[i].chain_list != NULL) {
//             ChainList *new_chain = chain_list[i].chain_list;
//             while (new_chain != NULL) {
//                free()
//                 new_chain = new_chain->chain_list;
//             }
//             return false;
//         }
//     }
// }

void process_instructions(int *list_number, int *instructions_number, ChainList **ptr_chain_list) {
    for (int i = 0; i < *instructions_number; i++) {
        char *instruction = read_input_word();
        char *word_parameter = NULL;
        int int_parameter = 0;

        if (strcmp(instruction, ADD) == 0) {
            word_parameter = read_input_word();
            execute_add(word_parameter, ptr_chain_list, list_number);
            printf("(%s, %p)\n", )
            free(word_parameter);
        }

        if (strcmp(instruction, GET) == 0) {
            read_int_parameter(&int_parameter);
            // Execute GET
        }

        if (strcmp(instruction, CHECK) == 0) {
            word_parameter = read_input_word();
            // Execute CHECK
            free(word_parameter);
        }

        if (strcmp(instruction, DEL) == 0) {
            word_parameter = read_input_word();
            // Execute DEL
            free(word_parameter);
        }

        free(instruction);
    }
}

ChainList *build_main_chain_list(int *list_number) {
    ChainList *chain_list = NULL;
    chain_list = calloc((*list_number), sizeof(ChainList));
    return chain_list;
}

int main(void) {

    int list_number, instructions_number;
    read_list_and_instructions_number(&list_number, &instructions_number);

    ChainList *chain_list = NULL;
    chain_list = build_main_chain_list(&list_number);

    process_instructions(&list_number, &instructions_number, &chain_list);
    free(chain_list);

    return 0;
}