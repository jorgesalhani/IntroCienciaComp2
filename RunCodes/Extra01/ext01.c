#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct tree {
    char info;
    struct tree *left;
    struct tree *right;
};

struct tree *root;
struct tree *stree(struct tree *root, struct tree *r, char info);
void print_tree(struct tree *root, int l);

void main(void) {
    char s[80] = "acbad\0";
    root = NULL;

    int c = 0;
    do {
        // printf("Insira uma letra: ");
        // scanf("%s", s);
        printf("%c\n", s[c]);
        if (!root) {
            root = stree(root, root, *(s+c));
        } else {
            stree(root, root, *(s+c));
        }
        c++;
    } while (c < strlen(s));

    print_tree(root, NULL);
}

struct tree *stree(struct tree *root, struct tree *r, char info) {
    if (!r) {
        r = (struct tree *) malloc(sizeof(struct tree));
        if (!r) {
            printf("Sem memoria\n");
            exit(0);
        }
        r -> left = NULL;
        r -> right = NULL;
        r -> info = info;

        if (!root) {
            return r;
        }

        if (info < root -> info) {
            root -> left = r;
        } else {
            root -> right = r;
        }
        return r;
    }

    if (info < r -> info) {
        stree(r, r -> left, info);
    } else {
        stree(r, r -> right, info);
    }
}

void print_tree(struct tree *r, int l) {
    int i;
    if (!r) return;

    print_tree(r->right, l+1);
    for (i = 0; i < 1; ++i) {
        printf("  ");
    }
    printf("%c\n", r -> info);
    print_tree(r -> left, l+1);

    free(r);
}