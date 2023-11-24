#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    int n;
    int *list;

    scanf("%d", &n);
    list = (int *)malloc(sizeof(int) * n);
    if (!list)
        return (-1);
    for (int i = 0; i < n; ++i)
        scanf("%d", list + i);
    selection_sort(&list, n);
    for (int i = 0; i < n; ++i)
        printf(" %d", list[i]);
    free(list);

    return (0);
}