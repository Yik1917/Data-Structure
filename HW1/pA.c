#include <stdio.h>
#include <stdlib.h>

void printout(int indexs[], int N){
    for (int i = 0; i <= N-2; i++)
        printf("%d ", indexs[i]);
    printf("%d\n", indexs[N-1]);
}
int main(){
    int N; scanf("%d", &N);
    int *A = malloc(sizeof(int)*N);
    for (int i = 0; i < N; i++)
        scanf("%d", A+i);
    
    int *indexs = malloc(sizeof(int)*N);
    int *stack = malloc(sizeof(int)*N);
    int top = -1;
    for (int i = 0; i < N; i++){
        while (top >= 0 && A[stack[top]] >= A[i]) top--;
        if (top < 0) indexs[i] = -1;
        else{
            indexs[i] = i-stack[top];
        }
        stack[++top] = i;
    }
    printout(indexs, N);

    int cnt_not = 0, cnt_yes = 0;
    int *B = malloc(sizeof(int)*N);
    for (int i = 0; i < N; i++){
        if (indexs[i] == -1) cnt_not++;
        else                 B[cnt_yes++] = indexs[i];
    }

    if (cnt_not == N) printf("EMPTY\n");
    else              printout(B, cnt_yes);

    return 0;
}