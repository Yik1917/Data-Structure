#include <stdio.h>
#include <stdlib.h>
#include "mst.h"


void swap(Edge **x, Edge **y){
    Edge *temp = *x;
    *x = *y;
    *y = temp;
}
void insertMinHeap(Edge **minHeap, Edge *node, int cntHeap){
    if (!node) return;
    minHeap[++cntHeap] = node;
    int i = cntHeap;
    while (i > 1){
        int parentIdx = (i%2)? (i-1)/2: i/2;
        if (minHeap[parentIdx]->w > minHeap[i]->w){
            swap(minHeap+parentIdx, minHeap+i);
            i = parentIdx;
        }else return;
    }
}
Edge *deleteMinHeap(Edge **minHeap, int cntHeap){
    if (cntHeap <= 0) return NULL;
    Edge *result = minHeap[1];
    minHeap[1] = minHeap[cntHeap--];
    int i = 1;
    while (i*2 <= cntHeap){
        int minIdx = i*2;
        if (i*2+1 <= cntHeap && minHeap[i*2+1]->w < minHeap[i*2]->w) minIdx = i*2+1;
        if (minHeap[i]->w > minHeap[minIdx]->w){
            swap(minHeap+i, minHeap+minIdx);
            i = minIdx;
        }else break;
    }
    return result;
}
void generate_mst(Node *node){ //Prim's Method
    Edge **minHeap = (Edge**)malloc(sizeof(Edge*)*2500000);
    int cntHeap = 0;
    for (int i = 0; i < node->edge_count; i++){
        insertMinHeap(minHeap, node->edges[i], cntHeap);
        cntHeap++;
    }

    short *htNode = (short*)calloc(100000, sizeof(short));
    htNode[node->id] = 1;
    while (cntHeap > 0){
        Edge *minEdge = deleteMinHeap(minHeap, cntHeap);
        cntHeap--;
        if (htNode[minEdge->u->id] && htNode[minEdge->v->id]) continue;
        minEdge->keep = 1;
        Node *adjNode = (htNode[minEdge->u->id])? minEdge->v: minEdge->u;
        htNode[minEdge->u->id] = 1;
        htNode[minEdge->v->id] = 1;
        for (int i = 0; i < adjNode->edge_count; i++){
            insertMinHeap(minHeap, adjNode->edges[i], cntHeap);
            cntHeap++;
        }
    }
    free(htNode); free(minHeap);
}
