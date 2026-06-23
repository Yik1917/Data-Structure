typedef struct Edge{
    struct Node *u, *v;
    int w;
    char keep;
    void *var;
} Edge;
typedef struct Node{
    int id;
    int edge_count;
    struct Edge **edges;
    void *var;
} Node;

void generate_mst(Node *node);