#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node *prev;
    int value; int id;
    struct node *next;
}Node;

Node *head;

Node *generateNode(Node *prev, int value, int id, Node *next)
{
    Node *node = malloc(sizeof(Node));
    node->prev = prev;
    node->value = value;
    node->id = id;
    node->next = next;
    return node;
}
void insertNode(Node *prev, Node *insertedNode)
{
    if (head == NULL) return;

    insertedNode->next = prev->next;
    insertedNode->prev = prev;
    prev->next->prev = insertedNode;
    prev->next = insertedNode;
    return;
}
void deleteNode(Node *prev)
{
    prev->prev->next = prev->next;
    prev->next->prev = prev->prev;
    return;
}
Node *access(int id)
{
    for (Node *ptr = head->next; ptr != head; ptr = ptr->next){
        if (ptr->id == id) return ptr;
    }
    return NULL;
}
void printLinkedlist()
{
    if (head->next == head) {
        printf("EMPTY\nEMPTY\n");
        return;
    }
    
    Node *ptr;
    for (ptr = head->next; ptr->next != head; ptr = ptr->next) printf("%d ", ptr->value);
    printf("%d\n", ptr->value);
    for ( ; ptr->prev != head; ptr = ptr->prev) printf("%d ", ptr->value);
    printf("%d\n", ptr->value);
    return;
}
int main()
{
    int N, Q; scanf("%d%d", &N, &Q);
    int cnt = N;

    //Generate doubly circular Linkedlist
    head = generateNode(NULL, 0, 0, NULL);
    Node *prev = head;
    for (int i = 1; i < N; i++){
        int num; scanf("%d", &num);
        Node *newNode = generateNode(prev, num, i, NULL);
        prev->next = newNode;
        prev = newNode;
    }
    int num; scanf("%d", &num);
    Node *newNode = generateNode(prev, num, N, head);
    head->prev = newNode;
    prev->next = newNode;
    //

    for (int i = 0; i < Q; i++){
        getchar();
        char mode; scanf("%c", &mode);
        if (mode == 'M'){
            char postfix; scanf("%c", &postfix);
            if (postfix == 'H'){
                int k; scanf("%d", &k);
                Node *kNode = access(k);
                deleteNode(kNode);
                insertNode(head, kNode);
            }else if (postfix == 'T'){
                int k; scanf("%d", &k);
                Node *kNode = access(k);
                deleteNode(kNode);
                insertNode(head->prev, kNode);
            }
        }else{
            if (mode == 'H'){
                int x; scanf("%d", &x);
                Node *insertedNode = generateNode(NULL, x, ++cnt, NULL);
                insertNode(head, insertedNode);
            }else if (mode == 'T'){
                int x; scanf("%d", &x);
                Node *insertedNode = generateNode(NULL, x, ++cnt, NULL);
                insertNode(head->prev, insertedNode);
            }else if (mode == 'A'){
                int k; scanf("%d", &k);
                int x; scanf("%d", &x);
                Node *kNode = access(k);
                Node *insertedNode = generateNode(NULL, x, ++cnt, NULL);
                insertNode(kNode, insertedNode);
            }else if (mode == 'B'){
                int k; scanf("%d", &k);
                int x; scanf("%d", &x);
                Node *kNode = access(k);
                Node *insertedNode = generateNode(NULL, x, ++cnt, NULL);
                insertNode(kNode->prev, insertedNode);
            }else if (mode == 'D'){
                int k; scanf("%d", &k);
                Node *kNode = access(k);
                deleteNode(kNode);
            }
        }
    }
    printLinkedlist();

    return 0;
}