#ifndef GRAPH_H
#define GRAPH_H

typedef struct listNode{
    int value;
    struct listNode *next;
} ListNode;
typedef struct{
    int weight;
    int from, to;
} Edge;

#endif