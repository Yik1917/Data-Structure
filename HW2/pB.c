#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int value;
    struct node *leftChild;
    struct node *rightChild;
} Node;
Node *head;
Node *genNode(int value, Node *leftChild, Node *rightChild){
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->leftChild = leftChild;
    newNode->rightChild = rightChild;
    return newNode;
}
void printBST(){    
    Node* BSTque[3000] = {head->leftChild};
    int front = 0, rear = 0;
    if (BSTque[front] == NULL){
        printf("\n"); return;
    }
    while (BSTque[front]){
        Node *left = BSTque[front]->leftChild, *right = BSTque[front]->rightChild;
        if (left){
            BSTque[++rear] = left;
        }
        if (right){
            BSTque[++rear] = right;
        }
        front++;
    }
    for (int i = 0; i < rear; i++){
        printf("%d ", BSTque[i]->value);
    }
    printf("%d\n", BSTque[rear]->value);
    
}
Node *findInorderSuccessor(Node *ptr){
    Node *firstPtr = ptr;
    if (firstPtr->leftChild == NULL){ //parentNode的rightchild直接是successor
        return firstPtr;
    }
    Node *prev;
    while (ptr->leftChild){
        prev = ptr;
        ptr = ptr->leftChild;
    }
    prev->leftChild = ptr->rightChild;
    ptr->rightChild = firstPtr;
    return ptr;
}
void insertBST(int value){
    Node *insertedNode = genNode(value, NULL, NULL);
    if (head->leftChild == NULL){
        head->leftChild = insertedNode;
        return;
    }
    Node *parentNode = head->leftChild;
    while (1){
        if (value >= parentNode->value){
            if (parentNode->rightChild == NULL){
                parentNode->rightChild = insertedNode;
                break;
            }
            parentNode = parentNode->rightChild;
        }else{
            if (parentNode->leftChild == NULL){
                parentNode->leftChild = insertedNode;
                break;
            }
            parentNode = parentNode->leftChild;
        }
    }
}
void deleteBST(int value){
    Node *parentNode = head->leftChild, *prev = head;
    while (1){
        if (parentNode->value == value){
            if (parentNode->leftChild && parentNode->rightChild){
                Node *succeededNode = findInorderSuccessor(parentNode->rightChild);
                if (prev->leftChild == parentNode){
                    prev->leftChild = succeededNode;
                }else{
                    prev->rightChild = succeededNode;
                }
                succeededNode->leftChild = parentNode->leftChild;
                free(parentNode);
                return;
            }
            if (parentNode->leftChild){
                if (prev->leftChild == parentNode){
                    prev->leftChild = parentNode->leftChild;
                }else{
                    prev->rightChild = parentNode->leftChild;
                }
                free(parentNode);
                return;
            }
            if (parentNode->rightChild){
                if (prev->leftChild == parentNode){
                    prev->leftChild = parentNode->rightChild;
                }else{
                    prev->rightChild = parentNode->rightChild;
                }
                free(parentNode);
                return;
            }
            if (prev->leftChild == parentNode){
                prev->leftChild = NULL;
            }else{
                prev->rightChild = NULL;
            }
            free(parentNode);
            return;
        }else if (value > parentNode->value){
            prev = parentNode;
            parentNode = parentNode->rightChild;
        }else if (value < parentNode->value){
            prev = parentNode;
            parentNode = parentNode->leftChild;
        }
    }
}
int main(){
    head = genNode(-1, NULL, NULL);
    while (1){
        char input[7]; scanf("%s", input);
        if (strcmp(input, "exit") == 0){
            printBST();
            break;
        }else if (strcmp(input, "insert") == 0){
            int x; scanf("%d", &x);
            insertBST(x);
        }else if (strcmp(input, "delete") == 0){
            int x; scanf("%d", &x);
            deleteBST(x);
        }
    }

    return 0;
}