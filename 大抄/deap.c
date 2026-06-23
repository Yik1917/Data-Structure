#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "deap.h"

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
int trans(int len1, int i, int j){
    if (i == -1 && j == -1) return -1;
    if (j == -1){
        if (i > len1) return -1;
        else{
            int L = floor(log(i)/log(2)) + 1;
            int shift = i - pow(2, L-1);
            j = pow(2, L-1)+pow(2, L-2)+shift;
            if (j > len1) j = trans(len1, (i % 2)? (i-1)/2: i/2, -1);
            return j;
        }
    }
    if (i == -1){
        if (j > len1) return -1;
        else{
            int L = floor(log(j)/log(2)) + 1;
            int shift = j - (pow(2, L-1) + pow(2, L-2));
            i = pow(2, L-1) + shift;
            return i;
        }
    }
    return -1;
}
short min_max(int idx){
    int L = floor(log(idx)/log(2)) + 1;
    if (idx >= pow(2, L-1)+pow(2, L-2)) return 2; // In max heap
    else return 1; // In min heap
}
void minHeap_maintain(int heap[], int i){ //注意因為是兩個heap合併，所以maintain的時候要多一點判斷，不然會超出min/max heap的範圍
    int len = heap[0];
    while (i > 3){
        int parentIdx = (i % 2)? (i-1)/2: i/2;
        if (heap[i] < heap[parentIdx]) swap(heap+i, heap+parentIdx);
        else break;
        i = parentIdx;
    }
    while (2*i <= len){
        int childIdx;
        if (2*i == len) childIdx = 2*i;
        else childIdx = (heap[2*i] <= heap[2*i+1])? 2*i: 2*i+1;
        if (heap[i] > heap[childIdx]){
            swap(heap+i, heap+childIdx);
            i = childIdx;
        }
        else break;
    }
}
void maxHeap_maintain(int heap[], int i){
    int len = heap[0];
    while (i > 3){
        int parentIdx = (i % 2)? (i-1)/2: i/2;
        if (heap[i] > heap[parentIdx]) swap(heap+i, heap+parentIdx);
        else break;
        i = parentIdx;
    }
    while (2*i <= len){
        int childIdx;
        if (2*i == len) childIdx = 2*i;
        else childIdx = (heap[2*i] >= heap[2*i+1])? 2*i: 2*i+1;
        if (heap[i] < heap[childIdx]){
            swap(heap+i, heap+childIdx);
            i = childIdx;
        }
        else break;
    }
}
void insertDeap(int heap[], int value){
    int len1 = heap[0];
    heap[++len1] = value; heap[0]++;
    short minOrMax = min_max(len1);
    int i, j;
    if (minOrMax == 1){
        i = len1; j = trans(len1, len1, -1);
    }else if (minOrMax == 2){
        i = trans(len1, -1, len1); j = len1;
    }
    if (heap[i] > heap[j]) swap(heap+i, heap+j);
    minHeap_maintain(heap, i);
    maxHeap_maintain(heap, j);
}
void deleteMinDeap(int heap[]){
    heap[2] = -1;
    int i = 2, len1 = heap[0];
    while (2*i <= len1){
        int childIdx;
        if (2*i == len1) childIdx = 2*i;
        else childIdx = (heap[2*i] <= heap[2*i+1])? 2*i: 2*i+1;
        swap(heap+i, heap+childIdx);
        i = childIdx;
    }
    heap[i] = heap[len1--]; heap[0]--;
    int j = trans(len1, i, -1);
    if (heap[i] > heap[j]) swap(heap+i, heap+j);
    minHeap_maintain(heap, i);
    maxHeap_maintain(heap, j);
}