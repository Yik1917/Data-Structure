#include <stdio.h>
#include <stdlib.h>
#include "treeStruct.h"
#include "hash.h"

int quadraticHash(int ht[], int key, int b){
    int k = key % b, i = 1;
    while (ht[k] != -1){
        k = (k + i*i) % b;
        i++;
    }
    return k;
}
int intervalSumHash(unsigned long long key, int m){ //123456789 => 987+654+321
    int unit = 3, temp = 0, sum = 0, i = 0;
    unsigned long long k = key;
    while (k > 0){
        temp *= 10;
        temp += k % 10;
        i++; k /= 10;
        if (i % unit == 0){
            sum += temp;
            temp = 0;
        }
    }
    sum += temp;
    return sum % m;
}
int foldingSumHash(unsigned long long key, int m){ //123456789 => 123+654+789
    int unit = 3, div = 1, temp = 0, sum = 0;
    unsigned long long k = key;
    for (int i = 0; i < unit; i++) div *= 10;
    short fold = 0;
    while (k > 0){
        int num = k % div; k /= div;
        if (fold % 2){
            while (num > 0){
                temp *= 10;
                temp += num % 10; num /= 10;
            }
        }else temp = num;
        sum += temp; temp = 0;
        fold++;
    }
    return sum % m;
}
short bloomFilterCheck(short filterHT[], unsigned long long key, int m, int (*h1)(unsigned long long, int), int (*h2)(unsigned long long, int)){
    int hash1 = h1(key, m);
    int hash2 = h2(key, m);
    return filterHT[hash1]*filterHT[hash2];
}