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
} t_incidence;

typedef struct s_node {
    int nodeNum;
} t_node;

// 편의상 0번을 비우고 1번부터 사용, 인덱스 == 노드번호
t_node vertices[7];
t_edge edges[21];
int edgeSize = 0;
t_incidence matrix[7][7];

// 매트릭스에 엣지 번호 추가
void addIncidence(int edgeNum) {
    int a, b;

    a = edges[edgeNum].a;
    b = edges[edgeNum].b;
    matrix[a][b].edge = edgeNum;
    matrix[b][a].edge = edgeNum;
}

// 새로운 엣지 생성
void newEdge(int a, int b, int weight) {
    if (weight == 0)
        return ;
    edges[edgeSize].a = a;
    edges[edgeSize].b = b;
    edges[edgeSize].weight = weight;
    // 새 엣지를 adjacency matrix에 추가
    addIncidence(edgeSize);
    edgeSize++;
}

// 그래프 생성
void buildGraph() {
    // 각 노드 생성
    for (int i = 1; i < 7; ++i) {
        vertices[i].nodeNum = i;
        for (int j = 1; j < 7; ++j)
            matrix[i][j].edge = -1;
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
    int edgeNum;

    for (int i = 1; i < 7; ++i) {
        edgeNum = matrix[nodeNum][i].edge;
        if (edgeNum == -1)
            continue;
        printf(" %d %d", i, edges[edgeNum].weight);
    }
    printf("\n");
}

// a노드의 incidence lists에서 b와 연결된 엣지를 삭제
void deleteIncidence(int a, int b) {
    matrix[a][b].edge = -1;
    matrix[b][a].edge = -1;
}

void updateMatrix(int delEdge) {
    for (int i = 1; i < 7; ++i) {
        for (int j = 1; j < 7; ++j) {
            if (matrix[i][j].edge > delEdge){
                matrix[i][j].edge -= 1;
            }
        }
    }
}

void deleteEdge(int edgeNum) {
    deleteIncidence(edges[edgeNum].a, edges[edgeNum].b);
    updateMatrix(edgeNum);
    for (int i = edgeNum; i < edgeSize - 1; ++i) {
        // 구조체 단순대입 됐었나??
        edges[i].a = edges[i + 1].a;
        edges[i].b = edges[i + 1].b;
        edges[i].weight = edges[i + 1].weight;
    }
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
        /*
        else if (cmd == 'p') {
            for (int i = 1; i < 7; ++i) {
                for (int j = 1; j < 7; ++j) 
                    printf("%d ", matrix[i][j].edge);
                printf("\n");
            }
        }
        */
    }   
}