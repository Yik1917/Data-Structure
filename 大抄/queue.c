#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int front = 0, rear = 0;
int queueAdd(int arr[], int size, int value){
    if ((rear+1)%size == front%size) return -1; // FULL
    arr[rear++] = value;
    return 1;
}
int queuePop(int arr[]){
    if (front == rear) return -1; //EMPTY
    return arr[front++];
}
