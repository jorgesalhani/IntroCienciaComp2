/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Trabalho 04: Hash Table
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void execute_add(char *word, ChainList **ptr_chain_list, int *list_number) {
    int word_position = calculate_hash_position(word, list_number);
    printf("%d\n", word_position);
}

void execute_get() {

}

void execute_check() {

}

void execute_del() {

}

void process_instructions(int *list_number, int *instructions_number, ChainList **ptr_chain_list) {
    for (int i = 0; i < *instructions_number; i++) {
        char *instruction = read_input_word();
        char *word_parameter = NULL;
        int int_parameter = 0;

        if (strcmp(instruction, ADD) == 0) {
            word_parameter = read_input_word();
            execute_add(word_parameter, ptr_chain_list, list_number);
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
    chain_list = malloc(sizeof(ChainList)*(*list_number));
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