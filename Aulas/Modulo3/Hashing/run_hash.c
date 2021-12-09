#include <stdio.h>
#include <stdlib.h>
#include <hashing.h>

int main(int argc, char *argv[]) {
    int m = atoi(argv[1]);

    int* t = create_hash_table(m);
    print_table(t, m);

    int key;
    int n_ins = 10;
    print("%d insercoes\n", n_ins);

    for (int j = 0; j < n_ins; j++) {
        scanf("%d ", &key);
        insert(t, key, m);
        print_table(t, m);
    }

    int n_rem = 5;
    printf("%d remocoes\n", n_rem);
    for (int j = 0; j < n_rem; j++) {
        scanf("%d ", &key);
        remove_hash(t, key, m);
        print_table(t, m);
    }

    int n_bus = 2;
    printf("%d buscas\n", n_bus);
    for (int j = 0; j < n_bus; j++) {
        scanf("%d ", &key);
        int p = search(t, key, m);
        printf("-> %d\n", p);
    }

    int *t2 = create_hash_table(m);
    for (int i = 0; i < m; i++) {
        if (t[i] >= 0) insert(t2, t[i], m);
    }
    print_table(t2, m);

    destroy_hash_table(&t);

    return 0;
}