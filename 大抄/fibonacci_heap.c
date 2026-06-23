#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX_DEGREE 10
#define MAX_TIMES 50
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

typedef struct link{
    struct link *prev, *next;
} Link;
typedef struct fiboNode{
    int key;
    short childCut;
    Link link;
    struct fiboNode *child;
    struct fiboNode *parent;
} FiboNode;

FiboNode *genNode(int key, Link link, FiboNode *child, FiboNode *parent){
    FiboNode *newNode = (FiboNode*)malloc(sizeof(FiboNode));
    newNode->key = key;
    newNode->childCut = 0;
    newNode->link = link;
    newNode->child = child;
    newNode->parent = parent;
    return newNode;
}
Link *insertCirLinkst(Link *link, Link *newLink){
    if (link == NULL){
        newLink->next = newLink;
        newLink->prev = newLink;
        return newLink;
    }
    newLink->next = link;
    newLink->prev = link->prev;
    link->prev = newLink;
    newLink->prev->next = newLink;
    return link;
}
Link *deleteCirLinkst(Link *link, Link *accusedLink){
    Link *temp = link;
    if (link == accusedLink){
        if (accusedLink->next == accusedLink){
            return NULL;
        }
        temp = link->next;
    }
    accusedLink->prev->next = accusedLink->next;
    accusedLink->next->prev = accusedLink->prev;
    return temp;
}
FiboNode *findMin(FiboNode *node){
    if (!node) return NULL;
    Link *ptr = &(node->link);
    FiboNode *minNode;
    int min = 10001;
    do{
        FiboNode *n = container_of(ptr, FiboNode, link);
        if (n->key < min) minNode = n;
        ptr = ptr->next;
    } while (ptr != &(node->link));
    return minNode;
}
int comp(const void *a, const void *b){
    return *((int*)b) - *((int*)a);
}
FiboNode *mergeFibo(FiboNode *fiboMin, int **degrees, FiboNode **ht){
    for (int i = 0; i <= MAX_DEGREE; i++){
        qsort(degrees[i]+1, degrees[i][0], sizeof(int), comp);
        int n = degrees[i][0];
        while (n > 1){
            FiboNode *L1 = ht[degrees[i][n--]];
            FiboNode *L2 = ht[degrees[i][n--]];
            if (L1->key <= L2->key){
                if (fiboMin->key > L1->key) fiboMin = L1;
                deleteCirLinkst(&(fiboMin->link), &(L2->link));
                if (L1->child) insertCirLinkst(&(L1->child->link), &(L2->link));
                else L1->child = container_of(insertCirLinkst(NULL, &(L2->link)), FiboNode, link);
                L2->parent = L1;
                degrees[i+1][++degrees[i+1][0]] = L1->key;
            }else{
                if (fiboMin->key > L2->key) fiboMin = L2;
                deleteCirLinkst(&(fiboMin->link), &(L1->link));
                if (L2->child) insertCirLinkst(&(L2->child->link), &(L1->link));
                else L2->child = container_of(insertCirLinkst(NULL, &(L1->link)), FiboNode, link);
                L1->parent = L2;
                degrees[i+1][++degrees[i+1][0]] = L2->key;
            }
        }
        degrees[i][0] = n;
    }
    return fiboMin;
}
FiboNode *insertFibo(FiboNode *fiboMin, int key, int **degrees, FiboNode **ht){
    FiboNode *newNode = genNode(key, (Link){NULL, NULL}, NULL, NULL);
    ht[key] = newNode; degrees[0][++degrees[0][0]] = key;
    if (!fiboMin){
        fiboMin = newNode;
        insertCirLinkst(NULL, &(newNode->link));
    }else{
        insertCirLinkst(&(fiboMin->link), &(newNode->link));
        if (fiboMin->key > newNode->key) fiboMin = newNode;
    }
    return fiboMin;
}
Link mergeCirLinkst(Link *link1, Link *link2){
    if (link1 == NULL && link2 == NULL) return (Link){NULL, NULL};
    if (link1 == NULL) return *link2;
    if (link2 == NULL) return *link1;
    Link *next1 = link1->next, *next2 = link2->next;
    next1->prev = link2; link2->next = next1;
    next2->prev = link1; link1->next = next2;
    return *link1;
}
FiboNode *meldFibo(FiboNode *fiboMin, int **degrees1, int **degrees2, FiboNode **ht){
    FiboNode *node = NULL; short check = 0;
    for (int i = 0; i <= MAX_DEGREE && !check; i++){
        for (int j = 1; j <= degrees2[i][0] && !check; j++){
            if (degrees2[i][j]){
                node = ht[degrees2[i][j]];
                check = 1;
            }
        }
    }
    if (!check) return mergeFibo(fiboMin, degrees1, ht);
    mergeCirLinkst(&(fiboMin->link), &(node->link));
    for (int i = 0; i <= MAX_DEGREE; i++){
        for (int j = 1;  j <= degrees2[i][0]; j++){
            degrees1[i][++degrees1[i][0]] = degrees2[i][j];
        }
    }
    fiboMin = mergeFibo(fiboMin, degrees1, ht);
    return fiboMin;
}
int **degreeCalc(FiboNode *node){
    FiboNode *ptr = node->child;
    int **degrees = calloc(MAX_DEGREE+1, sizeof(int*));
    for (int i = 0; i <= MAX_DEGREE; i++) degrees[i] = calloc(MAX_TIMES, sizeof(int));
    if (!ptr) return degrees;
    do {
        FiboNode *p = ptr->child;
        int cnt = 0;
        do {
            if (!p) break;
            cnt++;
            p = container_of(p->link.next, FiboNode, link);
        } while (p != ptr->child);
        degrees[cnt][++degrees[cnt][0]] = ptr->key;
        ptr = container_of(ptr->link.next, FiboNode, link);
    } while (ptr != node->child);
    return degrees;
}
int degree(FiboNode *node){
    FiboNode *ptr = node->child;
    int cnt = 0;
    do{
        if (!ptr) break;
        cnt++;
        ptr = container_of(ptr->link.next, FiboNode, link);
    } while (ptr != node->child);
    return cnt;
}
void cascadingCut(FiboNode *fiboMin, FiboNode *node, int **degrees){
    FiboNode *ptr = node;
    int cnt;
    while (ptr && ptr->parent && ptr->childCut == 1){
        int d = degree(ptr);
        degrees[d][++degrees[d][0]] = ptr->key;
        Link *link = deleteCirLinkst(&(ptr->parent->child->link), &(ptr->link));
        ptr->parent->child = (link)? container_of(link, FiboNode, link): NULL;
        insertCirLinkst(&(fiboMin->link), &(ptr->link));
        ptr = ptr->parent;
    }
    if (ptr && ptr->parent) ptr->childCut = 1;
}
FiboNode *decreaseKey(FiboNode *fiboMin, int key, int num, int **degrees, FiboNode **ht){
    FiboNode *node = ht[key];
    node->key -= num;
    ht[key] = NULL; ht[key-num] = node;
    int d = degree(node);
    if (node->parent == NULL){
        if (fiboMin->key > node->key) fiboMin = node;
        for (int i = 1; i <= degrees[d][0]; i++){
            if (degrees[d][i] == key) degrees[d][i] -= num;
        }
    }else if (node->key < node->parent->key){
        degrees[d][++degrees[d][0]] = node->key;
        Link *link = deleteCirLinkst(&(node->parent->child->link), &(node->link));
        node->parent->child = (link)? container_of(link, FiboNode, link): NULL;
        insertCirLinkst(&(fiboMin->link), &(node->link));
        if (fiboMin->key > node->key) fiboMin = node;
        cascadingCut(fiboMin, node->parent, degrees);
        node->parent = NULL;
    }
    return fiboMin;
}
void degreeClean(int *degree, int banned){
    int newdegree[MAX_TIMES] = {};
    int rear = 0;
    for (int i = 1; i <= degree[0]; i++){
        if (degree[i] != banned) newdegree[++rear] = degree[i];
    }
    degree[0] = rear;
    for (int i = 1; i <= rear; i++) degree[i] = newdegree[i];
}
FiboNode *deleteFibo(FiboNode *fiboMin, int key, int **degrees, FiboNode **ht){
    FiboNode *node = ht[key];
    if (node->parent == NULL){
        Link *link = deleteCirLinkst(&(fiboMin->link), &(node->link));
        fiboMin = (link)? container_of(link, FiboNode, link): NULL;
    }else{
        Link *link = deleteCirLinkst(&(node->parent->child->link), &(node->link));
        node->parent->child = (link)? container_of(link, FiboNode, link): NULL;
    }
    int **degrees1 = degreeCalc(node);
    int d = degree(ht[key]);
    degreeClean(degrees[d], key);
    fiboMin = meldFibo(fiboMin, degrees, degrees1, ht);
    ht[key] = NULL;
    cascadingCut(fiboMin, node->parent, degrees);
    free(node); free(degrees1);
    fiboMin = mergeFibo(fiboMin, degrees, ht);
    return fiboMin;
}
FiboNode *extractMin(FiboNode *fiboMin, int **degrees, FiboNode **ht){
    int **degrees1 = degreeCalc(fiboMin);
    FiboNode *temp = fiboMin;
    Link *link = deleteCirLinkst(&(fiboMin->link), &(fiboMin->link));
    fiboMin = (link)? container_of(link, FiboNode, link): NULL;
    int d = degree(ht[temp->key]);
    degreeClean(degrees[d], temp->key);
    fiboMin = meldFibo(fiboMin, degrees, degrees1, ht);
    ht[temp->key] = NULL;
    free(temp); free(degrees1);
    return fiboMin;
}
int compareKeys(const void *a, const void *b) {
    FiboNode *nodeA = *(FiboNode **)a;
    FiboNode *nodeB = *(FiboNode **)b;
    return nodeA->key - nodeB->key;
}

