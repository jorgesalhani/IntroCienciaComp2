#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Tree {
    int info;
    struct Tree *up_left;
    struct Tree *up_right;
    struct Tree *down_left;
    struct Tree *down_right;
};

struct Point {
    int x;
    int y;
};

struct Node {
    int x0;
    int y0;
    int height;
    int width;
    struct Point* points;
};

struct Point* contains(int x0, int y0, int w, int h, struct Point* points) {
    struct Point* pts = (struct Point*) malloc(sizeof(struct Point));
    for (int i = 0; i < )
}

void recursive_subdivide(struct Node* node) {
    if (!node->points) {
        return;
    }

    int w_ = node->width;
    int h_ = node->height;

    struct Point* p = contains(node->x0, node->y0, w_, h_, node->points);
}

int main(void) {
    
    
    return 0;
}