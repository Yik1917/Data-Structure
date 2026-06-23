#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int from, to;
    int weight;
    struct node *next;
} Node;
Node *genNode(int from, int to, int weight, Node *next){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->from = from; newNode->to = to; newNode->weight = weight;
    newNode->next = next;
    return newNode;
}
Node *insertAdjList(Node **adjV, int from, int to, int weight){
    Node *newNode = genNode(from, to, weight, *adjV);
    *adjV = newNode;
    return newNode;
}
int merge(Node *W[], int left, int right, int end){
    Node **temp = (Node**)malloc(sizeof(Node*)*(end-left)); int cnt = 0;
    int i = left, j = right;
    while (i < right && j < end){
        if (W[i]->weight <= W[j]->weight){
            temp[cnt++] = W[i++];
        }else{
            temp[cnt++] = W[j++];
        }
    }
    while (i < right) temp[cnt++] = W[i++];
    while (j < end) temp[cnt++] = W[j++];
    for (int k = 0; k < cnt; k++) W[left+k] = temp[k];
    return left;
}
int mergesort(Node *W[], int idx, int sublen){
    if (sublen > 1){
        int halflen = sublen/2;
        return merge(W, mergesort(W, idx, halflen), mergesort(W, idx+halflen, sublen-halflen), idx+sublen);
    }
    return idx;
}
Node *deleteMinHeap(Node *minHeap[], int *heaplen){
    int len = *heaplen;
    Node *minNode = minHeap[1];
    minHeap[1] = minHeap[len--];
    int i = 1;
    while (i*2 <= len){
        int m = i*2;
        if (i*2+1 <= len && minHeap[i*2]->weight > minHeap[i*2+1]->weight){
            m = i*2+1;
        }
        if (minHeap[i]->weight > minHeap[m]->weight){
            Node *temp = minHeap[i];
            minHeap[i] = minHeap[m]; minHeap[m] = temp;
            i = m;
        }else break;
    }
    *heaplen = len;
    return minNode;
}
void insertMinHeap(Node *minHeap[], Node *node, int *heaplen){
    int len = *heaplen;
    minHeap[++len] = node;
    int i = len;
    while (i > 1){
        if (minHeap[i/2]->weight > minHeap[i]->weight){
            Node *temp = minHeap[i/2];
            minHeap[i/2] = minHeap[i]; minHeap[i] = temp;
            i /= 2;
        }else break;
    }
    *heaplen = len;
}
int findRoot(int parents[], int u){
    if (parents[u] == u) return u;
    return findRoot(parents, parents[u]);
}
Node **Kruskal(int n, Node *W[], int edgeNum){
    Node **spanTreeAdjList = (Node**)calloc(n+1, sizeof(Node*));
    spanTreeAdjList[0] = genNode(0, 0, 0, NULL);
    int parents[n+1];
    for (int i = 1; i <= n; i++) parents[i] = i;
    int cnt = 0, costSum = 0;
    for (int i = 0; i < edgeNum; i++){
        if (cnt == n-1){
            spanTreeAdjList[0]->weight = costSum;
            return spanTreeAdjList;
        }
        int rootA = findRoot(parents, W[i]->from);
        int rootB = findRoot(parents, W[i]->to);
        if (rootA != rootB){
            insertAdjList(spanTreeAdjList+W[i]->from, W[i]->from, W[i]->to, W[i]->weight);
            insertAdjList(spanTreeAdjList+W[i]->to, W[i]->from, W[i]->to, W[i]->weight);
            parents[rootA] = rootB;
            cnt++; costSum += W[i]->weight;
        }
    }
}
Node **Prim(int n, Node *leastEdge, Node **adjList){
    Node **queue = (Node**)malloc(sizeof(Node*)*(n*(n-1)/2+1));
    queue[0] = genNode(0, 0, 0, NULL);
    short *ht = (short*)calloc(n+1, sizeof(short)); ht[leastEdge->from] = 1;
    int heaplen = 0;
    for (Node *ptr = adjList[leastEdge->from]; ptr; ptr = ptr->next){
        insertMinHeap(queue, ptr, &heaplen);
    }

    Node **spanTreeAdjList = (Node**)calloc(n+1, sizeof(Node*));
    spanTreeAdjList[0] = genNode(0, 0, 0, NULL);

    int cnt = 0, costSum = 0;
    while (cnt < n-1){
        Node *minEdge = deleteMinHeap(queue, &heaplen);
        if (ht[minEdge->to]) continue;
        insertAdjList(spanTreeAdjList+minEdge->from, minEdge->from, minEdge->to, minEdge->weight);
        insertAdjList(spanTreeAdjList+minEdge->to, minEdge->to, minEdge->from, minEdge->weight);
        cnt++; costSum += minEdge->weight;
        ht[minEdge->to] = 1;
        for (Node *ptr = adjList[minEdge->to]; ptr; ptr = ptr->next){
            if (!ht[ptr->to]) insertMinHeap(queue, ptr, &heaplen);
        }
    }
    free(ht);
    spanTreeAdjList[0]->weight = costSum;
    return spanTreeAdjList;
}
int main(){
    int n; scanf("%d", &n);
    int from, to, weight;
    Node **adjList = (Node**)calloc(n+1, sizeof(Node*));
    Node **W = (Node**)calloc(n*(n-1)/2+1, sizeof(Node*));
    int Wlen = 0;
    while (scanf("%d%d%d", &from, &to, &weight) != EOF){
        if (!(0 < from && from <= n && 0 < to && to <= n && 0 < weight)) continue;
        Node *node = insertAdjList(adjList+from, from, to, weight);
        insertAdjList(adjList+to, to, from, weight);
        insertMinHeap(W, node, &Wlen);
    }
    Node **spanTreeAdjList = Prim(n, W[1], adjList);
    for (int i = 1; i <= n; i++){
        for (Node *ptr = spanTreeAdjList[i]; ptr; ptr = ptr->next){
            printf("%d %d %d\n", i, ptr->to, ptr->weight);
        }
    }
        

    return 0;
}