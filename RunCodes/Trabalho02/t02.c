/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Trabalho 02: Tratamento de audio
*/

#include <stdlib.h>
#include <stdio.h>

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


int main (void) {

    FILE* wav_file = read_wav_filename();

    int compression_coeff = 0;
    read_compression_coeff_input(&compression_coeff);
    
    printf("%d\n", compression_coeff);
    fclose(wav_file);

    return 0;
}

