#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

// 외부노드: 할당은 되어 있으나 lChild rChild 모두 NULL인 노드
typedef struct s_node {
	struct s_node* lChild;
	struct s_node* rChild;
	struct s_node* parent;
	int	key;
    int height;
} node;

// 노드 w가 외부노드인지 여부를 반환
int isExternal(node* w) {
	if (w->lChild == NULL && w->rChild == NULL)
		return (1);
	return (0);
}

int	isInternal(node* w) {
	if (w->lChild != NULL || w->rChild != NULL)
		return (1);
	return (0);
}

void	printTree(node* v) {
	if (isInternal(v)) {
		printf(" %d", v->key);
		printTree(v->lChild);
		printTree(v->rChild);
	}
}

// 현재 트리에서 키 k를 저장한 노드를 찾아 그 노드에 저장된 원소를 '출력'하는 것으로 변경
void	findElement(node* v, int k) {
	if (isExternal(v)) {
		printf("X\n");
		return;
	}
	if (v->key == k)
		printf("%d\n", k);
	else if (k < v->key)
		return (findElement(v->lChild, k));
	else if (k > v->key)
		return (findElement(v->rChild, k));
}

// 외부노드를 하나 생성함
node* newNode() {
	node* new = (node*)malloc(sizeof(node));
	if (!new)
		return (NULL);
	new->lChild = NULL;
	new->rChild = NULL;
	new->parent = NULL;
    new->height = 0;
	return (new);
}

// 현재 트리에서 키 k를 저장한 노드를 반환. 해당 노드가 없을 경우, 있었어야 할 위치(외부노드) 반환
node* treeSearch(node* v, int k) {
	if (isExternal(v))
		return (v);
	if (v->key == k)
		return (v);
	else if (k < v->key)
		return (treeSearch(v->lChild, k));
	else
		return (treeSearch(v->rChild, k));
}

void    expandExternal(node *w){
    node *l, *r;

    l = newNode();
    r = newNode();
    l->parent = w;
    l->height = 0;
    r->parent = w;
    r->height = 0;
    w->lChild = l;
    w->rChild = r;
    w->height = 1;
}

int updateHeight(node *w){
    int h;
    
    h = w->lChild->height;
    if (h < w->rChild->height)
        h = w->rChild->height;
    if ((h + 1)!= w->height){
        w->height = h + 1;
        return (1);
    }
    return (0);
}

node    *restructure(node **root, node *x, node *y, node *z){
    node *T0, *T1, *T2, *T3;
    node *a, *b, *c;

    // 높이가 가장 낮은 것부터 x,y,z였던 노드들을 중위순회 a, b, c로 재설정.
    if (z->key < y->key && y->key < x->key){
        //printf("RR Case\n");
        a = z;
        b = y;
        c = x;
        T0 = a->lChild;
        T1 = b->lChild;
        T2 = c->lChild;
        T3 = c->rChild;
    }
    else if (x->key < y->key && y->key < z->key){
        //printf("LL Case\n");
        a = x;
        b = y;
        c = z;
        T0 = a->lChild;
        T1 = a->rChild;
        T2 = b->rChild;
        T3 = c->rChild;
    }
    else if (z->key < x->key && x->key < y->key){
        //printf("RL Case\n");
        a = z;
        b = x;
        c = y;
        T0 = a->lChild;
        T1 = b->lChild;
        T2 = b->rChild;
        T3 = c->rChild;
    }
    else { // 좌회전 후 우회전, LR Case
        //printf("LR Case\n");
        a = y;
        b = x;
        c = z;
        T0 = a->lChild;
        T1 = b->lChild;
        T2 = b->rChild;
        T3 = c->rChild;
    }

    //printf("height of T0, T1, T2, T3 = %d, %d, %d, %d\n", T0->height, T1->height, T2->height, T3->height);
    // z의 윗노드와 b를 연결
    if (z->parent == NULL){
        *root = b;
        b->parent = NULL;
    }
    else if (z->parent->lChild == z){
        z->parent->lChild = b;
        b->parent = z->parent;
    }
    else{
        z->parent->rChild = b;
        b->parent = z->parent;
    }

    // T0와 T1을 a의 서브트리로 만든다.
    a->lChild = T0;
    a->rChild = T1;
    T0->parent = a;
    T1->parent = a;
    updateHeight(a);

    // T2와 T3을 C의 서브트리로 만든다.
    c->lChild = T2;
    c->rChild = T3;
    T2->parent = c;
    T3->parent = c;
    updateHeight(c);

    //a와 c를 b의 자식으로 만든다.
    b->lChild = a;
    b->rChild = c;
    a->parent = b;
    c->parent = b;
    updateHeight(b);
    return (b);
}

int isBalanced(node *w){
    int t = w->lChild->height - w->rChild->height;
    if (t < 0)
        t = -t;
    return (t < 2);
}

void    searchAndFixAfterInsertion(node **root, node *w){
    node *x, *y, *z;

    w->lChild->height = 0;
    w->rChild->height = 0;
    w->height = 1;
    if (w->parent == NULL)
        return ;
    z = w->parent;
    // 삽입노드 w의 부모부터 높이를 갱신 + 균형이 맞는지를 확인하며 올라감
    while (updateHeight(z) & isBalanced(z)){
        if (z->parent == NULL)
            return ;
        z = z->parent;
    }
    if (isBalanced(z))
        return ; // 수정사항 없으면 return

    // 밸런스가 깨진 노드 (z)의 더 큰 부트리를 y로 설정
    // 부트리가 크다 = 높이가 높다 = 균형이 깨진 원인이라는 소리
    if (z->lChild->height > z->rChild->height)
        y = z->lChild;
    else
        y = z->rChild;
    //마찬가지로 y의 더 큰 부트리를 가진 자식을 x로 설정
    if (y->lChild->height > y->rChild->height)
        x = y->lChild;
    else
        x = y->rChild;
    //printf("height: xl %d, xr %d, yl %d, yr %d, zl %d, zr %d\n", x->lChild->height, x->rChild->height,\
    y->lChild->height, y->rChild->height, z->lChild->height, z->rChild->height);
    restructure(root, x, y, z);
    return ;
}

// 현재 트리에 키 k를 저장한 새 노드를 삽입
void	insertItem(node** tree, int k) {
	node* w = treeSearch(*tree, k);
	// k가 이미 존재하는 노드이면 삽입 X(중복노드 허용X)
	if (isInternal(w))
		return;
	// 위치 w에 키 k를 가지는 새 내부노드를 설정
	else {
		w->key = k;
		expandExternal(w);
        searchAndFixAfterInsertion(tree, w);
	}
}

int main() {
	char	cmd;
	int	key;
	node* tree = newNode();

	while (1) {
		scanf("%c", &cmd);
		getchar();
		// q 입력 시 종료
		if (cmd == 'q')
			break;
		if (cmd == 'p') {
			printTree(tree);
			printf("\n");
			continue;
		}
		scanf("%d", &key);
		getchar();
		if (cmd == 'i')
			insertItem(&tree, key);
		else if (cmd == 's')
			findElement(tree, key);
	}
	return (0);
}