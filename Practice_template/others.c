#include <stdio.h>
#include <stdlib.h>
#include "treeStruct.h"
#include "others.h"

void genTreeLevelOrder(Node *root, int values[], int len){
    Node **que = malloc(sizeof(Node*)*len); int front = 0, rear = 0, lastrear = 0;
    que[rear++] = root;
    for (int i = 1;;){
        int temp = rear;
        for (int j = lastrear; j < temp; j++){
            if (i >= len){
                printf("values[] reached the end.\n");
                return;
            }
            Node *newLeft = genNode(values[i++], NULL, NULL);
            que[j]->left = newLeft;
            que[rear++] = newLeft;
            if (i >= len){
                printf("values[] reached the end.\n");
                return;
            }
            Node *newRight = genNode(values[i++], NULL, NULL);
            que[j]->right = newRight;
            que[rear++] = newRight;
        }
        lastrear = temp;
    }
}