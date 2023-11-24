#include <stdio.h>
#include <stdlib.h>

#define FRESH 0
#define VISITED 1
#define TREE 2
#define BACK -1

typedef struct s_edge {
    int a; 
    int b;
    int label;
} t_edge;

// incidence list의 각 노드 구조체
typedef struct s_incidence {
    int edge;
    struct s_incidence *next;
} t_incidence;

typedef struct s_node {
    int nodeNum; // 노드의 id
    int label;
    t_incidence *head; // 첫 노드는 아무것도 없는 헤드노드
} t_node;

// 편의상 0번을 비우고 1번부터 사용, 인덱스 == 노드번호
t_node *vertices;
t_edge *edges;
int edgeSize = 0;

// 인접 노드의 node Number 순으로 삽입됨
void addIncidence(int node, int edgeNum) {
    int neighbor, edge_neighbor;
    t_incidence *p = vertices[node].head, *tmp;
    t_incidence *new = (t_incidence *)malloc(sizeof(t_incidence));

    new->edge = edgeNum;
    new->next = NULL;

    while (p->next) {
        // 이웃의 node num 정하기.
        neighbor = edges[p->next->edge].a;
        if (edges[p->next->edge].b != node)
            neighbor = edges[p->next->edge].b;
        edge_neighbor = edges[edgeNum].a;
        if (edges[edgeNum].b != node)
            edge_neighbor = edges[edgeNum].b;
        // 나보다 큰 연결노드를 발견하면, 그 연결노드 직전에 삽입
        if (neighbor > edge_neighbor) {
            new->next = p->next;
            p->next = new;
            return ;
        }
        p = p->next;
    }
    // 끝까지 삽입지점을 찾지 못했다면, 노드번호가 가장 크다는 의미이므로 마지막 삽입
    p->next = new;
}

// 새로운 엣지 생성
void newEdge(int a, int b) {
    edges[edgeSize].a = a;
    edges[edgeSize].b = b;
    edges[edgeSize].label = FRESH;
    // 새 엣지를 부착 노드들 내부의 incidence 리스트에 추가
    addIncidence(a, edgeSize);
    if (a != b)
        addIncidence(b, edgeSize);
    edgeSize++;
}

void buildGraph(int n) {
    vertices = (t_node *)malloc(n * sizeof(t_node) + 1);
    // 각 노드 생성
    for (int i = 1; i <= n; ++i) {
        vertices[i].nodeNum = i;
        vertices[i].head = (t_incidence *)malloc(sizeof(t_incidence));
        vertices[i].head->next = NULL;
        vertices[i].label = FRESH;
    }
}

void buildEdges(int m) {
    edges = (t_edge *)malloc(m * sizeof(t_edge));
    int a, b;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &a, &b);
        getchar();
        newEdge(a, b);
    }
}

// edge e와 연결된 노드 중 v가 아닌 다른 노드를 반환
int opposite(int v, int e) {
    if (edges[e].a == v)
        return edges[e].b;
    return edges[e].a;
}

// edge와 vertice의 label을 FRESH로 초기화하는 작업은 각 정점 및 간선 생성 시 완료함
void DFS(int v) {
    int w;
    vertices[v].label = VISITED;
    printf("%d\n", v); // 방문 노드를 출력

    // 노드 u에 인접한 모든 간선들에 대해 반복. incidence lists는 오름차순 정렬이 전제돼 있음.
    t_incidence *p = vertices[v].head->next;
    while (p) {
        // 해당 엣지를 방문한 적이 없다면.. (p-edge = e)
        if (edges[p->edge].label == FRESH) {
            // 그 엣지의 v가 아닌 다른 노드를 w로 설정
            w = opposite(v, p->edge);
            // w에 방문한 적 없다면, 해당 간선을 트리 간선으로 설정.
            if (vertices[w].label == FRESH) {
                edges[p->edge].label = TREE;
                DFS(w);
            }
            else {
                edges[p->edge].label = BACK;
            }
        }
        p = p->next;
    }
}

int main() {
    int n, m, s;

    scanf("%d %d %d", &n, &m, &s);
    getchar();
    // 정점 할당. 정점 인덱스 = 정점번호.
    buildGraph(n);
    buildEdges(m);
    DFS(s);

    return (0);
}