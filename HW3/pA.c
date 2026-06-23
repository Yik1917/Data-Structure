#include <stdio.h>
#include <stdlib.h>
#define MAX_N 200000

typedef struct Node{
    int label;
    struct Node *next;
}Node;
typedef struct Edge{
    int from, to;
} Edge;
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
void deleteAdjList(Node **adjList, int label, int from){
    Node *head = adjList[from];
    if (head->label == label){
        adjList[from] = head->next;
        free(head); return;
    }
    for (Node *prev = head, *ptr = head->next; ptr; ptr = ptr->next){
        if (ptr->label == label){
            prev->next = ptr->next;
            free(ptr); return;
        }
        prev = ptr;
    }
    printf("Edge not found!!\n");
}
void DFS(Node **adjList, int label, int n, short *ht, int *parents, int i){
    for (Node *ptr = adjList[label]; ptr; ptr = ptr->next){
        if (1 <= ptr->label && ptr->label <= n){
            if (ht[ptr->label] != 1){
                ht[ptr->label] = 1;
                parents[ptr->label] = i;
                DFS(adjList, ptr->label, n, ht, parents, i);
            }
        }else{
            printf("Access out of adjList!!\n"); return;
        }
    }
}
int findRoot(int *parents, int childIdx){
    int prev = childIdx, current = parents[childIdx];
    while (current != -1){
        prev = current;
        current = parents[prev];
    }
    return prev;
}

int main(){
    int n, m, q; scanf("%d%d%d", &n, &m, &q);
    Node **adjList = calloc(n+1, sizeof(Node*));
    Edge *edges = (Edge*)malloc(sizeof(Edge)*(m+1));
    for (int i = 1; i <= m; i++){
        int u, v; scanf("%d%d", &u, &v);
        edges[i] = (Edge){u, v};
        insertAdjList(adjList, genNode(v, NULL), u);
        insertAdjList(adjList, genNode(u, NULL), v);
    }

    int *inputs = (int*)malloc(sizeof(int)*(q+1));
    for (int i = 1; i <= q; i++){
        int input; scanf("%d", &input);
        Edge edge = edges[input];
        deleteAdjList(adjList, edge.to, edge.from);
        deleteAdjList(adjList, edge.from, edge.to);
        inputs[i] = input;
    }
    short *ht = (short*)calloc(n+1, sizeof(short));
    int *parents = (int*)calloc(n+1, sizeof(int));
    int cnt = 0;
    for (int i = 1; i <= n; i++){
        if (!ht[i]){
            ht[i] = 1;
            parents[i] = -1;
            DFS(adjList, i, n, ht, parents, i);
            cnt++;
        }
    }
    
    int *cumulativeResults = (int*)malloc(sizeof(int)*(q+1));
    cumulativeResults[0] = cnt;
    for (int i = q; i >= 1; i--){
        Edge edge = edges[inputs[i]];
        int rootA = findRoot(parents, edge.from), rootB = findRoot(parents, edge.to);
        if (rootA != rootB){
            parents[rootA] = rootB;
            cnt--;
        }
        cumulativeResults[q-i+1] = cnt;
    }
    for (int i = q; i >= 0; i--){
        printf("%d\n", cumulativeResults[i]);
    }

    return 0;
}