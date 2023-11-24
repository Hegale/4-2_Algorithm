#include <stdio.h>
#include <stdlib.h>

typedef struct s_edge {
    int origin; 
    int destination;
} t_edge;

typedef struct s_incidence {
    int edge;
    struct s_incidence *next;
} t_incidence;

typedef struct s_node {
    char name;
    int inDegree;
    t_incidence *outEdges; // 첫 노드는 아무것도 없는 헤드노드
    t_incidence *inEdges;
} t_node;

typedef struct s_qnode {
    int elem;
    struct s_qnode *next;
} t_qnode;

typedef struct s_queue {
    int count; // 큐의 노드 개수
    t_qnode *front;
    t_qnode *rear; 
} t_queue;

t_node *G; // 인덱스 = 정점 번호. elem = 정점 이름
t_edge *edges; // 정점들
int n = 0; // 정점 수
int m = 0; // 간선 수
int *topOrder; // 각 정점들의 위상순서.
int *Q; // 정점들의 대기열

//====== Queue ======//
t_queue *initQueue() {
    t_queue *queue = (t_queue *)malloc(sizeof(t_queue));

    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
    return queue;
}

int isQueueEmpty(t_queue *queue) {
    return (queue->count == 0);
}

void enqueue(t_queue *queue, int elem) {
    t_qnode *node = (t_qnode *)malloc(sizeof(t_qnode));
    
    node->elem = elem;
    node->next = NULL;

    if (isQueueEmpty(queue))
        queue->front = node;
    else
        queue->rear->next = node;
    
    queue->rear = node;
    queue->count++;
}

int dequeue(t_queue *queue) {
    t_qnode *p;
    int elem;

    if (isQueueEmpty(queue)) {
        printf("[Error] Queue is empty\n");
        return -1;
    }
    p = queue->front;
    elem = p->elem;
    queue->front = p->next; // 큐의 front를 다음 노드로
    free(p);
    queue->count--; //dequeue
    return elem;    
}

//====== Graph ======//
void initArray() {
    topOrder = (int *)malloc((n + 1) * sizeof(int));
    Q = (int *)malloc(n * sizeof(int));
}

int getIndex(char name) {
    for (int i = 0; i < n; ++i) {
        if (G[i].name == name)
            return i ;
    }
    return -1; // 오류 발생 가능, segfault
}

void addFirst(t_incidence *H, int i) {
    t_incidence *node = (t_incidence *)malloc(sizeof(t_incidence));
    node->edge = i;
    node->next = H->next;
    H->next = node;
}

// 그래프에 정점 삽입
void insertVertex(char vName, int i) {
    G[i].name = vName;
    G[i].outEdges = (t_incidence *)malloc(sizeof(t_incidence));
    G[i].outEdges->next = NULL;
    G[i].inEdges = (t_incidence *)malloc(sizeof(t_incidence));
    G[i].inEdges->next = NULL;
    G[i].inDegree = 0;
}

// 그래프에 방향간선 삽입
void insertDirectedEdge(char uName, char wName, int i) {
    int u, w; // 존재하지 않는 정점이 입력된 경우 오류발생 가능

    u = getIndex(uName);
    w = getIndex(wName);
    edges[i].origin = u;
    edges[i].destination = w;
    addFirst(G[u].outEdges, i);
    addFirst(G[w].inEdges, i);
    G[w].inDegree++;
}

// 그래프 생성
void buildGraph() {
    char vName;

    scanf("%d", &n);
    getchar();
    G = (t_node *)malloc(n * sizeof(t_node));

    // 각 노드 생성
    for (int i = 0; i < n; ++i) {
        scanf("%c", &vName);
        getchar();
        insertVertex(vName, i);
    }
    
    char uName, wName;

    scanf("%d", &m);
    getchar();
    edges = (t_edge *)malloc(m * sizeof(t_edge));
    for (int i = 0; i < m; ++i) {
        scanf("%c %c", &uName, &wName);
        getchar();
        insertDirectedEdge(uName, wName, i);
    }
}

void topologicalSort() {
    t_incidence *e;
    int u, w, t;

    t_queue *Q = initQueue();
    int *in = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        in[i] = G[i].inDegree;
        if (in[i] == 0)
            enqueue(Q, i); // 진입차수 0인 정점들을 큐에 삽입
    }

    t = 1;
    while (!isQueueEmpty(Q)) {
        u = dequeue(Q);
        topOrder[t] = u;
        t++;
        
        e = G[u].outEdges->next;
        while (e != NULL) {
            w = edges[e->edge].destination;
            in[w]--;
            if (in[w] == 0)
                enqueue(Q, w);
            e = e->next;
        }
    }

    if (t <= n)
        topOrder[0] = 0;
    else
        topOrder[0] = 1;
}

int main() {
    char cmd, a, b;

    buildGraph();
    initArray();
    
    topologicalSort();

    if (topOrder[0] == 0)
        printf("0\n");
    else {
        for (int i = 1; i <= n; ++i) {
            printf("%c", G[topOrder[i]].name);
            if (i != n)
                printf(" ");
        }
    }

    return (0);
}