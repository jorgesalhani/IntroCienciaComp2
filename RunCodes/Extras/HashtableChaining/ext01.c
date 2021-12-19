#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 31
#define h(x) (x % m)

typedef struct Node {
    int val;
    struct Node *next;
} Node;

Node *fill_table(Node *table, int table_range, int number);
Node *insert(Node *table, int hash_index, int val);
Node *del(Node *table, int table_range, int val);
void print_table(Node *table, int table_range);
void search_table(Node *table, int table_range, int val);

int main(void) {
    Node *table;
    int n, i, j, choice, search;
    int hash_num, val;

    table = (Node*)malloc(sizeof(Node)*(N));
    for (i = 0; i < N; i++) {
        table[i].next = NULL;
    }

    printf("--h(x) = xmod%d--\n", N);
    printf("\n\n");

    while (1) {
        printf("1. Insert random numbers\n");
        printf("2. Delete a number\n");
        printf("3. Search a number\n");
        printf("4. Show Hash Table\n");
        printf("0. Exit program\n");
        printf("\n-------\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0: return 0;
            case 1:
                printf("Lot to insert: ");
                scanf("%d", &n);
                table = fill_table(table, N, n);
                printf("Filled HashTable with %d random values\n", n);
                printf("\n-------\n");
                break;
            case 2:
                printf("Give a number: ");
                scanf("%d", &search);
                table = del(table, N, search);
                printf("\n-------\n");
                break;
            case 3:
                printf("Give a number: ");
                scanf("%d", &search);
                search_table(table, N, search);
                printf("\n-------\n");
                break;
            case 4:
                printf("-HASHTABLE-\n\n");
                print_table(table, N);
                printf("\n-------\n");
                break;
        }
    }
    return 0;
}

Node *fill_table(Node *table, int table_range, int number) {
    int i, num;
    for (i = 0; i < number; i++) {
        num = rand()%10000;
        table = insert(table, num %table_range, num);
    }
    return table;
}

void print_table(Node *table, int table_range) {
    int i;
    Node* cur;
    for (i = 0; i < table_range; i++) {
        if (table[i].next == NULL) {
            printf("Table[%d] is empty\n", i);
            continue;
        }

        cur = table[i].next;
        printf("Table[%d]", i);
        while (cur!= NULL) {
            printf("->%d", (*cur).val);
            cur = (*cur).next;
        }
        printf("\n");
    }
}

Node *insert(Node *table, int hash_index, int val) {
    Node *nn, *cur;

    nn = (Node*)malloc(sizeof(Node));
    nn->val = val;
    nn->next = NULL;

    if (table[hash_index].next == NULL) {
        table[hash_index].next = nn;
        return table;
    }

    cur = table[hash_index].next;
    while(cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = nn;
    return table;
}

void search_table(Node *table, int table_range, int val) {
    int index = val % table_range;
    Node *cur;

    if (table[index].next == NULL) {
        printf("Value %d not found cause Table[%d] is empty.\n", val, index);
    }

    cur = table[index].next;
    while (cur != NULL) {
        if (cur->val == val) {
            printf("Value %d was found.\n", val);
            return;
        }

        cur = cur->next;
    }
    printf("Value %d not found in HashTable!\n", val);
}

Node *del(Node *table, int table_range, int val) {
    int index = val % table_range;
    Node *prev;

    if (table[index].next == NULL) {
        printf("Value %d not found cause Table[%d] is empty.\n", val, index);
        return table;
    }

    if (table[index].next->val == val) {
        printf("Value %d was found at table[%d] and Deleted!\n", val,index);
        table[index].next = table[index].next->next;
        return table;
    }

    prev = table[index].next;
    while (prev->next != NULL) {
        if (prev->next->val == val) {
            prev->next = prev->next->next;
            printf("Value %d was found at table[%d] and Deleted!\n", val,index);
            return table;
        }

        prev = prev->next;
    }
    printf("Value %d was not found in Hashtable!\n", val);
    return table;
}