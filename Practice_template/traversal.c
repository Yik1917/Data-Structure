#include <stdio.h>
#include <stdlib.h>
#include "traversal.h"
#include "treeStruct.h"

Node **inorderTraversal(Node *subroot, int len){
    if (subroot == NULL || len <= 0){
        printf("Haveraversed but do not have subroot!!!\n");
        return NULL;
    }
    Node **st = (Node**)malloc(sizeof(Node*)*len); int top = 0;
    Node **resultQue = (Node**)malloc(sizeof(Node*)*len); int rear = 0;
    int cntOfLoop = 0;
    while (rear < len){
        if (cntOfLoop++ > 2*len){
            printf("Gen of ResultQue Failed!!!\n");
            return NULL;
        }
        for (Node *parent = subroot; parent != NULL; parent = parent->left){
            st[top++] = parent;
        }

        Node *topNode;
        do{
            topNode = st[--top];
            resultQue[rear++] = topNode;
        } while (topNode->right == NULL && top > 0);
        subroot = topNode->right;
    }
    free(st);
    return resultQue;
}
Node **postorderTraversal(Node *subroot, int len){
    Node **st = (Node**)malloc(sizeof(Node*)*len); int top = 0;
    Node **resultQue = (Node**)malloc(sizeof(Node*)*len); int rear = 0;
    int cntOfLoop = 0;
    while (rear < len){
        if (cntOfLoop++ > 2*len){
            printf("Gen of ResultQue Failed!!!\n");
            return NULL;
        }
        for (Node *parent = subroot; parent != NULL; parent = parent->left){
            st[top++] = parent;
        }
        Node *topNode = st[--top];
        Node *nextNode = topNode;
        while (topNode->right == NULL || topNode->right == nextNode){ //nextNode負責判斷是否在回去的路上
            resultQue[rear++] = topNode;
            nextNode = topNode;
            if (top == 0) return resultQue;
            topNode = st[--top];
        }
        top++;
        subroot = topNode->right;
    }
    return resultQue;
}
Node **preorderTraversal(Node *subroot, int len){
    Node **stack = (Node**)malloc(len*sizeof(Node*)); int top = 0;
    Node **resultQue = (Node**)malloc(len*sizeof(Node*)); int rear = 0;
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