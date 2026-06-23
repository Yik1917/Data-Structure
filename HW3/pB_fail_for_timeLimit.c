#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int label;
    struct Node *next;
} Node;
Node *genNode(int label, Node *next){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->label = label;
    newNode->next = next;
    return newNode;
}
void insertAdjList(Node **adjList, Node *newNode, int from){ //insert at the head
    if (!newNode){
        printf("Access NULL!!\n"); return;
    }
    newNode->next = adjList[from];
    adjList[from] = newNode;
}
short DFS(short *ht, Node **adjList, int label){
    for (Node *ptr = adjList[label]; ptr; ptr = ptr->next){
        if (ht[ptr->label]) return 1;
        else{
            ht[ptr->label] = 1;
            short check = DFS(ht, adjList, ptr->label);
            if (check) return 1;
        }
    }
    ht[label] = 0;
    return 0;
}
short isCyclic(Node **adjList, int N){
    short *ht = (short*)calloc(N, sizeof(short));
    for (int i = 0; i < N; i++){
        ht[i] = 1;
        if (DFS(ht, adjList, i)) return 1;
        ht[i] = 0;
    }
    return 0;
}
int main(){
    int N, D; scanf("%d%d", &N, &D);
    Node **adjList = (Node**)calloc(N, sizeof(Node*));
    for (int i = 0; i < D; i++){
        int u, v; scanf("%d%d", &u, &v);
        Node *newNode = genNode(v, NULL);
        insertAdjList(adjList, newNode, u);
    }
    if (isCyclic(adjList, N)) printf("1\n");
    else printf("0\n");
    return 0;
}