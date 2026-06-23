#include <stdio.h>
#include <stdlib.h>

typedef struct Pos{
    int x, y;
} Pos;

int M, N;
char *map;
int *costs;
short *ht;
Pos *que;
int front = 0, rear = 0;
Pos holes[26][2] = {};
short holesCnt[26] = {};
Pos B, E;

void adjAdd(int x, int y, int leastCost){
    short check = 0;
    char letter = map[x*N+y];
    if ('A' <= letter && letter <= 'Z' && letter != 'B' && letter != 'E') check = 1;

    int pos_x = -1, pos_y = -1;
    if (x+1 < M && !ht[(x+1)*N+y] && map[(x+1)*N+y] != '#'){
        pos_x = x+1; pos_y = y;
        que[rear].x = pos_x; que[rear++].y = pos_y;
        costs[pos_x*N+pos_y] = leastCost+1;
        ht[pos_x*N+pos_y] = 1;
    }
    if (y+1 < N && !ht[x*N+y+1] && map[x*N+y+1] != '#'){
        pos_x = x; pos_y = y+1;
        que[rear].x = pos_x; que[rear++].y = pos_y;
        costs[pos_x*N+pos_y] = leastCost+1;
        ht[pos_x*N+pos_y] = 1;
    }
    if (0 <= x-1 && !ht[(x-1)*N+y] && map[(x-1)*N+y] != '#'){
        pos_x = x-1; pos_y = y;
        que[rear].x = pos_x; que[rear++].y = pos_y;
        costs[pos_x*N+pos_y] = leastCost+1;
        ht[pos_x*N+pos_y] = 1;
    }
    if (0 <= y-1 && !ht[x*N+y-1] && map[x*N+y-1] != '#'){
        pos_x = x; pos_y = y-1;
        que[rear].x = pos_x; que[rear++].y = pos_y;
        costs[pos_x*N+pos_y] = leastCost+1;
        ht[pos_x*N+pos_y] = 1;
    }
    if (check && holesCnt[letter-'A'] >= 2){
        if (holes[letter-'A'][0].x == x && holes[letter-'A'][0].y == y){
            pos_x = holes[letter-'A'][1].x; pos_y = holes[letter-'A'][1].y;
        }else{
            pos_x = holes[letter-'A'][0].x; pos_y = holes[letter-'A'][0].y;
        }
        if (!(ht[pos_x*N+pos_y])){
            que[rear].x = pos_x; que[rear++].y = pos_y;
            costs[pos_x*N+pos_y] = leastCost+1;
            ht[pos_x*N+pos_y] = 1;
        }
    }
}
int BFS(int x, int y, int startCost){
    while (front < rear) {
        Pos pos = que[front];
        adjAdd(pos.x, pos.y, costs[pos.x*N+pos.y]);
        front++;
        if (costs[E.x*N+E.y]) return costs[E.x*N+E.y];
    }
    return -1;
}
int main(){
    scanf("%d%d", &M, &N); getchar();
    map = (char*)malloc(sizeof(char)*M*N);
    costs = (int*)calloc(M*N, sizeof(int));
    ht = (short*)calloc(M*N, sizeof(int));
    que = malloc(sizeof(Pos)*M*N);
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            char input; scanf("%c", &input);
            map[i*N+j] = input;
            if ('A' <= input && input <= 'Z'){
                int pos = input-'A';
                holes[pos][holesCnt[pos]].x = i;
                holes[pos][holesCnt[pos]].y = j;
                holesCnt[pos]++;
            }
        }
        getchar();
    }
    B = holes['B'-'A'][0]; E = holes['E'-'A'][0];
    ht[B.x*N+B.y] = 1;
    que[rear].x = B.x; que[rear++].y = B.y;
    int result = BFS(B.x, B.y, 0);
    printf("%d\n", result);
    free(map); free(costs); free(ht); free(que);
    return 0;
}