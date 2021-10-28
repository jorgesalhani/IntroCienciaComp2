void selectionsort(char *item, int count) {
    register int a, b, c;
    int exchange;
    char t;

    for (a = 0; a < count-1; ++a) {
        exchange = 0;
        c = a;
        t = item[a];

        for (b = a+1; b < count ; ++b) {
            if (item[b] < t) {
                c = b;
                t = item[b];
                exchange = 1;
            }
        }

        if (exchange) {
            item[c] = item[a];
            item[a] = t;
        }
    }
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void selectionsort(char *item, int count);

void main(void) {
    char s[80];

    printf("Digite uma string: ");
    scanf("%s", s);
    selectionsort(s, strlen(s));
    printf("String ordenada: %s\n", s);
}