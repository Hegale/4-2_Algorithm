#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 23
#define Q 17
#define ACTIVE 1
#define INACTIVE -1
#define EMPTY 0
#define NoSuchKey -1

typedef struct t_hashtable {
    int status; // ACTIVE, INACTIVE, EMPTY 세 개의 상태를 가진다
    int key; // 키
} s_hashTable;

s_hashTable hashTable[M];

int h(int k) {
    return (k % M);
}

int h_(int k) {
    return (Q - (k % Q));
}

void deactivate(int d) {
    hashTable[d].status = INACTIVE;
}

void activate(int d) {
    hashTable[d].status = ACTIVE;
}

int inactive(int d) {
    return (hashTable[d].status == INACTIVE);
}

int active(int d) {
    return (hashTable[d].status == ACTIVE);
}

int isEmpty(int d) {
    return (hashTable[d].status == EMPTY);
}

int findElement(int k) {
    int v;

    for (int i = 0; i < M; ++i) {
        v = (h(k) + i * h_(k)) % M;
        if (isEmpty(v))
            return (NoSuchKey); // 탐색 실패
        else if (active(v) && k == hashTable[v].key) {
            // 탐색 성공
            printf("%d %d\n", v, k);
            return (hashTable[v].key);
        }
    }
    return (NoSuchKey);
}

void insertItem(int k) {
    int v;

    for (int i = 0; i < M; ++i) {
        v = (h(k) + i * h_(k)) % M;
        // 중복 키가 있는 경우 삽입 자체를 거부한다.
        if (active(v) && k == hashTable[v].key) {
            printf("Duplicate key. Insertion rejected.\n");
            return ;
        }
        // 해당 버켓이 비어 있거나, 그 자리의 키가 삭제된 경우 삽입이 가능함.
        if (isEmpty(v) || inactive(v)) {
            hashTable[v].key = k;
            activate(v);
            return ;
        }
    }
    // 해시테이블이 만원일 경우
    printf("Hashtable is full. Insertion rejected.\n");
}

int removeElement(int k) {
    int v;

    for (int i = 0; i < M; ++i) {
        v = (h(k) + i * h_(k)) % M;
        // 비어 있다면 해당 키가 삽입된 적 없는 것이므로
        if (isEmpty(v))
            return (NoSuchKey);
        else if (active(v) && k == hashTable[v].key) {
            deactivate(v);
            return (k);
        }
    }
    return (NoSuchKey);
}

void printItems() {
    printf("====================================[ HashTable Status ]====================================\n");
    for (int i = 0; i < M; ++i)
        printf("%4d", i);
    printf("\n");
    // 비어 있거나 비활성화된 버켓의 경우 .을 대신 출력.
    for (int i = 0; i < M; ++i) {
        if (active(i))
            printf("%4d", hashTable[i].key);
        else
            printf("   .");
    }
    printf("\n");
}

void buildTable() {
    for (int i = 0; i < M; ++i) {
        hashTable[i].status = EMPTY;
        hashTable[i].key = -1;
    }
    // 프로그래밍 요구사항: 원만한 실행을 위해 20개 정도의 항목으로
    // 해시테이블을 초기화한 후, 명령코드를 입력받기 시작한다.
    /*
    srand(time(NULL));
    for (int i = 0; i < 20; ++i)
        insertItem(rand() % 100);
        */
}

int main() {
    int k, result;
    char cmd;
    
    // 심층문제 요구사항대로, 20개의 항목으로 해시테이블 초기화
    buildTable();

    while (1) {
        scanf("%c", &cmd);
        getchar();
        // 출력 시 추가 k 입력 필요 없음
        if (cmd == 'p') {
            printItems();
            continue ;
        }
        else if (cmd == 'q') {
            break ;
        }
        scanf("%d", &k);
        getchar();
        // 각 명령에 맞는 동작을 시행한 후 결과를 출력한다.
        if (cmd == 'i') {
            insertItem(k);
        }
        else if (cmd == 'f') {
            result = findElement(k);
            if (result != NoSuchKey)
                printf("Key found! key = %d\n", result);
            else 
                printf("NoSuchKey\n");
        }
        else if (cmd == 'r') {
            result = removeElement(k);
            if (result != NoSuchKey)
                printf("Key deleted! key = %d\n", result);
            else 
                printf("NoSuchKey\n");
        }
    }
    return (0);
}