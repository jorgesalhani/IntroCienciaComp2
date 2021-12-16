#include <stdio.h>
#include <stdlib.h>

void read_list_and_instructions_number(int *list_number, int *instructions_number) {
    scanf("%d ", list_number);
    scanf("%d ", instructions_number);
}

int main(void) {

    int list_number, instructions_number;
    read_list_and_instructions_number(&list_number, &instructions_number);

    printf("%d %d\n", list_number, instructions_number);

    return 0;
}