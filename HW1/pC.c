#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node *prev;
    char letter;
    struct node *next;
} Node;
Node *head;

void insertNode(Node *prev, Node *insertedNode)
{
    if (head == NULL) return;

    insertedNode->next = prev->next;
    insertedNode->prev = prev;
    if (prev->next != NULL){
        prev->next->prev = insertedNode;
    }
    prev->next = insertedNode;
}
Node *deleteNode(Node *prev)
{
    if (prev->prev == NULL) return prev;
    prev->prev->next = prev->next;
    if (prev->next) prev->next->prev = prev->prev;
    return prev->prev;
}
Node *generateNode(Node *prev, char letter, Node *next)
{
    Node *node = malloc(sizeof(Node));
    node->prev = prev;
    node->letter = letter;
    node->next = next;
    return node;
}
void printLinkedlist()
{
    for (Node *ptr = head->next; ptr != NULL; ptr = ptr->next) printf("%c", ptr->letter);
    printf("\n");
    return;
}
int main()
{
    char str[255] = {}; scanf("%s", str);
    if (!str[0]) return -1;

    //Generate doubly Linkedlist
    head = generateNode(NULL, '\0', NULL);
    int i = 0;
    Node *prev = head;
    while (i < 255 && str[i]){
        Node *newNode = generateNode(prev, str[i], NULL);
        prev->next = newNode;
        prev = newNode;
        i++;
    }

    int M; scanf("%d", &M);
    Node *ptr = head;
    while (ptr->next) ptr = ptr->next;
    Node *current = ptr;
    for (int i = 0; i < M; i++){
        getchar();
        char input; scanf("%c", &input);
        if (input == 'L'){
            if (current->prev){
                current = current->prev;
            }
        }else if (input == 'R'){
            if (current->next){
                current = current->next;
            }
        }else if (input == 'I'){
            getchar();
            char letter; scanf("%c", &letter);
            Node *insertedNode = generateNode(NULL, letter, NULL);
            insertNode(current, insertedNode);
            current = insertedNode;
        }else if (input == 'D'){
            current = deleteNode(current);
        }
    }
    printLinkedlist();

    return 0;
}