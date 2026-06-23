#include <stdio.h.>
#include <stdlib.h>
#include "queue.h"

int main(){
    int arr[5];
    int size = sizeof(arr)/sizeof(int);
    queueAdd(arr, size, 2);
    queueAdd(arr, size, 3);
    printf("%d\n", queuePop(arr));
    for (int i = front; i < rear; i++){
        printf("%d ", arr[i]);
    }
}