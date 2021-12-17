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

void read_int_parameter(int *int_parameter) {
    scanf("%d ", int_parameter);
}

void process_instructions(int *list_number, int *instructions_number) {
    for (int i = 0; i < *instructions_number; i++) {
        char *instruction = read_input_word();
        char *word_parameter = NULL;
        int int_parameter = 0;

        printf("%s: ", instruction);


        if (strcmp(instruction, ADD) == 0) {
            word_parameter = read_input_word();
            // Execute ADD
            printf("%s\n", word_parameter);
            free(word_parameter);
        }

        if (strcmp(instruction, GET) == 0) {
            read_int_parameter(&int_parameter);
            printf("%d\n", int_parameter);
            // Execute GET
        }

        if (strcmp(instruction, CHECK) == 0) {
            word_parameter = read_input_word();
            // Execute CHECK
            printf("%s\n", word_parameter);
            free(word_parameter);
        }

        if (strcmp(instruction, DEL) == 0) {
            word_parameter = read_input_word();
            printf("%s\n", word_parameter);
            // Execute DEL
            free(word_parameter);
        }

        free(instruction);
    }
}

int main(void) {

    int list_number, instructions_number;
    read_list_and_instructions_number(&list_number, &instructions_number);

    process_instructions(&list_number, &instructions_number);

    return 0;
}