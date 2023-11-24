#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void    swap(int **list, int a, int b)
{
    int tmp;

    tmp = (*list)[a];
    (*list)[a] = (*list)[b];
    (*list)[b] = tmp;
}

void    selection_sort(int **list, int n)
{
    int *p;
    int max;

    p = *list;
    for (int i = n - 1; i >= 0; --i)
    {
        max = i;
        for (int j = 0; j < i; ++j)
        {
            if (p[max] < p[j])
                max = j;
        }
        if (max != i)
            swap(list, i, max);
    }

}

void    insertion_sort(int **list, int n)
{
    int *p;
    int key, j;

    p = *list;
    for (int i = 1; i < n; ++i)
    {
        key = p[i];
        j = i - 1;
        while (j >= 0 && key < p[j])
        {
            p[j + 1] = p[j];
            j--;
        }
        p[j + 1] = key;
    }
}

void get_A_time(int **A)
{
    LARGE_INTEGER start, end, diff, ticksPerSec;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceFrequency(&start);
    selection_sort(A, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("A time : %12f sec\n", ((double)diff.QuadPart/(double)ticksPerSec.QuadPart));
}

void get_B_time(int **B)
{
    LARGE_INTEGER start, end, diff, ticksPerSec;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceFrequency(&start);
    insertion_sort(B, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("B time : %12f sec\n", ((double)diff.QuadPart/(double)ticksPerSec.QuadPart));
}

int main()
{
    int n;
    int *A, *B;
    int *RA, *RB;

    scanf("%d", &n);
    A = (int *)malloc(n * sizeof(int));
    B = (int *)malloc(n * sizeof(int));
    RA = (int *)malloc(n * sizeof(int));
    RB = (int *)malloc(n * sizeof(int));
    if (!A || !B || !RA || !RB)
        return (-1);
    //랜덤시행
    srand(time(NULL));
    for (int i = 0; i < n; ++i){
        A[i] = rand();
        B[i] = A[i];
    }

    // ===============A===============
    printf("testing A\n");
    get_A_time(&A);
    get_B_time(&B);

    // ===============B===============
    printf("\ntesting B\n");
    get_A_time(&A);
    get_B_time(&B);

    // ===============C===============

    for (int i = 0; i < n; ++i){
        RA[i] = A[n - i - 1];
        RB[i] = B[n - i - 1];
    }

    printf("testing C\n");
    get_A_time(&A);
    get_B_time(&B);
    
    free(A);
    free(B);
    free(RA);
    free(RB);

    return (0);
}