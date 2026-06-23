#ifndef LEFTIST_H
#define LEFTIST_H

typedef struct leftistNode{
    int value;
    struct leftistNode *left, *right;
    int shortest;
} LefNode;

LefNode *insertLeftist(LefNode *root, int value);
LefNode *deleteMinLeftist(LefNode *root);
LefNode *meldLeftist(LefNode *rootA, LefNode *rootB);

#endif