#include <stdio.h>
#include <stdlib.h>

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
    insertion_sort(&list, n);
    for (int i = 0; i < n; ++i)
        printf(" %d", list[i]);
    free(list);

    return (0);
}
