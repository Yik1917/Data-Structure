#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct node{
    int to;
    struct node *next;
} Node;
void insertAdjList(Node **adjV, int to){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->to = to;
    newNode->next = *adjV;
    *adjV = newNode;
}
void DFS_genSpanTree(Node **adjList, int u, int p, int D[], int low[], Node **spanTreeAdjList, short isAP[]){
    static int timer = 0;
    D[u] = low[u] = ++timer;
    int childCount = 0;
    for (Node *ptr = adjList[u]; ptr; ptr = ptr->next){
        int v = ptr->to;
        if (v == p) continue;
        if (D[v]){
            low[u] = MIN(low[u], D[v]);
        }else{
            childCount++;
            insertAdjList(spanTreeAdjList+u, v);
            DFS_genSpanTree(adjList, v, u, D, low, spanTreeAdjList, isAP);
            low[u] = MIN(low[u], low[v]);
            if (p != -1 && low[v] >= D[u]) isAP[u] = 1;
        }
    }
    if (p == -1 && childCount > 1) isAP[u] = 1;
}
int main(){
    int n; scanf("%d", &n);
    int from, to;
    Node **adjList = (Node**)calloc(n+1, sizeof(Node*));
    while (scanf("%d%d", &from, &to) != EOF){
        if (!(0 < from && from <= n && 0 < to && to <= n)) continue;
        insertAdjList(adjList+from, to);
        insertAdjList(adjList+to, from);
    }
    Node **spanTreeAdjList = (Node**)calloc(n+1, sizeof(Node*));
    short *ht = calloc(n+1, sizeof(short));
    int *D = calloc(n+1, sizeof(int));
    int *low = calloc(n+1, sizeof(int));
    short *isAP = calloc(n+1, sizeof(short));
    DFS_genSpanTree(adjList, 1, -1, D, low, spanTreeAdjList, isAP);
    for (int i = 1; i <= n; i++){
        if (isAP[i]) printf("%d ", i);
    }
    printf("\n");
    return 0;
}