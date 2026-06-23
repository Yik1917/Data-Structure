#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
int SearchHeapArray(int heap[], int accusedValue){
    for (int i = 1; i <= heap[0]; i++){
        if (accusedValue == heap[i]) return i;
    }
    printf("The accusedValue is not in the heap!!!\n");
    return -1;
}
void InsertMinHeapArray(int heap[], int accusedValue){
    int len = heap[0];
    heap[++len] = accusedValue;
    int i = len; int cntOfLoop = 0;
    while (1){
        if (cntOfLoop++ > 1e6){
            printf("may sink into infinite loop!!!\n");
            break;
        }
        int parentIdx = (i % 2)? (i-1)/2: i/2;
        if (parentIdx < 1){
            break;
        }
        if (heap[parentIdx] > heap[i]){
            swap(heap+parentIdx, heap+i);
        }else break;
        i = parentIdx;
    }
    heap[0] = len;
}
void DeleteMinHeapArray(int heap[], int accusedValue){
    int accusedIdx = SearchHeapArray(heap, accusedValue);
    int len = heap[0];
    swap(heap+accusedIdx, heap+len);
    len--; heap[0] = len;
    int i = accusedIdx; int cntOfLoop = 0;
    while (1){
        if (cntOfLoop++ > 1e6){
            printf("may sink into infinite loop!!!\n");
            return;
        }
        if (2*i > len){
            return;
        }else{
            if (heap[i] > heap[2*i]){
                swap(heap+i, heap+2*i);
                i = 2*i;
            }else return;
        }
    }
}