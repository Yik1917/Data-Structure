#ifndef AVL_H
#define AVL_H

typedef struct node{
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
    int height;
} Node;

#endif