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
    // char wav_filename[100];
    // scanf("%s ", wav_filename);

    char wav_filename[50] = "cat.wav";   
    FILE* wav_file = fopen(wav_filename, "rb");
    if (wav_file == NULL) {
        perror("Error opening file!\n");
        exit(-1);
    }

    return wav_file;
}

void read_compression_coeff_input(int* compression_coeff) {
    // scanf("%d ", compression_coeff);
    *compression_coeff = 100;
}

unsigned char* store_wav_binary_content(FILE* fp, int* content_length) {
    unsigned char buf4[4];

    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    int dataSize = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;

    unsigned char* data = malloc(sizeof(*data) * (dataSize));
    
    int i = 0;
    while (i < dataSize) {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);
    *content_length = dataSize;
    return data;
}


int main (void) {
    FILE* wav_file = read_wav_filename();

    int compression_coeff = 0;
    read_compression_coeff_input(&compression_coeff);

    int content_length = 0;
    unsigned char* wav_file_content = NULL;
    wav_file_content = store_wav_binary_content(wav_file, &content_length);

    for(int i = 0; i<10; i++) printf("%hhx ", wav_file_content[i]);
    printf("\n");

    free(wav_file_content);

    return 0;
}

