void shellsort(char *item, int count) {
    register int i, j, gap, k;
    char x, a[5];

    a[0] = 9;
    a[1] = 5;
    a[2] = 3;
    a[3] = 2;
    a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; i++) {
            x = item[i];
            for (j = i-gap; x < item[j] && j >= 0; j=j-gap) {
                item[j+gap] = item[j];
            }
            item[j+gap] = x;
        }
    }
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void shellsort(char *item, int count);

void main(void) {
    char s[80];

    printf("Digite uma string: ");
    scanf("%s", s);
    shellsort(s, strlen(s));
    printf("String ordenada: %s\n", s);
}