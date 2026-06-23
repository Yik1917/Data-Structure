#include <stdio.h>
#include <stdlib.h>
#include "disjoint_set.h"
#include "treeStruct.h"

int find(int parents[], int key){
    if (parents[key] == -1) return key;
    int root = find(parents, parents[key]);
    parents[key] = root;
    return root;
}
void union_set(int parents[], int a, int b){ //May ask for Weight Rule or Height Rule
    int rootA = find(parents, a);
    int rootB = find(parents, b);
    if (rootA == rootB) return;
}