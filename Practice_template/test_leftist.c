#include <stdio.h>
#include <stdlib.h>
#include "treeStruct.h"
#include "traversal.h"
#include "binary_search_tree.h"
#include "leftist_tree.h"
#include "heap.h"

Node *root;
Node *genNode(int value, Node *left, Node *right){
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}
int main(){
    Node **nodes = calloc(81, sizeof(Node*));
    int value, left, right;
    while (scanf("%d%d%d", &value, &left, &right) != EOF){
        if (left != -1){
            if (nodes[left]) continue;
            nodes[left] = genNode(left, NULL, NULL);
        }
        if (right != -1){
            if (nodes[right]) continue;
            nodes[right] = genNode(right, NULL, NULL);
        }

        if (nodes[value]){
            if (left != -1) nodes[value]->left = nodes[left];
            if (right != -1) nodes[value]->right = nodes[right];
        }else nodes[value] = genNode(value, nodes[left], nodes[right]);
    }
    meldLeftist(nodes[2], nodes[5]);
    for (int i = 0; i < 20; i++){
        if (nodes[i]){
            int left = (nodes[i]->left)? nodes[i]->left->value: -1;
            int right = (nodes[i]->right)? nodes[i]->right->value: -1;
            printf("%d %d %d\n", nodes[i]->value, left, right);
        }
    }
    return 0;
}