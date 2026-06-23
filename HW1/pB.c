#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, K; scanf("%d%d", &N, &K);
    int *arr = malloc(sizeof(int)*N), max = -99;
    for (int i = 0; i < N; i++){
        scanf("%d", arr+i);
        if (arr[i] > max) max = arr[i];
    }
    int *S = calloc(sizeof(int), max+1);
    for (int i = 0; i < N; i++){
        S[arr[i]]++;
    }
    int *prefS = malloc(sizeof(int)*(max+1));
    int sum = 0;
    for (int i = 0; i <= max; i++){
        sum += S[i];
        prefS[i] = sum;
    }

    long long maxResult = 0;
    for (int k = K; k <= max; k++){
        long long result = 0;
        int low = k-1, high = k+k-1;
        //printf("k=%d ", k);
        while (low < max){
            if (high > max) result += 1LL*(prefS[max]-prefS[low])*(low+1);
            else result += 1LL*(prefS[high]-prefS[low])*(low+1);
            //printf("%d %d\n", low, high);
            low += k; high += k;
        }
        //printf("result=%d\n", result);
        if (result > maxResult) maxResult = result;
    }
    printf("%lld\n", maxResult);
    return 0;
}