#include <stdio.h>
#include <stdlib.h>

typedef struct s_node{
    int elem;
    struct s_node *next;
} node;

int M;
node *hashTable;

node *newNode(int k) {
    node *new = (node *)malloc(sizeof(node));
    new->elem = k;
    new->next = NULL;
    return (new);
}

void buildTable() {
    scanf("%d", &M);
    getchar();
    hashTable = (node *)malloc(M * sizeof(node));
    if (!hashTable)
        return;
    for (int i = 0; i < M; ++i) {
        hashTable->elem = -1;
        hashTable->next = NULL;
    }
}

int h(int k) {
    return (k % M);
}

int findElement(int k) {
    int v = h(k), cnt = 0;
    node *p = hashTable + v;

    if (!(p->next))
        return (0);
    while (1) {
        ++cnt;
        p = p->next;
        if (p->elem == k)
            return (cnt);
        else if (p->next == NULL)
            return (0);
    }
}

int removeElement(int k) {
    int v = h(k), cnt = 0;
    node *p = hashTable + v, *tmp;

    while (1) {
        if (!(p->next))
            return (0);
        ++cnt;
        if (p->next->elem == k) {
            tmp = p->next->next;
            free(p->next);
            p->next = tmp;
            return (cnt);
        }
        p = p->next;
    }
}

void insertItem(int k) {
    int v = h(k);
    node *p = hashTable + v;
    node *new = newNode(k);

    if (!(p->next)) {
        p->next = new;
        return ;
    }
    new->next = p->next;
    p->next = new;
}

void printElements() {
    node *p;

    for (int i = 0; i < M; ++i) {
        p = hashTable + i;
        if (!(p->next))
            continue ;
        p = p->next;
        while (p) {
            printf(" %d", p->elem);
            p = p->next;
        }
    }
    printf("\n");
}

int main() {
    int M, k, result;
    char cmd;
    
    buildTable();

    while (1) {
        scanf("%c", &cmd);
        getchar();
        if (cmd == 'p') {
            printElements();
            continue ;
        }
        else if (cmd == 'e')
            break ;
        scanf("%d", &k);
        getchar();
        if (cmd == 'i') {
            insertItem(k);
        }
        else if (cmd == 's') {
            result = findElement(k);
            printf("%d\n", result);
        }
        else if (cmd == 'd') {
            result = removeElement(k);
            printf("%d\n", result);
        }
    }
    return (0);
}