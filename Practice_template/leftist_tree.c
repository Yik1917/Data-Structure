#include <stdio.h>
#include <stdlib.h>
#include "leftist_tree.h"

int shortest(LefNode *node){ //耗時作法
    int leftD = (node->left)? shortest(node->left): 0;
    int rightD = (node->right)? shortest(node->right): 0;
    return (leftD < rightD)? 1+leftD: 1+rightD;
}
void bottomUp(LefNode *node){ //不管有沒有交換，都要做shortest的更新
    if (node->right){
        bottomUp(node->right);
        if (node->left){
            if (node->left->shortest < node->right->shortest){
                node->shortest = node->left->shortest+1;
                LefNode *temp = node->left;
                node->left = node->right;
                node->right = temp;
            }else node->shortest = node->right->shortest+1;
        }else{
            node->shortest = 1;
            node->left = node->right;
            node->right = NULL;
        }
    }else node->shortest = 1;
}
LefNode *meldLeftist(LefNode *rootA, LefNode *rootB){
    if (rootA == NULL && rootB == NULL) return NULL;
    if (rootA == NULL) return rootB;
    if (rootB == NULL) return rootA;
    //Phase1
    LefNode *root;
    if (rootA->value < rootB->value){
        root = rootA;
    }else{
        root = rootB;
        rootB = rootA;
    }
    LefNode *ptr;
    for (ptr = root; ptr->right != NULL; ptr = ptr->right){
        if (ptr->right->value > rootB->value){
            LefNode *temp = ptr->right;
            ptr->right = rootB;
            rootB = temp;
        }
    }
    ptr->right = rootB;
    
    //Phase2
    bottomUp(root);

    return root;
}
LefNode *insertLeftist(LefNode *root, int value){
    LefNode *newNode = (LefNode*)malloc(sizeof(LefNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return meldLeftist(root, newNode);
}
LefNode *deleteMinLeftist(LefNode *root){
    LefNode *finalRoot;
    if (root->left == NULL && root->right == NULL) finalRoot = NULL;
    else if (root->left && root->right == NULL) finalRoot = root->left;
    else if (root->left == NULL && root->right){
        printf("This is not a leftist tree!!\n");
        finalRoot = NULL;
    }else finalRoot = meldLeftist(root->left, root->right);

    free(root);
    return finalRoot;
}