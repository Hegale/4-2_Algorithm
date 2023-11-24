#include <stdio.h>
#include <stdlib.h>

#define FRESH 0
#define VISITED 1
#define TREE 2
#define CROSS 3
#define BACK -1

typedef struct s_edge {
    int a; 
    int b;
    int label;
} t_edge;

// incidence list의 각 노드 구조체
typedef struct s_incidence {
    int edge;
} t_incidence;

typedef struct s_node {
    int nodeNum; // 노드의 id
    int label;
} t_node;

// 편의상 0번을 비우고 1번부터 사용, 인덱스 == 노드번호
t_node *vertices;
t_edge *edges;
int edgeSize = 0;
t_incidence **matrix;


int n, m, s;

// 매트릭스에 엣지 번호 추가
void addIncidence(int edgeNum) {
    int a, b;

    a = edges[edgeNum].a;
    b = edges[edgeNum].b;
    matrix[a][b].edge = edgeNum;
    matrix[b][a].edge = edgeNum;
}

// 새로운 엣지 생성
void newEdge(int a, int b) {
    edges[edgeSize].a = a;
    edges[edgeSize].b = b;
    edges[edgeSize].label = FRESH;
    // 새 엣지를 adjacency matrix에 추가
    addIncidence(edgeSize);
    edgeSize++;
}

void buildGraph() {
    vertices = (t_node *)malloc((n + 1) * sizeof(t_node));
    matrix = (t_incidence **)malloc((n + 1) * sizeof(t_incidence *));
    // 각 노드 생성
    for (int i = 1; i <= n; ++i) {
        vertices[i].nodeNum = i;
        matrix[i] = (t_incidence *)malloc((n + 1) * sizeof(t_incidence));
        for (int j = 1; j <= n; ++j)
            matrix[i][j].edge = -1;
        vertices[i].label = FRESH;
    }
}

void buildEdges() {
    edges = (t_edge *)malloc(m * sizeof(t_edge));
    int a, b;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &a, &b);
        getchar();
        newEdge(a, b);
    }
}

void initListL(int L[][101]) {
    for (int i = 0; i < 101; ++i) {
        L[i][0] = 0; // 리스트가 비어 있음을 나타냄
    }
}

// 해당 L의 끝에 노드 추가
void addLast(int L[], int v) {
    int i = 0;
    while (L[i])
        i++;
    L[i] = v;
    L[i + 1] = 0;
}

// edge e와 연결된 노드 중 v가 아닌 다른 노드를 반환
int opposite(int v, int e) {
    if (edges[e].a == v)
        return edges[e].b;
    return edges[e].a;
}

// matrix를 통한 인접 노드의 방문은 노드 번호의 오름차순으로 진행됨.
void BFS(int v) {
    int i, j, e, w;
    int L[101][101]; // 부족하진않을듯..
    initListL(L);
    addLast(L[0], v);
    vertices[v].label = VISITED;

    printf("%d\n", v); // 방문한 노드 출력

    i = 0;
    // 해당 레벨에서 새 노드를 한 번도 마주치지 못한다면, 반복은 종료된다.
    while (L[i][0]) {
        // j로 L[i]의 각 요소에 접근. 각 요소는 L[i]에 담긴 노드이다.
        for (int j = 0; L[i][j]; ++j) {
            //printf("L[%d][%d] = %d\n", i, j, L[i][j]);
            v = L[i][j];
            // 노드 v에 인접한 모든 간선들의 집합에 대해
            for (int k = 1; k <= n; ++k) {
                e = matrix[v][k].edge;
                // 간선이 존재하지 않으면 지나침
                if (e == -1)
                    continue;
                // 해당 간선을 방문한 적이 없으면, 다음 리스트에 업데이트
                if (edges[e].label == FRESH) {
                    w = opposite(v, e);
                    if (vertices[w].label == FRESH) {
                        edges[e].label = TREE;
                        vertices[w].label = VISITED;
                        printf("%d\n", w); // 방문한 노드 출력
                        addLast(L[i + 1], w);
                    }
                    else
                        edges[e].label = CROSS;
                }
            }
        }
        i++;
    }
}

int main() {

    scanf("%d %d %d", &n, &m, &s);
    getchar();
    // 정점 할당. 정점 인덱스 = 정점번호.
    buildGraph();
    buildEdges();
    BFS(s);

    return (0);
}