#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

typedef struct link{
    struct link *prev, *next;
} Link;
typedef struct fiboNode{
    int key;
    Link link;
    struct fiboNode *minChild;
} FiboNode;
typedef struct dblFiboLink{
    FiboNode *node;
    Link link;
    int dump;
} DblFiboLink;

void insertCirLinkst(Link *minLink, Link *newLink)
void mergeFibo(FiboNode *fiboMin, DblFiboLink *degrees[]);
FiboNode *insertFibo(FiboNode *fiboMin, FiboNode *newNode, DblFiboLink *degrees[]);

#endif