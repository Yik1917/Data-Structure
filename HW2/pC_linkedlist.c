#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 10005
#define MAXTOK 10005
typedef struct Token {
    int type;   // 1 = number, 2 = operator, 3 = parentheses
    char ch;    // operator or parentheses
    int num;    // number
} Token;
typedef struct node{
    Token token;
    struct node *left, *right;
} Node;
Node *parenthesesAdd(Node *startPtr);
Node *unitCheck(Node *startPtr);

Node *headOfList;
Token listline[MAXLEN];
Node *root;

Node *genNode(Token token, Node *left, Node *right){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->token = token;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}
void insertNode(Node *insertedNode){
    insertedNode->left->right = insertedNode;
    insertedNode->right->left = insertedNode;
}
void getInput() {
    headOfList = genNode((Token){}, NULL, NULL);
    Node *prev = genNode((Token){3, '(', -1}, headOfList, NULL), *newNode;
    headOfList->right = prev;
    char input[20];
    while (scanf("%s", input) != EOF){
        char c = input[0];
        if ('0' <= c && c <= '9'){ //Number
            newNode = genNode((Token){1, ' ', atoi(input)}, prev, NULL);
        }else if (c == '+' || c == '-' || c == '*' || c == '/'){ //Operator
            newNode = genNode((Token){2, c, -1}, prev, NULL);
        }else{ //parentheses
            newNode = genNode((Token){3, c, -1}, prev, NULL);
        }
        prev->right = newNode;
        prev = newNode;
    }
    prev->right = genNode((Token){3, ')', -1}, prev, headOfList);
    headOfList->left = prev->right;
}
Node *parenthesesAdd(Node *startPtr){
    int operCnt = 0, cnt = 0; short check = 0; 
    for (Node *ptr = startPtr, *lastOperPtr = NULL; ptr && cnt < 50000; ptr = ptr->right){ 
        cnt++;
        if (ptr->token.type == 2){
            operCnt++;
            if (!lastOperPtr) continue;
            if (operCnt >= 2){
                if (((lastOperPtr->token.ch == '+' || lastOperPtr->token.ch == '-') && (ptr->token.ch == '+' || ptr->token.ch == '-')) || ((lastOperPtr->token.ch == '*' || lastOperPtr->token.ch == '/') && (ptr->token.ch == '*' || ptr->token.ch == '/'))){
                    insertNode(genNode((Token){3, '(', -1}, startPtr->left, startPtr));
                    insertNode(genNode((Token){3, ')', -1}, ptr->left, ptr));
                    check = 1;
                }else{
                    if (!check){
                        if ((lastOperPtr->token.ch == '+' || lastOperPtr->token.ch == '-') && (ptr->token.ch == '*' || ptr->token.ch == '/')){
                            startPtr = lastOperPtr->right;
                            operCnt = 0;
                            check = 0;
                        }else{
                            insertNode(genNode((Token){3, '(', -1}, startPtr->left, startPtr));
                            insertNode(genNode((Token){3, ')', -1}, ptr->left, ptr));
                            startPtr = ptr->right;
                            operCnt = 0;
                            continue;
                        }
                    }else{
                        check = 0;
                        startPtr = lastOperPtr->right;
                    }
                }
                operCnt--;
            }
            lastOperPtr = ptr;
            continue;
        }else if (ptr->token.ch == ')'){
            if (operCnt > 0 && !check && startPtr->left->token.ch != '('){
                insertNode(genNode((Token){3, '(', -1}, startPtr->left, startPtr));
                insertNode(genNode((Token){3, ')', -1}, ptr->left, ptr));
            }
            return ptr->left;
        }
        ptr = unitCheck(ptr);
    }
    return NULL;
}
Node *unitCheck(Node *startPtr){
    Node *ptr = startPtr;
    while (ptr != NULL){
        if (ptr->token.ch == '('){
            ptr = parenthesesAdd(ptr->right);
        }else if (ptr->token.type == 1){
            return ptr;
        }else if (ptr->token.ch == ')'){
            while (startPtr->right->token.ch == '(' && ptr->left->token.ch == ')'){
                startPtr = startPtr->right;
                ptr = ptr->left;
            }
            return ptr;
        }
        if (ptr) ptr = ptr->right;
    }
    return NULL;
}
Node *unitCheckforTreeBuild(Node *startPtr){
    Node *ptr = startPtr;
    int cnt = 0;
    while (ptr != NULL){
        if (ptr->token.ch == '(') cnt++;
        else if (ptr->token.ch == ')') cnt--;
        if (cnt == 0) return ptr;
        ptr = ptr->right;
    }
    return NULL;
}
long long ResultAndTreeBuild(Node *startPtr, Node *endPtr, Node *parent){
    if (startPtr == endPtr){
        parent->token.type = 1;
        parent->token.num = startPtr->token.num;
        return startPtr->token.num;
    }
    Node *boundPtr = unitCheckforTreeBuild(startPtr);
    Node *leftChild = genNode((Token){0, ' ', -1}, NULL, NULL), *rightChild = genNode((Token){0, ' ', -1}, NULL, NULL);
    parent->left = leftChild; parent->right = rightChild;
    parent->token.type = 2;
    parent->token.ch = boundPtr->right->token.ch;
    Node *operPtr, *leftboundPtr, *rightboundPtr;
    for (operPtr = boundPtr; operPtr->token.type != 2; operPtr = operPtr->right){/**/}
    if (startPtr->token.type == 3){
        startPtr = startPtr->right;
        leftboundPtr = operPtr->left->left;
    }else leftboundPtr = operPtr->left;
    if (endPtr->token.type == 3){
        endPtr = endPtr->left;
        rightboundPtr = operPtr->right->right;
    }else rightboundPtr = operPtr->right;

    if (parent->token.ch == '+'){
        return ResultAndTreeBuild(startPtr, leftboundPtr, leftChild)+ResultAndTreeBuild(rightboundPtr, endPtr, rightChild);
    }else if (parent->token.ch == '-'){
        return ResultAndTreeBuild(startPtr, leftboundPtr, leftChild)-ResultAndTreeBuild(rightboundPtr, endPtr, rightChild);
    }else if (parent->token.ch == '*'){
        return ResultAndTreeBuild(startPtr, leftboundPtr, leftChild)*ResultAndTreeBuild(rightboundPtr, endPtr, rightChild);
    }else{
        return ResultAndTreeBuild(startPtr, leftboundPtr, leftChild)/ResultAndTreeBuild(rightboundPtr, endPtr, rightChild);
    }
}
void printList(){
    for (Node *ptr = headOfList->right; ptr != headOfList; ptr = ptr->right){
        if (ptr->token.type == 1){
            printf("%d ", ptr->token.num);
        }else{
            printf("%c ", ptr->token.ch);
        }
    }
}
int preorderTraversal(Token que[]){
    int rear = 0;
    int top = 0;
    Node **stack = (Node**)malloc(MAXLEN * sizeof(Node*));
    stack[top++] = root;
    Node *parent, *startPtr;
    while (top){
        startPtr = stack[--top];
        for (parent = startPtr; parent != NULL; parent = parent->left){
            que[rear++] = parent->token;
            if (parent->right) stack[top++] = parent->right;
        }
    }
    free(stack);
    return rear;
}
void printPreorder(Token que[], int len){
    for (int i = 0; i < len-1; i++){
        if (que[i].type == 1) printf("%d ", que[i].num);
        else printf("%c ", que[i].ch);
    }
    if (que[len-1].type == 1) printf("%d\n", que[len-1].num);
    else printf("%c\n", que[len-1].ch);
}
int main() {
    getInput();
    parenthesesAdd(headOfList->right->right);
    //printList();
    root = genNode((Token){}, NULL, NULL);
    long long finalResult = ResultAndTreeBuild(headOfList->right->right, headOfList->left->left, root);
    printf("%lld\n", finalResult);
    Token preorderQue[MAXLEN];
    int lenOfQue = preorderTraversal(preorderQue);
    printPreorder(preorderQue, lenOfQue);
    return 0;
}