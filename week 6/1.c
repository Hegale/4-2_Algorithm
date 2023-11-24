#include <stdio.h>
#include <stdlib.h>

int rFE(int *dic, int k, int l, int r)
{
    int mid, rfe;

    if (l > r)
        return (-10);
    mid = (l + r) / 2;
    if (k == dic[mid])
        return (mid);
    else if (k < dic[mid]){
        rfe = rFE(dic, k, l, mid - 1);
        // 완전히 일치하는 원소가 없다면 결과는 탐색이 멈춘 시점의 mid-1이 된다.
        if (rfe == -10)
            return (mid - 1);
        return (rfe);
    }
    else if (k > dic[mid]){
        rfe = rFE(dic, k, mid + 1, r);
        if (rfe == -10)
            return (mid);
        return (rfe);
    }
    // 이 아래로 내려올 수 없음
    return (-10);
}

int findElement(int *dic, int k, int n)
{
    return (rFE(dic, k, 0, n - 1));
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
    printf(" %d", findElement(dic, k, n));
    free(dic);
}