int compareRoots(const void *a, const void *b) {
    FiboNode *nodeA = *(FiboNode **)a;
    FiboNode *nodeB = *(FiboNode **)b;
    int degA = degree(nodeA);
    int degB = degree(nodeB);
    
    if (degA != degB) {
        return degA - degB;
    }
    return nodeA->key - nodeB->key;
}

void printFibo_LevelOrder(FiboNode *minNode) {
    if (!minNode) return;
    FiboNode *roots[10001]; 
    int rootCount = 0;
    FiboNode *ptr = minNode;
    do {
        roots[rootCount++] = ptr;
        ptr = container_of(ptr->link.next, FiboNode, link);
    } while (ptr != minNode && ptr);
    qsort(roots, rootCount, sizeof(FiboNode*), compareRoots);
    FiboNode *queue[10001];
    FiboNode *nextLevel[10001];
    
    for (int i = 0; i < rootCount; i++) {
        FiboNode *root = roots[i];
        printf("%d", root->key);
        int qSize = 0;
        queue[qSize++] = root;
        while (qSize > 0) {
            int nextCount = 0;            
            for (int j = 0; j < qSize; j++) {
                FiboNode *parent = queue[j];
                
                if (parent->child) {
                    FiboNode *child = parent->child;
                    do {
                        nextLevel[nextCount++] = child;
                        child = container_of(child->link.next, FiboNode, link);
                    } while (child != parent->child);
                }
            }            
            if (nextCount > 0) {
                qsort(nextLevel, nextCount, sizeof(FiboNode*), compareKeys);                
                for (int k = 0; k < nextCount; k++) {
                    printf(" %d", nextLevel[k]->key); 
                    queue[k] = nextLevel[k]; 
                }
                qSize = nextCount;
            } else {
                qSize = 0;
            }
        }
        printf("\n");
    }
}
int main(){
    FiboNode *fiboMin = NULL;
    int **degrees = calloc(MAX_DEGREE+1, sizeof(int*));
    for (int i = 0; i <= MAX_DEGREE; i++) degrees[i] = calloc(MAX_TIMES, sizeof(int));
    FiboNode **ht = calloc(10001, sizeof(FiboNode*));
    char input[15];
    while (scanf("%s", input) != EOF){
        if (strcmp(input, "insert") == 0){
            int key; scanf("%d", &key);
            fiboMin = insertFibo(fiboMin, key, degrees, ht);
        }else if (strcmp(input, "delete") == 0){
            int key; scanf("%d", &key);
            fiboMin = deleteFibo(fiboMin, key, degrees, ht);
        }else if (strcmp(input, "decrease") == 0){
            int key, num; scanf("%d%d", &key, &num);
            fiboMin = decreaseKey(fiboMin, key, num, degrees, ht);
        }else if (strcmp(input, "extract-min") == 0){
            fiboMin = extractMin(fiboMin, degrees, ht);
        }else if (strcmp(input, "exit") == 0){
            break;
        }
    }
    printFibo_LevelOrder(fiboMin);
    return 0;
}