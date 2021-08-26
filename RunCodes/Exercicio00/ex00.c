#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
	int numbers[100];
	scanf("%d", &numbers[0]);
	char buffer = getchar();
	
	int total_numbers = 1;
	while (buffer != EOF){
		scanf("%d", &numbers[total_numbers]);
		buffer = getchar();
		total_numbers++;
	}

	int numbers_frequency[total_numbers*2]; 
      
	for (int j = 0; j < total_numbers; j++) {

		int counter = 0;
		for (int cursor = 0; cursor < total_numbers; cursor++) {
			if (numbers[j] == numbers[cursor]) {
				counter++;	
			}
		}
      	
		numbers_frequency[(j*2)] = numbers[j];
		numbers_frequency[(j*2)+1] = counter;

		int repeated = 0;
		for (int cursor = 0; cursor < j; cursor++) {
			if (numbers_frequency[(cursor*2)] == numbers_frequency[(j*2)]) {
				repeated = 1;
			}
		}
      	
		if (repeated == 0) {
			printf("%d (%d)\n", numbers_frequency[(j*2)], numbers_frequency[(j*2)+1]);
	
		}
	}

	return 0;
}

