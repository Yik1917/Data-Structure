#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H
#include "treeStruct.h"

int find(int parents[], int key);
void union_set(int parents[], int a, int b);

#endif