#include <stdio.h>
#include <stdlib.h>

int sejong(int a, int b, char *yn, int n)
{
    int mid, l, r;

    l = a;
    r = b;
    for (int i = 0; i < n; ++i)
    {
        mid = (l + r) / 2;
        if (yn[i] == 'N'){
            // 왼쪽을 탐색해야 하는 경우, right 값을 조정
            r = mid;
        }
        else if (yn[i] == 'Y'){
            l = mid + 1;
        }
    }
    // 해당하는 인덱스가 존재하지 않는 경우
    return ((l + r) / 2);
}

int main()
{
    int a, b, n;
    char    yn[1000];

    scanf("%d %d %d", &a, &b, &n);
    getchar();
    scanf("%s", yn);
    printf("%d", sejong(a, b, yn, n));
}