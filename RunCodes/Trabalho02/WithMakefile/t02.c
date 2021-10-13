/* HEADER
Autor:      Jorge Augusto Salgado Salhani --- no USP: 8927418 ---
Disciplina: SCC0201 Introducao a Ciencia da Computacao - 2o sem 2021
Titulo:     Trabalho 02: Tratamento de audio
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>

FILE* read_wav_filename(void) {
    char wav_filename[100];
    scanf("%s ", wav_filename);

    // char wav_filename[50] = "bubble.wav";   // TEST
    FILE* wav_file = fopen(wav_filename, "rb");
    if (wav_file == NULL) {
        perror("Error opening file!\n");
        exit(-1);
    }

    return wav_file;
}

void read_compression_coeff_input(int* compression_coeff) {
    scanf("%d ", compression_coeff);
    // *compression_coeff = 100; // TEST
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

double complex* discrete_fourier_transform_coefficients(unsigned char** pointer_to_wav_content, int* content_length) {
    unsigned char* wav_content = *pointer_to_wav_content;
    int length = *content_length;

    double complex* fourier_coeffs = NULL;
    fourier_coeffs = calloc(length, sizeof(double complex));

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            fourier_coeffs[i] += wav_content[j] * cexp((-2.0 * M_PI * (((i+1) * j * 1.0) / (length * 1.0))) * _Complex_I);
        }
        // printf("%.1lf + %.1lfi: ", creal(fourier_coeffs[i]), cimag(fourier_coeffs[i]));
    }
    return fourier_coeffs;
}

void count_non_positive_vector_components(int* non_positive_vector_components, double complex complex_vector) {
    int local_count = *non_positive_vector_components;
    if (creal(complex_vector) <= 0 && cimag(complex_vector) <= 0) {
        *non_positive_vector_components = local_count + 1;
    }
}

double* get_magnitudes(double complex** pointer_to_complex_vector, int* content_length) {
    double complex* complex_vector = *pointer_to_complex_vector;
    double* vector_magnitudes = NULL;
    vector_magnitudes = malloc(sizeof(double) * (*content_length));
    
    double real_sqr, imag_sqr, vector_magnitude;

    int non_positive_vector_components = 0;
    
    for (int i = 0; i < *content_length; i++) {
        real_sqr = (creal(complex_vector[i])) * (creal(complex_vector[i]));
        imag_sqr = (cimag(complex_vector[i])) * (cimag(complex_vector[i]));
        vector_magnitudes[i] = sqrt(real_sqr + imag_sqr);

        count_non_positive_vector_components(&non_positive_vector_components, complex_vector[i]);
    }

    printf("%d\n", non_positive_vector_components);

    return vector_magnitudes;
}

void map_zero_position(int* sorted_positions, int new_position){
    sorted_positions[0] = new_position-1;
}

void shift_smaller_positions_one_unit(int* sorted_positions, int number_positions_mapped, int new_position, bool first_fixed_point_found) {
    int i = 1;
    if (first_fixed_point_found) i = 0;

    while (i < number_positions_mapped) {
        int cursor_content = sorted_positions[i]; 
        if (sorted_positions[i] >= new_position) {
            sorted_positions[i] = sorted_positions[i] + 1;
        }
        i++;
    }

    i = 1;
    if (first_fixed_point_found) i = 0;
}

int* sort_magnitudes_and_map_original_positions(double* vector_magnitudes, int content_length) {
    
	int* sorted_positions = NULL;
    sorted_positions = malloc(sizeof(int) * content_length);

    int previous_cursor = 0;
	double cursor_content = 0.0;

    bool first_fixed_point_found = false;

    for (int i = 1; i < content_length; i++) {							
        cursor_content = vector_magnitudes[i];
        previous_cursor = i - 1;									
        while (previous_cursor >= 0 && vector_magnitudes[previous_cursor] > cursor_content) {			
            vector_magnitudes[previous_cursor + 1] = vector_magnitudes[previous_cursor]; 	
            previous_cursor = previous_cursor - 1;					
        }

        int new_position = previous_cursor + 1;										
        vector_magnitudes[new_position] = cursor_content;
        sorted_positions[i] = new_position;

        if (!first_fixed_point_found && i == new_position) {
            map_zero_position(sorted_positions, new_position);
            first_fixed_point_found = true;
        }

        shift_smaller_positions_one_unit(sorted_positions, i, sorted_positions[i], first_fixed_point_found);
    }

    return sorted_positions;
}

void zero_values_beyond_compression_coeff(double* vector_magnitudes, int compression_coeff, int content_length) {
    for (int i = 0; i < (content_length - compression_coeff); i++) {
        vector_magnitudes[i] = 0.0;
    }
}

double complex* return_magnitudes_to_original_position(double complex* fourier_coefficients, double* vector_magnitudes, int* sorted_positions, int content_length, int compression_coeff) {
    double complex* new_fourier_coefficients = NULL;
    new_fourier_coefficients = malloc(sizeof(double complex) * compression_coeff);
    int new_vector_position = 0;
    for (int i = content_length-1; i >= 0; i--) {
        int original_position = sorted_positions[i];
        if (vector_magnitudes[original_position] > 0.0) {
            new_fourier_coefficients[new_vector_position] = fourier_coefficients[original_position];
            new_vector_position++;
        }
    }

    return new_fourier_coefficients;
}

double complex* discrete_inverse_fourier_transform_coefficients(double complex* new_vector_magnitudes, int compression_coeff) {
    double complex* fourier_coeffs = NULL;
    fourier_coeffs = calloc(compression_coeff, sizeof(double complex));

    for (int i = 0; i < compression_coeff; i++) {
        for (int j = 0; j < compression_coeff; j++) {
            fourier_coeffs[i] += new_vector_magnitudes[j] * cexp((2.0 * M_PI * (((i+1) * j * 1.0) / (compression_coeff * 1.0))) * _Complex_I);
        }
        fourier_coeffs[i] *= (1/(double)(compression_coeff));
    }
    return fourier_coeffs;
} 

int main (void) {
    FILE* wav_file = read_wav_filename();

    int compression_coeff = 0;
    read_compression_coeff_input(&compression_coeff);

    int content_length = 0;
    unsigned char* wav_content = NULL;
    wav_content = store_wav_binary_content(wav_file, &content_length);

    // content_length = 30; // FAST TEST
    // compression_coeff = 10;

    printf("%d\n", content_length);

    double complex* fourier_coefficients = NULL;
    fourier_coefficients = discrete_fourier_transform_coefficients(&wav_content, &content_length);

    double* vector_magnitudes = NULL;
    vector_magnitudes = get_magnitudes(&fourier_coefficients, &content_length);

    // printf("ORIGINAL:\n");
    // for (int i = 0; i < content_length; i++) printf("%lf   ", vector_magnitudes[i]);
    // printf("\n\n");

    int* sorted_positions = NULL;
    sorted_positions = sort_magnitudes_and_map_original_positions(vector_magnitudes, content_length);

    // printf("SORTED:\n");
    // for (int i = 0; i < content_length; i++) printf("%lf   ", vector_magnitudes[i]);
    // printf("\n\n");

    // printf("TRANSITIONS:\n");
    // for (int i = 0; i < content_length; i++) printf("%d   ", sorted_positions[i]);
    // printf("\n\n");

    zero_values_beyond_compression_coeff(vector_magnitudes, compression_coeff, content_length);
    
    // printf("ZEROED:\n");
    // for (int i = 0; i < content_length; i++) printf("%lf   ", vector_magnitudes[i]);
    // printf("\n\n");

    double complex* new_fourier_coefficients = NULL;
    new_fourier_coefficients = return_magnitudes_to_original_position(fourier_coefficients, vector_magnitudes, sorted_positions, content_length, compression_coeff);



    // printf("ROLLBACK:\n");
    // for (int i = 0; i < compression_coeff; i++) printf("%.2lf + %.2lfi\n", creal(new_fourier_coefficients[i]), cimag(new_fourier_coefficients[i]));
    // printf("\n\n");

    double complex* inverse_fourier_vector = NULL;
    inverse_fourier_vector = discrete_inverse_fourier_transform_coefficients(new_fourier_coefficients, compression_coeff);
    
    // printf("IFT:\n");
    // for (int i = 0; i < compression_coeff; i++) printf("%.2lf + %.2lfi\n", creal(inverse_fourier_vector[i]), cimag(inverse_fourier_vector[i]));
    // printf("\n\n");

    for (int i = content_length-1; i >= (content_length - compression_coeff); i--) {
      printf("%d\n", (int)vector_magnitudes[i]);  
    }

    free(inverse_fourier_vector);
    free(new_fourier_coefficients);
    free(sorted_positions);
    free(vector_magnitudes);
    free(fourier_coefficients);

    free(wav_content);

    return 0;
}

