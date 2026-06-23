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
Token input[MAXTOK];
typedef struct node{
    Token token;
    struct node *left, *right;
} Node;
int cntHash[MAXLEN];
int parHash[MAXLEN];
int input_len = 0;
Node *root;
void init() {
    for (int i = 0; i < MAXTOK; i++) {
        input[i].type = 0;
        input[i].ch = '\0';
        input[i].num = 0;
    }
    for (int i = 0; i < MAXLEN; i++) parHash[i] = -1;
}
void getInput() {
    char line[MAXLEN];
    fgets(line, sizeof(line), stdin);
    int len = strlen(line);
    for (int i = 0; i < len; i++) {
        char c = line[i];
        if (c == ' ')
            input_len += 1;
        else if ('0' <= c && c <= '9') {
            input[input_len].type = 1; // number
            input[input_len].num = input[input_len].num * 10 + (c - '0');
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            input[input_len].type = 2; // operator
            input[input_len].ch = c;
        } else if (c == '(' || c == ')') {
            input[input_len].type = 3; // parentheses
            input[input_len].ch = c;
        } else {
            break; // end of line
        }
    }
    ++input_len;
}
Node *genNode(Token token, Node *left, Node *right){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->token = token;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}
void parCombine(){
    for (int i = input_len-1, cnt = 0; i >= 0; i--){
        if (input[i].ch == ')')
            cntHash[cnt++] = i;
        else if (input[i].ch == '(')
            parHash[cntHash[--cnt]] = i;
    }
}
int unitCheck(int idx, int startIdx, short *returnCheck){
    short checkOfFirstMulti = 0; int firstMultiIdx = startIdx-1;
    for (int i = idx, check = 1; i >= startIdx; i--){
        if (input[i].ch == ')') i = parHash[i];
        else if (input[i].ch == '+' || input[i].ch == '-') check = 0;
        else if (!checkOfFirstMulti && (input[i].ch == '*' || input[i].ch == '/')){
            firstMultiIdx = i;
            checkOfFirstMulti = 1;
            *returnCheck = checkOfFirstMulti;
        }
        if (!check) return i+1;
    }
    return firstMultiIdx+1; //This is a cosecutive multiplication
}

int ResultAndTreeBuild(int startIdx, int endIdx, Node *parent){
    for (int i = endIdx; i >= startIdx; i--){
        if (i == startIdx){
            // 只剩一個 token（預期為數字）
            parent->token.type = 1;
            parent->token.num  = input[i].num;
            return parent->token.num;
        }

        // 由右往左：先抓以 i 結尾的「單元」起點
        short check = 0;
        int idx = unitCheck(i, startIdx, &check);  // [idx .. i] 是一個 number 或 (...) 段

        // 單元左邊若不是運算子（或已越界），把左界右移一格，繼續
        if (idx - 1 < startIdx || input[idx - 1].type != 2){
            startIdx++;
            continue;
        }

        // 在單元左邊那個運算子處切分（最右邊的該層運算子）→ 左結合
        Node *leftChild  = genNode((Token){}, NULL, NULL);
        Node *rightChild = genNode((Token){}, NULL, NULL);
        parent->token.type = 2;
        parent->token.ch   = input[idx - 1].ch;
        parent->left  = leftChild;
        parent->right = rightChild;

        char operator = input[idx - 1].ch;
        int  operIdx  = idx - 1;

        if (input[i].type == 3 && input[idx].type == 3){
            if (!check){
                i--;
                idx++;
            }
        }

        // 左半段：[startIdx .. operIdx-1]，右半段：[idx .. i]
        if (operator == '+')
            return ResultAndTreeBuild(startIdx, operIdx - 1, leftChild)
                 + ResultAndTreeBuild(idx, i, rightChild);
        if (operator == '-')
            return ResultAndTreeBuild(startIdx, operIdx - 1, leftChild)
                 - ResultAndTreeBuild(idx, i, rightChild);
        if (operator == '*')
            return ResultAndTreeBuild(startIdx, operIdx - 1, leftChild)
                 * ResultAndTreeBuild(idx, i, rightChild);
        return ResultAndTreeBuild(startIdx, operIdx - 1, leftChild)
             / ResultAndTreeBuild(idx, i, rightChild);
    }
    printf("Error\n");
    return -99;
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
    init();
    getInput();
    parCombine();
    //for (int i = input_len; i >= 0; i--) printf("%d %d\n", i, parHash[i]);
    //return 0;
    root = genNode((Token){}, NULL, NULL);
    long long calcuResult = ResultAndTreeBuild(0, input_len-1, root);
    printf("%lld\n", calcuResult);

    Token preorderQue[MAXLEN];
    int lenOfQue = preorderTraversal(preorderQue);
    printPreorder(preorderQue, lenOfQue);

    return 0;
}
//1 + 2 * ( 4 * ( 3 + 5 ) * 2 ) + 2