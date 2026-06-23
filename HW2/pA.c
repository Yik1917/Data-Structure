#include <stdio.h>

void swap(long long *x, long long *y){
    long long temp = *x;
    *x = *y;
    *y = temp;
}
void maintain(int accusedIdx, long long heap[]){
    while (accusedIdx > 1){
        int parentIdx = (accusedIdx % 2)? (accusedIdx-1)/2: (accusedIdx/2);
        if (heap[parentIdx] < heap[accusedIdx]){
            swap(heap+parentIdx, heap+accusedIdx);
        }else break;
        accusedIdx = parentIdx;
    }
    int len = heap[0];
    while (2*accusedIdx <= len){
        int childIdx;
        if (2*accusedIdx+1 <= len){
            childIdx = (heap[2*accusedIdx] >= heap[2*accusedIdx+1])? 2*accusedIdx: 2*accusedIdx+1;
        }else childIdx = 2*accusedIdx;

        if (heap[childIdx] > heap[accusedIdx]){
            swap(heap+childIdx, heap+accusedIdx);
        }else break;
        accusedIdx = childIdx;
    }
}
void insert_heap(long long x, long long heap[]){
    int len = heap[0];
    heap[++len] = x;
    heap[0] = len;
    maintain(len, heap);
}
void mergeFirstSecond(long long heap[]){
    long long resultOfMerger = heap[1] - heap[2];
    if (heap[0] == 2){
        heap[1] = resultOfMerger;
        heap[0]--;
        return;
    }
    long long secondValue = (heap[2] >= heap[3])? heap[2]: heap[3];
    resultOfMerger = heap[1]-secondValue;
    swap(heap+heap[0], heap+1);
    heap[0]--;
    maintain(1, heap);
    swap(heap+heap[0], heap+1);
    heap[0]--;
    maintain(1, heap);
    insert_heap(resultOfMerger, heap);
}
void printHeap(long long heap[]){
    int len = heap[0];
    for (int i = 1; i < len; i++){
        printf("%lld ", heap[i]);
    }
    printf("%lld\n", heap[len]);
}
void alter(int accusedIdx, long long delta, long long heap[]){
    heap[accusedIdx] += delta;
    maintain(accusedIdx, heap);
}
int main()
{
    long long heap[250001]; heap[0] = 0;
    int N; scanf("%d", &N);
    for (int i = 0; i < N; i++){
        short mode; scanf("%hd", &mode);
        if (mode == 0){
            long long x; scanf("%lld", &x);
            insert_heap(x, heap);
        }else if (mode == 1){
            mergeFirstSecond(heap);
        }else if (mode == 2){
            int idx; long long delta; scanf("%d%lld", &idx, &delta);
            alter(idx+1, delta, heap);
        }
    }
    printHeap(heap);
    return 0;
}