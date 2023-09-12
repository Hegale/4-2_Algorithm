#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
    struct s_node   *left;
    struct s_node   *right;
    int num;
} t_node;

void    create_tree(t_node **root, int num, int l, int r)
{
    int scan_n, scan_l, scan_r;

    *root = (t_node *)malloc(sizeof(t_node));
    if (*root == 0)
        return ;
    (*root)->num = num;
    // 왼쪽 자식이 존재할 때
    if (l)
    {
        scanf("%d %d %d", &scan_n, &scan_l, &scan_r);
        create_tree(&((*root)->left), scan_n, scan_l, scan_r);
    }
    else
        (*root)->left = 0;
    if (r)
    {
        scanf("%d %d %d", &scan_n, &scan_l, &scan_r);
        create_tree(&((*root)->right), scan_n, scan_l, scan_r);
    }
    else
        (*root)->right = 0;
}

void print_node(t_node *node, char *str)
{
    printf(" %d", node->num);
    if (*str == 0)
        return ;
    if (*str == 'L')
        print_node(node->left, str + 1);
    if (*str == 'R')
        print_node(node->right, str + 1);
}

// print를 추가하여 순회 출력 함수로도 이용 가능
void    clear_all(t_node **head)
{
    if (!(*head))
        return ;
    //printf(" %d", head->num);
    if ((*head)->left)
        clear_all(&((*head)->left));
    if ((*head)->right)
        clear_all(&((*head)->right));
    free(*head);
}

int main()
{
    int n, s, num, l, r;
    char str[101];
    t_node  *root, *p;

    scanf("%d", &n);
    scanf("%d %d %d", &num, &l, &r);
    create_tree(&root, num, l, r);
    scanf("%d", &s);
    for (int i = 0; i < s; ++i)
    {
        scanf("%s", str);
        p = root;
        print_node(p, str);
        printf("\n");
    }
    clear_all(&root);
    return (0);
}
