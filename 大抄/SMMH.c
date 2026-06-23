#include <stdio.h>
#include <stdlib.h>
#include "SMMH.h"

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
int SMMHCompAbove(int heap[], int idx){
    int parentIdx = (idx % 2)? (idx-1)/2: idx/2;
    int parentSiblIdx = (parentIdx % 2)? parentIdx-1: parentIdx+1;
    if (parentIdx <= 1 || parentSiblIdx <= 1) return -1;
    if (parentIdx > parentSiblIdx){
        if (heap[idx] < heap[parentSiblIdx]){
            swap(heap+parentSiblIdx, heap+idx);
            return parentSiblIdx;
        }
        if (heap[idx] > heap[parentIdx]){
            swap(heap+idx, heap+parentIdx);
            return parentIdx;
        }
    }else{
        if (heap[idx] > heap[parentSiblIdx]){
            swap(heap+parentSiblIdx, heap+idx);
            return parentSiblIdx;
        }
        if (heap[idx] < heap[parentIdx]){
            swap(heap+idx, heap+parentIdx);
            return parentIdx;
        }
    }
    return -1;
}
int SMMHCompBelow(int heap[], int idx){
    int siblIdx = idx+1;
    int len = heap[0];
    int smallestIdx;
    if (2*idx > len) return -1;
    if (2*siblIdx <= len) smallestIdx = (heap[2*idx] <= heap[2*siblIdx])? 2*idx: 2*siblIdx;
    else smallestIdx = 2*idx;
    
    if (heap[smallestIdx] < heap[idx]){
        swap(heap+smallestIdx, heap+idx);
        return smallestIdx; 
    }
    return -1;
}
void insertSMMH(int heap[], int value){
    int len = heap[0];
    heap[++len] = value; heap[0]++;
    int i = len;
    if (i % 2){
        int siblIdx = i-1;
        if (heap[siblIdx] > heap[i]){
            swap(heap+siblIdx, heap+i);
            i = siblIdx;
        }
    }else{
        int siblIdx = i+1;
        if (siblIdx <= len && heap[siblIdx] < heap[i]){
            swap(heap+siblIdx, heap+i);
            i = siblIdx;
        }
    }
    while (i != -1) i = SMMHCompAbove(heap, i);
}
void deleteMinSMMH(int heap[]){
    int len = heap[0];
    heap[2] = heap[len--]; heap[0]--;
    int i = 2;
    while (i != -1){
        if (heap[i] > heap[i+1]){
            swap(heap+i, heap+i+1);
            i = i+1;
        }
        i = SMMHCompBelow(heap, i);
    }
}
int main(){
    int heap[20] = {15, -1, 2, 80, 8, 60, 4, 50, 12, 20, 10, 16, 14, 30, 6, 40};
    deleteMinSMMH(heap);
    deleteMinSMMH(heap);
    printf("%d\n", heap[0]);
    printf("%d\n", heap[heap[0]]);
    for (int i = 2; i <= heap[0]; i++){
        printf("%d ", heap[i]);
    }
}