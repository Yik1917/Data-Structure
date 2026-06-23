#include <stdio.h>
#include <stdlib.h>
#include "minmax_heap.h"

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
short levelDetermine(int index){
    int lower = 1, upper = 2;
    int cnt = 0;
    while (!(lower <= index && index < upper)){
        cnt++;
        lower *= 2; upper *= 2;
    }
    if (cnt % 2) return 2; //Max Level
    else return 1; //Min level
}
int moveUpper(int idx){ //return the index of the upper same kind of level
    int i = (idx % 2)? (idx-1)/2: idx/2;
    return (i % 2)? (i-1)/2: i/2;
}
int getMin(int heap[]){
    if (heap[0] == 0) return -99;
    else return heap[1];
}
int getMax(int heap[]){
    if (heap[0] == 0) return -99;
    if (heap[0] == 1) return heap[1];
    int len = heap[0];
    int smallest = INT_MAX;
    for (int i = 2; i <= len && i < 4; i++){
        if (heap[i] < smallest) smallest = heap[i];
    }
    return smallest;
}
void insertMinMax(int heap[], int value){
    if (heap[0] == 0){
        heap[1] = value; heap[0]++;
        return;
    }
    int len = heap[0];
    heap[++len] = value; heap[0]++;
    int childIdx = len;
    int parentIdx = (childIdx % 2)? (childIdx-1)/2: childIdx/2;
    int i;
    if (levelDetermine(len) == 1){ //Min level
        if (heap[childIdx] > heap[parentIdx]){
            swap(heap+childIdx, heap+parentIdx);
            i = parentIdx;
            while (i > 3){
                int upperI = moveUpper(i);
                if (heap[upperI] < heap[i]){
                    swap(heap+upperI, heap+i); i = upperI;
                }else break;
            }
        }else{
            i = childIdx;
            while (i > 3){
                int upperI = moveUpper(i);
                if (heap[upperI] > heap[i]){
                    swap(heap+upperI, heap+i); i = upperI;
                }else break;
            }
        }
    }else{ //Max level
        if (heap[childIdx] < heap[parentIdx]){
            swap(heap+childIdx, heap+parentIdx);
            i = parentIdx;
            while (i > 3){
                int upperI = moveUpper(i);
                if (heap[upperI] > heap[i]){
                    swap(heap+upperI, heap+i); i = upperI;
                }else break;
            }
        }else{
            i = childIdx;
            while (i > 3){
                int upperI = moveUpper(i);
                if (heap[upperI] < heap[i]){
                    swap(heap+upperI, heap+i); i = upperI;
                }else break;
            }
        }
    }
}
void deleteMinMinMax(int heap[]){
    int len = heap[0];
    if (len == 0) return;
    heap[1] = heap[len--]; heap[0]--;
    if (len < 2) return;
    int i = 1;
    while (4*i <= len){
        int smallest = INT_MAX, smallestIdx;
        for (int j = 0; j < 4; j++){
            int idx = 4*i + j;
            if (idx > len) break;
            if (heap[idx] < smallest){
                smallest = heap[idx];
                smallestIdx = idx;
            }
        }
        if (heap[i] > smallest){
            swap(heap+i, heap+smallestIdx);
            i = smallestIdx;
            int parentIdx = (i % 2)? (i-1)/2: i/2;
            if (heap[i] > heap[parentIdx]) swap(heap+i, heap+parentIdx);
        }else break;
    }
    if (2*i > len) return;
    int smallestIdx;
    if (2*i == len) smallestIdx = 2*i;
    else smallestIdx = (heap[2*i] <= heap[2*i+1])? 2*i: 2*i+1;
    if (heap[i] > heap[smallestIdx]) swap(heap+i, heap+smallestIdx);
}