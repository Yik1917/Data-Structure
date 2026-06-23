#ifndef TRAVERSAL_H
#define TRAVERSAL_H
#include "treeStruct.h"
Node **inorderTraversal(Node *subroot, int len);
Node **postorderTraversal(Node *subroot, int len);
Node **preorderTraversal(Node *subroot, int len);

#endif