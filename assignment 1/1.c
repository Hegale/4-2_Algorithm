#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SWAP(a, b) {int tmp=L[a]; L[a]=L[b]; L[b]=tmp;}


void	downHeap(int *L, int n, int i, int last);

void buildHeap(int *L, int n)
{
    int i = n / 2;

	for ( ; i >= 1; --i)
		downHeap(L, n, i, n);
}

void    printList(int *list, int n)
{
    for (int i = 1; i <= n; ++i)
        printf("%d ", list[i]);
    printf("\n");
}

int *buildList(int n, int min, int max)
{
    int *list;

    list = (int *)malloc((n + 1) * (int)sizeof(int));
    if (!list)
        return (NULL);
    srand(time(NULL));
    for (int i = 1; i <= n; ++i){
        list[i] = (rand() % (max - min + 1) + min);
    }
    return (list);
}

void	downHeap(int *L, int n, int i, int last){
	int bigger, left, right;

    left = 2 * i;
    right = 2 * i + 1;
    // 자식이 없는 경우
    if (left > last)
        return ;
	bigger = left;
	if (right <= last && (L[right] > L[bigger]))
		bigger = right;
	if (L[i] >= L[bigger])
		return ;
	SWAP(i, bigger);
	downHeap(L, n, bigger, last);
}

void inPlaceHeapSort(int *L, int n)
{
    buildHeap(L, n);

    for (int i = n; i >= 2; i--)
    {
        SWAP(1, i);
        downHeap(L, n, 1, i - 1);
    }
}

// 반복 정렬을 피하기 위해 매번 배열 복사하여 사용
int findKthSmallest(int *L, int n, int k)
{
    int output;
    int *H = (int *)malloc((n + 1) * (int)sizeof(int));

    for (int i = 1; i <= n; ++i)
        H[i] = L[i];
    inPlaceHeapSort(H, n);
    output = H[k];
    free(H);
    return (output);
}


int main()
{
    int *L;
    int output[5], karray[4];
    LARGE_INTEGER start, end, diff, ticksPerSec;

    L = buildList(10, 1, 100);
    printList(L, 10);
    //k = 1, 2, 3일 때 3회 호출
    for (int i = 1; i <= 3; ++i)
        output[i] = findKthSmallest(L, 10, i);
    printf("%d %d %d\n", output[1], output[2], output[3]);
    free(L);

    // k = 1, 100, 99900, 99999일 때 4회 호출
    L = buildList(100000, 1, 1000000);
    karray[0] = 1;
    karray[1] = 100;
    karray[2] = 99900;
    karray[3] = 99999;
    // 매회 시간 측정하여 출력
    for (int i = 0; i <= 3; ++i){
        QueryPerformanceFrequency(&ticksPerSec);
        QueryPerformanceFrequency(&start);
        output[i] = findKthSmallest(L, 100000, karray[i]);
        QueryPerformanceCounter(&end);
        diff.QuadPart = end.QuadPart - start.QuadPart;
        printf("e = %d, time = %12f\n", output[i], ((double)diff.QuadPart/(double)ticksPerSec.QuadPart));
    }
    free(L);

    return (0);
}
