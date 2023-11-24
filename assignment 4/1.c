#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef int (*func)(int, int, int); // 함수 포인터 선언

int MAX = 30;
int *A;
int *H;

// 분할통치 역방향 
int aritelDC(int n, int s, int d) {
    int mincost, cost;

    // 이미 도착했으면 반환
    if (s == d)
        return 0;
    mincost = INT_MAX;
    // 다음 칸부터 목적지까지
    for (int k = s + 1; k <= d; ++k) {
        // 비용 = k까지의 항공료 + k의 숙박료 + k~d까지의 최저항공료
        cost = A[k - s] + H[k] + aritelDC(n, k, d);
        mincost = MIN(mincost, cost);
    }
    return mincost;
}

// 동적 역방향 해결
int aritelDP(int n, int s, int d) {
    int cost;
    int *m = (int *)malloc(n * sizeof(int));

    m[d] = 0;
    for (int i = d - 1; i >= s; --i) {
        m[i] = INT_MAX;
        for (int k = i + 1; k <= d; ++k) {
            // 비용 = s부터 k까지의 항공료 + k의 숙박료 + k부터 목적지까지의 최소비용
            cost = A[k - i] + H[k] + m[k];
            m[i] = MIN(m[i], cost);
        }
        printf("i = %d, m[i] = %d\n", i, m[i]);
    }
    return m[0];
}

void initGlobal() {
    A = (int *)malloc(MAX * sizeof(int));
    H = (int *)malloc(MAX * sizeof(int));
}

int main() {
    int n, s, d, mincost;

    initGlobal();

    A[0] = 0;
    A[1] = 1;
    for (int i = 2; i < MAX; ++i)
        A[i] = A[i - 1] + A[i - 1] % 5 + 3;
    H[0] = 0;
    H[1] = 1;
    for (int i = 2; i < MAX; ++i)
        H[i] = (H[i - 1] + i) % 9 + 1;
    printf("n\ts\td\tmincost\t\tversion\t\tcputime\n");

    n = 6;
    
    int sList[3] = {0, 2, 2};
    int dList[3] = {4, 5, 4};
    for (int i = 0; i < 3; ++i) {
        mincost = aritelDC(n, sList[i], dList[i]);
        //printCPUTIME;
        mincost = aritelDP(n, sList[i], dList[i]);
        //printCPUTIME
    }

    n = MAX;
    s = 1;
    d = n - 2;
    aritelDC(n, s, d);
    //printCPUTIME;
    aritelDP(n, s, d);
    //printCPUTIME;

}
