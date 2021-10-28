void bubblesort(char *item, int count) {
    register int a, b;
    register char t;

    for (a = 1; a < count; ++a) {
        for (b = count-1; b >= a; --b) {
            if (item[b-1] > item[b]) {
                t = item[b-1];
                item[b-1] = item[b];
                item[b] = t;
            }
        }
    }
}

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void bubblesort(char *item, int count);

void main(void) {
    char s[80];

    printf("Digite uma string: ");
    scanf("%s", s);
    bubblesort(s, strlen(s));
    printf("String ordenada: %s\n", s);
}