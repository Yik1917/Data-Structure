#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int label;
    struct Node *next;
} Node;
typedef struct Adj{
    int quantity;
    struct Node *next;
} Adj;
Node *genNode(int label, Node *next){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->label = label;
    newNode->next = next;
    return newNode;
}
void insertAdjList(Adj *adjList, Node *newNode, int from){ //insert at the head
    if (!newNode){
        printf("Access NULL!!\n"); return;
    }
    newNode->next = adjList[from].next;
    adjList[from].next = newNode;
    adjList[from].quantity++;
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
int main(){
    int N, D; scanf("%d%d", &N, &D);
    Adj *adjList = (Adj*)calloc(N, sizeof(Adj));
    Adj *adjList_R = (Adj*)calloc(N, sizeof(Adj));
    for (int i = 0; i < D; i++){
        int u, v; scanf("%d%d", &u, &v);
        Node *newNode1 = genNode(v, NULL);
        insertAdjList(adjList, newNode1, u);
        Node *newNode2 = genNode(u, NULL);
        insertAdjList(adjList_R, newNode2, v);
    }
    printf("%d\n", isCyclic(adjList, adjList_R, N));
    return 0;
}