#include <stdio.h>
#include <stdlib.h>

int M, n, q;
int *hashTable;

void buildTable() {
    scanf("%d %d %d", &M, &n, &q);
    getchar();
    hashTable = (int *)malloc(M * sizeof(int));
    if (!hashTable)
        return;
    for (int i = 0; i < M; ++i) {
        hashTable[i] = 0;
    }
}

int h(int k) {
    return (k % M);
}

int h_(int k) {
    return (q - (k % q));
}

void findElement(int k) {
    int v;

    for (int i = 0; i < M; ++i) {
        v = (h(k) + i * h_(k)) % M;
        if (hashTable[v] == 0)
            break ;
        if (hashTable[v] == k) {
            // 탐색 성공
            printf("%d %d\n", v, k);
            return ;
        }
    }
    // 탐색 실패
    printf("-1\n");
}

void insertItem(int k) {
    int v;

    for (int i = 0; i < M; ++i) {
        v = (h(k) + i * h_(k)) % M;
        if (hashTable[v] == 0) {
            hashTable[v] = k;
            // 충돌 횟수만큼 C 출력
            for (int j = 0; j < i; ++j)
                printf("C");
            // 주소 출력
            printf("%d\n", v);
            return ;
        }
    }
}

void printItems() {
    for (int i = 0; i < M; ++i)
        printf(" %d", hashTable[i]);
    printf("\n");
}

int main() {
    int M, k, result;
    char cmd;
    
    buildTable();

    while (1) {
        scanf("%c", &cmd);
        getchar();
        if (cmd == 'e' || cmd == 'p') {
            printItems();
            if (cmd == 'e')
                break ;
            continue ;
        }
        scanf("%d", &k);
        getchar();
        if (cmd == 'i') {
            insertItem(k);
        }
        else if (cmd == 's') {
            findElement(k);
        }
    }
    return (0);
}