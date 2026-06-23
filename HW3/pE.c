#include <stdlib.h>
#include <string.h>
#include "hash.h"

static Data *ht = NULL;
int mod = 100003;

void insert(Data *data){
    if (!ht){
        ht = (Data*)malloc(sizeof(Data)*mod); //1KB = 1024 byte, 1MB = 1024KB => 1MB = 1024*1024 byte
        memset(ht, -1, sizeof(Data)*mod);
    }

    int k = data->key % mod;
    int i = 1;
    while (ht[k].key != -1){
        k = (k + i*i) % mod;
        i++;
    }
    ht[k] = *data;
}
void remove(int key){
    if (!ht){
        ht = (Data*)malloc(sizeof(Data)*mod); //1KB = 1024 byte, 1MB = 1024KB => 1MB = 1024*1024 byte
        memset(ht, -1, sizeof(Data)*mod);
        //printf("hash table has not been created!!\n");
        return;
    }

    int k = key % mod, i = 1, value = -1;
    while (ht[k].key != -1){
        if (ht[k].key == key){
            value = ht[k].value;
            break;
        }
        k = (k + i*i) % mod;
        i++;
    }

    if (value == -1){
        //printf("The value is not in the hash table!!\n");
    }else{
        ht[k].key = -99;
    }
}
int search(int key){
    int k = key % mod, i = 1;
    while (ht[k].key != -1){
        if (ht[k].key == key) return ht[k].value;
        k = (k + i*i) % mod;
        i++;
    }
    return -1;
}