#include <stdio.h>
#include <stdlib.h>
#include "treeStruct.h"
#include "binary_search_tree.h"

Node *findInorderSuccessor(Node *ptr){
    Node *firstPtr = ptr;
    if (firstPtr->left == NULL){ //parentNode的rightchild直接是successor
        return firstPtr;
    }
    Node *prev;
    while (ptr->left){
        prev = ptr;
        ptr = ptr->left;
    }
    prev->left = ptr->right;
    ptr->right = firstPtr;
    return ptr;
}
void insertBST(Node **root, Node *accusedNode){
    if (accusedNode == NULL) return;
    if (*root == NULL){
        *root = accusedNode;
        return;
    }
    Node *parent = *root;
    int cntOfLoop = 0;
    while (1){
        if (cntOfLoop++ > 1e6){
            printf("may sink into infinite loop!!!\n");
            return;
        }
        if (accusedNode->value > parent->value){
            if (parent->right == NULL){
                parent->right = accusedNode;
                return;
            }
            parent = parent->right;
        }else{
            if (parent->left == NULL){
                parent->left = accusedNode;
                return;
            }
            parent = parent->left;
        }
    }
}
void deleteBST(Node **root, int value){
    Node *parentNode = *root, *prev = *root;
    while (1){
        if (parentNode->value == value){
            if (parentNode->left && parentNode->right){
                Node *succeededNode = findInorderSuccessor(parentNode->right); //是不是inorder successor有區別
                if (prev->left == parentNode){
                    prev->left = succeededNode;
                }else if (prev->right == parentNode)
                    prev->right = succeededNode;
                else{
                    *root = succeededNode;
                }
                succeededNode->left = parentNode->left;
                free(parentNode);
                return;
            }
            if (parentNode->left){
                if (prev->left == parentNode){
                    prev->left = parentNode->left;
                }else if (prev->right == parentNode)
                    prev->right = parentNode->left;
                else{
                    *root = parentNode->left;
                }
                free(parentNode);
                return;
            }
            if (parentNode->right){
                if (prev->left == parentNode){
                    prev->left = parentNode->right;
                }else if (prev->right == parentNode)
                    prev->right = parentNode->right;
                else{
                    *root = parentNode->right;
                }
                free(parentNode);
                return;
            }
            if (prev->left == parentNode)
                prev->left = NULL;
            else if (prev->right == parentNode)
                prev->right = NULL;
            else
                *root = NULL;
            free(parentNode);
            return;
        }else if (value > parentNode->value){
            prev = parentNode;
            if (parentNode->right) parentNode = parentNode->right;
            else{
                printf("Not found!!!\n");
                return;
            }
        }else if (value < parentNode->value){
            prev = parentNode;
            if (parentNode->left) parentNode = parentNode->left;
            else{
                printf("Not found!!!\n");
                return;
            }
        }
    }
}