#include <stdio.h>
#include <stdlib.h>

/*
    정점은 고정, node number가 1-6이므로 구조체의 배열로 구현
    각 정점과 연결된 간선을 나타내는 incidence lists는 연결리스트로 구현
    + 내부에 간선을 향하는 포인터를 만들어 구현
    간선도 배열로 구현
*/

typedef struct s_edge {
    int a; 
    int b;
    int weight;
} t_edge;

typedef struct s_incidence {
    int edge;
    struct s_incidence *next;
} t_incidence;

typedef struct s_node {
    int nodeNum;
    t_incidence *head; // 첫 노드는 아무것도 없는 헤드노드
} t_node;

// 편의상 0번을 비우고 1번부터 사용, 인덱스 == 노드번호
t_node vertices[7];
t_edge edges[21];
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
void newEdge(int a, int b, int weight) {
    if (weight == 0)
        return ;
    edges[edgeSize].a = a;
    edges[edgeSize].b = b;
    edges[edgeSize].weight = weight;
    // 새 엣지를 부착 노드들 내부의 incidence 리스트에 추가
    addIncidence(a, edgeSize);
    if (a != b)
        addIncidence(b, edgeSize);
    edgeSize++;
}

// 그래프 생성
void buildGraph() {
    // 각 노드 생성
    for (int i = 1; i < 7; ++i) {
        vertices[i].nodeNum = i;
        vertices[i].head = (t_incidence *)malloc(sizeof(t_incidence));
        vertices[i].head->next = NULL;
    }
    // 새 엣지 생성, 새 엣지를 엣지 리스트에 추가,
    // 새 엣지를 연결된 노드들의 incidence list에 추가
    newEdge(1, 2, 1);
    newEdge(1, 3, 1);
    newEdge(1, 4, 1);
    newEdge(1, 6, 2);
    newEdge(2, 3, 1);
    newEdge(3, 5, 4);
    newEdge(5, 5, 4);
    newEdge(5, 6, 3);
}

// a 명령어, 인접 노드와 간선 가중치 출력
void printNeighbor(int nodeNum) {
    // 그래프에 정점 a가 존재하지 않을 때
    if (nodeNum < 1 || nodeNum > 6) {
        printf("-1\n");
        return ;
    }
    t_incidence *p = vertices[nodeNum].head;
    int neighbor, edgeNum;

    p = p->next;
    while (p) {
        edgeNum = p->edge;
        neighbor = edges[edgeNum].a;
        if (edges[edgeNum].b != nodeNum)
            neighbor = edges[edgeNum].b;
        printf(" %d %d", neighbor, edges[edgeNum].weight);
        p = p->next;
    }
    printf("\n");
}

// a노드의 incidence lists에서 b와 연결된 엣지를 삭제
void deleteIncidence(int a, int b) {
    t_incidence *p, *tmp;

    p = vertices[a].head;
    
    // 중복은 별도 처리
    if (a == b) {
        while (p->next) {
            if (edges[p->next->edge].a == b && edges[p->next->edge].b == b) 
                break;
            p = p->next;
        }
    }
    else {
        while (p->next) {
            if (edges[p->next->edge].a == b || edges[p->next->edge].b == b)
                break;
            p = p->next;
        }
    }
    tmp = p->next;
    p->next = p->next->next;
    free(tmp);
}

void updateIncidence(int edgeNum) {
    t_incidence *p;

    // 모든 노드에 대해 edges 인덱스 갱신
    for (int i = 1; i < 7; ++i) {
        p = vertices[i].head;
        p = p->next;
        while (p) {
            if (p->edge > edgeNum)
                p->edge -= 1;
            p = p->next;
        }
    }
}

void deleteEdge(int edgeNum) {
    deleteIncidence(edges[edgeNum].a, edges[edgeNum].b);
    if (edges[edgeNum].a != edges[edgeNum].b)
        deleteIncidence(edges[edgeNum].b, edges[edgeNum].a);
    for (int i = edgeNum; i < edgeSize - 1; ++i) {
        // 구조체 단순대입 됐었나??
        edges[i].a = edges[i + 1].a;
        edges[i].b = edges[i + 1].b;
        edges[i].weight = edges[i + 1].weight;
    }
    updateIncidence(edgeNum);
    edgeSize--;
}

// m 명령어 처리, 루프 간선 고려해야함
void editEdge(int a, int b, int weight) {
    if (a < 1 || a > 6 || b < 1 || b > 6) {
        printf("-1\n");
        return ;
    }
    for (int i = 0; i < edgeSize; ++i) {
        // 해당 간선을 찾았을 때
        if ((edges[i].a == a && edges[i].b == b) ||
         (edges[i].a == b && edges[i].b == a)) {
            if (weight == 0)
                deleteEdge(i);
            else
                edges[i].weight = weight;
            return ;
        }
    }
    // 해당하는 간선이 존재하지 않을 때, 새 간선 추가
    newEdge(a, b, weight);
}

int main() {
    char cmd;
    int nodeNum, m, weight, a, b;

    buildGraph();
    while (1) {
        scanf("%c", &cmd);
        getchar();
        if (cmd == 'a') {
            scanf("%d", &nodeNum);
            getchar();
            printNeighbor(nodeNum);
        }
        else if (cmd == 'm') {
            scanf("%d %d %d", &a, &b, &m);
            getchar();
            editEdge(a, b, m);
        }
        else if (cmd == 'q')
            break ;
    }   
}