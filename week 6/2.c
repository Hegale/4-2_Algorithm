#include <stdio.h>
#include <stdlib.h>

int iFE(int *dic, int k, int n)
{
    int mid, l, r;

    l = 0;
    r = n - 1;
    while (1)
    {
        mid = (l + r) / 2;
        if (k == dic[mid])
            return (mid);
        else if (k < dic[mid]){
            // 왼쪽을 탐색해야 하는 경우, right 값을 조정
            r = mid - 1;
            if (l > r)
                return (mid);
        }
        else if (k > dic[mid]){
            l = mid + 1;
            if (l > r)
                return (mid + 1);
        }
    }
    // 해당하는 인덱스가 존재하지 않는 경우
    return (-1);
}

int main()
{
    int n, k;
    int *dic;

    scanf("%d %d", &n, &k);
    dic = (int *)malloc(n * sizeof(int));
    if (!dic)
        return (-1);
    for (int i = 0; i < n; ++i)
        scanf("%d", dic + i);
    printf(" %d", iFE(dic, k, n));
    free(dic);
}