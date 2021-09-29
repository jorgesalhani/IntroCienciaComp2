/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Trabalho 02: Tratamento de audio
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>

FILE* read_wav_filename(void) {
    char wav_filename[100];
    scanf("%s ", wav_filename);

    FILE* wav_file = fopen(wav_filename, "rb");
    if (wav_file == NULL) {
        perror("Error opening file!\n");
        exit(-1);
    }

    return wav_file;
}

void read_compression_coeff_input(int* compression_coeff) {
    scanf("%d ", compression_coeff);
}

unsigned char* store_wav_binary_content(FILE* wav_file, long int* content_length) {
    fseek(wav_file, 0, SEEK_END);
    long int file_size = ftell(wav_file);
    *content_length = file_size;

    unsigned char* wav_content = calloc(file_size, sizeof(unsigned char));

    int i = 1;
    while (i < file_size) {
        fread(&wav_content[i], sizeof(unsigned char), 1, wav_file);
        i++;
    }

    fclose(wav_file);

    return wav_content;
}


int main (void) {

    FILE* wav_file = read_wav_filename();

    int compression_coeff = 0;
    read_compression_coeff_input(&compression_coeff);

    long int content_length = 0;
    unsigned char* wav_file_content = NULL;
    wav_file_content = store_wav_binary_content(wav_file, &content_length);

    for(int i = 0; i<10; i++) printf("%u ", wav_file_content[i]);
    printf("\n");
    // printf("%ld\n", content_length);
    // printf("%u\n", wav_file_content);



    free(wav_file_content);

    return 0;
}

