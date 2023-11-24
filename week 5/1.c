#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(n1, n2) {int tmp=n1; n1=n2; n2=tmp;}

void    printList(int *list, int l, int r)
{
    for (int i = l; i <= r; ++i)
        printf(" %d", list[i]);
    printf("\n");
}

// 나눈 인덱스 a, b를 저장하기 위해 포인터를 받아 옴. x = 피봇의 인덱스
void    inPlacePartition(int *list, int l, int r, int k, int *a, int *b)
{
    int p = list[k];
    int i, j, pivot_count;

    SWAP(list[k], list[r]);
    pivot_count = 1;
    i = l;
    j = r - 1;
    while (i <= j)
    {
        while (i <= j && list[i] < p)
            i++;
        // pivot과 같은 값 발생 시 추가로 끝으로 미룸. j값 초기화
        if (i <= j && list[i] == p){
            SWAP(list[r - pivot_count], list[i]);
            pivot_count++;
            // j가 아직 끝일 경우, 피봇 직전으로 초기화
            if (j == r - pivot_count + 1)
                j--;
            continue;
        }
        while (j >= i && list[j] > p)
            j--;
        if (j >= i && list[j] == p){
            SWAP(list[r - pivot_count], list[j]);
            pivot_count++;
            if (j == r - pivot_count + 1)
                j--;
            continue;
        }
        if (i < j)
            SWAP(list[i], list[j]);
        //printf("    in partition =");
        //printList(list, l, r);
    }
    *a = i;
    *b = i + pivot_count - 1;
    //printf("    pivotcount = %d, i = %d, j = %d, a = %d, b = %d\n", pivot_count, i, j, *a, *b);
    // 끝에 몰아 뒀던 pivot을 다시 가운데에 끼워넣기. 
    for (int z = 0; z < pivot_count; z++)
    {
        SWAP(list[r - z], list[i]);
        i++;
    }
    //printf("    partition end =");
    //printList(list, l, r);
}

// l = 리스트의 첫 인덱스, r = 마지막 인덱스, k = 피봇의 인덱스
void    inPlaceQuickSort(int *list, int l, int r)
{
    int k, a, b;

    if (l >= r)
        return ;
    // 랜덤한 피봇 생성
    k = rand() % (r - l + 1) + l;
    //printf("k = %d, l = %d, r = %d\n", k, l, r);
    inPlacePartition(list, l, r, k, &a, &b);
    //printList(list, l, r);
    inPlaceQuickSort(list, l, a - 1);
    inPlaceQuickSort(list, b + 1, r);
}

int main()
{
    int n;
    int *list;

    srand(time(NULL));
    scanf("%d", &n);
    list = (int *)malloc(n * sizeof(int));
    if (!list)
        return (-1);
    for (int i = 0; i < n; ++i)
        scanf("%d", list + i);
    inPlaceQuickSort(list, 0, n - 1);
    printList(list, 0, n - 1);
    free(list);
}
