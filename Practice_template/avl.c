#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

Node *genNode(int key, Node *left, Node *right, Node *parent){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = left;
    newNode->right = right;
    newNode->parent = parent;
    newNode->height = 1;
    return newNode;
}
short BF(Node *node){
    if (node == NULL) return -99;
    int leftH = 0, rightH = 0;
    if (node->left) leftH = node->left->height;
    if (node->right) rightH = node->right->height;
    return leftH - rightH;
}
Node *rightRotate(Node *node){
    Node *newRoot = node->left;
    node->left = newRoot->right;
    if (newRoot->right) newRoot->right->parent = node;
    newRoot->right = node;
    newRoot->parent = node->parent;
    node->parent = newRoot;
    return newRoot;
}
Node *leftRotate(Node *node){
    Node *newRoot = node->right;
    node->right = newRoot->left;
    if (newRoot->left) newRoot->left->parent = node;
    newRoot->left = node;
    newRoot->parent = node->parent;
    node->parent = newRoot;
    return newRoot;
}
Node *BF_adjust(Node **root, Node *accusedNode){
    if (accusedNode == NULL || *root == NULL) return accusedNode;
    int bf = BF(accusedNode);
    Node *newRoot;
    if (bf == 2){
        if (BF(accusedNode->left) == 1){
            newRoot = rightRotate(accusedNode);
        }else if (BF(accusedNode->left) == -1){
            accusedNode->left = leftRotate(accusedNode->left);
            accusedNode->left->parent = accusedNode;
            newRoot = rightRotate(accusedNode);
        }else if (BF(accusedNode->left) == 0){
            newRoot = rightRotate(accusedNode);
        }
    }else if (bf == -2){
        if (BF(accusedNode->right) == -1){
            newRoot = leftRotate(accusedNode);
        }else if (BF(accusedNode->right) == 1){
            accusedNode->right = rightRotate(accusedNode->right);
            accusedNode->right->parent = accusedNode;
            newRoot = leftRotate(accusedNode);
        }else if (BF(accusedNode->right) == 0){
            newRoot = leftRotate(accusedNode);
        }
    }else return accusedNode;
    int leftH = 0, rightH = 0;
    if (accusedNode->left) leftH = accusedNode->left->height;
    if (accusedNode->right) rightH = accusedNode->right->height;
    accusedNode->height = (leftH > rightH)? leftH+1: rightH+1;
    leftH = 0; rightH = 0;
    if (newRoot->left) leftH = newRoot->left->height;
    if (newRoot->right) rightH = newRoot->right->height;
    newRoot->height = (leftH > rightH)? leftH+1: rightH+1;

    Node *parent = newRoot->parent;
    if (parent == NULL) *root = newRoot;
    else if (parent->left == accusedNode) parent->left = newRoot;
    else parent->right = newRoot;
    return newRoot;
}
void insertAVL(Node **root, Node *accusedNode){
    if (accusedNode == NULL) return;
    if (*root == NULL){
        *root = accusedNode;
        return;
    }
    Node *ptr = *root;
    while (1){
        if (accusedNode->key < ptr->key){
            if (ptr->left == NULL){
                ptr->left = accusedNode; break;
            }
            ptr = ptr->left;
        }else{
            if (ptr->right == NULL){
                ptr->right = accusedNode; break;
            }
            ptr = ptr->right;
        }
    }
    accusedNode->parent = ptr;
    while (ptr){
        int leftH = 0, rightH = 0;
        if (ptr->left) leftH = ptr->left->height;
        if (ptr->right) rightH = ptr->right->height;
        int temp = (leftH > rightH)? leftH+1: rightH+1;
        if (temp == ptr->height) break;
        ptr->height = temp;
        ptr = BF_adjust(root, ptr);
        ptr = ptr->parent;
    }
}
Node **preorderTraversal(Node *subroot, int len){
    Node **stack = (Node**)malloc(len*sizeof(Node*)); int top = 0;
    Node **resultQue = (Node**)calloc(len, sizeof(Node*)); int rear = 0;
    stack[top++] = subroot;
    Node *parent, *startPtr;
    while (top > 0){
        startPtr = stack[--top];
        for (parent = startPtr; parent != NULL; parent = parent->left){
            resultQue[rear++] = parent;
            if (parent->right) stack[top++] = parent->right;
        }
    }
    free(stack);
    return resultQue;
}
int main(){
    Node *root = NULL;
    int input;
    while (scanf("%d", &input) != EOF){
        Node *node = genNode(input, NULL, NULL, NULL);
        insertAVL(&root, node);
    }
    Node **resultQue = preorderTraversal(root, 100);
    for (int i = 0; resultQue[i] != NULL; i++) printf("%d ", resultQue[i]->key);
    return 0;
}