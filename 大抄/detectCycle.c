#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int from;
    struct node *next;
} Node;
void insertAdjList(Node **adjV, int from){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->from = from;
    newNode->next = *adjV;
    *adjV = newNode;
}
void detectCycle(Node **adjList_in, int outdegress[], int i){
    for (Node *ptr = adjList_in[i]; ptr; ptr = ptr->next){
        outdegress[ptr->from]--;
        if (outdegress[ptr->from] == 0){
            detectCycle(adjList_in, outdegress, ptr->from);
        }
    }
}
int main(){
    int n; scanf("%d", &n);
    int from, to;
    Node **adjList_in = (Node**)calloc(n+1, sizeof(Node*));
    int *outdegrees = (int*)calloc(n+1, sizeof(int));
    while (scanf("%d%d", &from, &to) != EOF){
        if (!(0 < from && from <= n && 0 < to && to <= n)) continue;
        insertAdjList(adjList_in+to, from);
        outdegrees[from]++;
    }
    for (int i = 1; i <= n; i++){
        if (outdegrees[i] == 0){
            detectCycle(adjList_in, outdegrees, i);
        }
    }
    short check = 0;
    for (int i = 1; i <= n; i++){
        if (outdegrees[i] > 0){
            check = 1;
            break;
        }
    }
    if (check) printf("There is a cycle\n");
    else printf("There is no cycle\n");
    return 0;
}