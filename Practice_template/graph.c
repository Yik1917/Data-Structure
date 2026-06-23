#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define MAXNODE 500

//Node **nodes = (Node **)malloc(sizeof(Node *) * MAX_NODES);
//memset(nodes, 0, sizeof(Node *) * MAX_NODES);  作為事後初始化用

int cmp_int(const void *a, const void *b) {
    return *(int*)a - *(int*)b;   // 升冪排序
}

ListNode *genNode(int value, ListNode *next){
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->value = value;
    newNode->next = next;
    return newNode;
}
void insertAdjList(ListNode **adjList, int idx, int value){
    ListNode *newNode = genNode(value, adjList[idx]->next);
    adjList[idx]->next = newNode;
}
void DFS(ListNode **adjList, int idx, short ht[], ListNode **spanTreeAdjList){
    ht[idx] = 1;
    for (ListNode *ptr = adjList[idx]->next; ptr != NULL; ptr = ptr->next){
        if (ht[ptr->value] == 0){
            insertAdjList(spanTreeAdjList, idx, ptr->value);
            DFS(adjList, ptr->value, ht);
        }
    }
}
void BFS(ListNode **adjList, int idx, short ht[]){
    int queue[MAXNODE];
    int front = 0, rear = 0;
    queue[rear++] = idx;
    ht[idx] = 1;
    while (front < rear){
        int i = queue[front++];
        for (ListNode *ptr = adjList[i]->next; ptr != NULL; ptr = ptr->next){
            if (ht[ptr->value] == 0){
                ht[ptr->value] = 1;
                queue[rear++] = ptr->value;
            }
        }
    }
}
void DFS_ArticulationPoint(ListNode **adjList, int u, int parent) {
    // 1. 初始化
    dfn[u] = low[u] = ++timer;
    int children = 0; // 計算在 DFS Tree 中的孩子數量 (for Root判斷)

    for (Node *ptr = adjList[u]; ptr != NULL; ptr = ptr->next) {
        int v = ptr->label;

        if (v == parent) continue; // 略過剛過來的父節點 (無向圖必備)

        if (dfn[v]) {
            // [情況 A] v 已經訪問過 -> 這是一條 Back Edge
            // 代表 u 可以透過這條邊連到祖先 v
            // 更新 low[u]，看能不能變得更小
            low[u] = MIN(low[u], dfn[v]);
        } 
        else {
            // [情況 B] v 沒訪問過 -> 這是一條 Tree Edge
            children++;
            DFS_ArticulationPoint(adjList, v, u); // 遞迴下去

            // 回溯後，用孩子的 low 更新自己的 low
            // (孩子能到的最高祖先，我也能到)
            low[u] = MIN(low[u], low[v]);

            // [關鍵判斷]：非根節點的 AP 條件
            // 如果 parent != -1 (不是根) 且 孩子 v 爬不高 (low[v] >= dfn[u])
            if (parent != -1 && low[v] >= dfn[u]) {
                isAP[u] = 1;
            }
        }
    }

    // [根節點特判]
    // 如果是 DFS 的起點 (root)，且有兩個以上的 Tree Edge 孩子
    if (parent == -1 && children > 1) {
        isAP[u] = 1;
    }
}
long long Kruskal(Edge edges[], int edgeNum, int nodeNum){
    qsort(edges, edgeNum, sizeof(Edge), cmp_int);
    int *parents = (int*)calloc(nodeNum, sizeof(int));
    long long result = 0;
    for (int i = 0, cntEdge = 0; i < edgeNum; i++){
        int rootA = find(edges[i].from, parents);
        int rootB = find(edges[i].to, parents);
        if (rootA != rootB){
            result += edges[i].weight;
            union_set(rootA, rootB);
            if (++cntEdge == nodeNum-1) return result;
        }
    }
    return -1;
}
long long Prims(Node *node){
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
short isCyclic(Adj *adjList, Adj *adjList_R, int N){
    int *st = (int*)malloc(sizeof(int)*N), top = 0;
    for (int i = 0; i < N; i++){
        if (adjList[i].quantity == 0){
            for (Node *ptr = adjList_R[i].next; ptr; ptr = ptr->next){
                adjList[ptr->label].quantity--;
                if (adjList[ptr->label].quantity <= 0) st[top++] = ptr->label;
            }
        }
    }
    while (top > 0){
        int i = st[--top];
        for (Node *ptr = adjList_R[i].next; ptr; ptr = ptr->next){
            adjList[ptr->label].quantity--;
            if (adjList[ptr->label].quantity == 0) st[top++] = ptr->label;
        }
    }
    for (int i = 0; i < N; i++){
        if (adjList[i].quantity > 0) return 1;
    }
    free(st);
    return 0;
}