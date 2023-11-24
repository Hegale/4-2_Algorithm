#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

// 외부노드: 할당은 되어 있으나 lChild rChild 모두 NULL인 노드
typedef struct s_node {
	struct s_node* lChild;
	struct s_node* rChild;
	struct s_node* parent;
	int					key;
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

// 현재 트리에 키 k를 저장한 새 노드를 삽입
void	insertItem(node* tree, int k) {
	node* w = treeSearch(tree, k);
	// k가 이미 존재하는 노드이면 삽입 X(중복노드 허용X)
	if (isInternal(w))
		return;
	// 위치 w에 키 k를 가지는 새 내부노드를 설정
	else {
		w->key = k;
		w->lChild = newNode();
		w->lChild->parent = w;
		w->rChild = newNode();
		w->rChild->parent = w;
	}
}

// 노드 w의 중위순위 후계자(=오른쪽으로 한 번 이동 후 왼쪽 끝까지 내려가 찾은 내부노드) 반환
node* inOrderSucc(node* w) {
	w = w->rChild;
	if (isExternal(w)) 
		return (NULL); //invalidNodeException
	while (isInternal(w->lChild))
		w = w->lChild;
	return (w);
}

// 쌍둥이(같은 부모를 공유하는 나와 다른 노드)를 반환
node* sibling(node* w) {
	if (w->parent == NULL)
		return (NULL); //invalidNodeException, root는 sibling을 가지지 않는다.
	if (w->parent->lChild == w)
		return (w->parent->rChild);
	else
		return (w->parent->lChild);
}

// 외부노드 z와 그 부모 w를 삭제
node* reduceExternal(node** root, node* z) {
	node* w = z->parent;
	node* zs = sibling(z);
	node* g;

	// w가 루트 노드였을 경우, zs를 루트로 대체함
	if (w->parent == NULL) { // isRoot(w)
		*root = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		// 노드 삭제한 빈자리에 외부노드 쌍둥이 채워주기
		if (w == g->lChild)
			g->lChild = zs;
		else
			g->rChild = zs;
	}
	free(w);
	free(z);
	return (zs);
}

// 현재 트리에서 키 k를 저장한 노드를 삭제 후 원소를 반환
void	removeElement(node** tree, int k) {
	node* z, *y;
	node* w = treeSearch(*tree, k);

	if (isExternal(w)) {
		printf("X\n");
		return;
	}
	// w의 자식 중 외부노드를 z로 설정하는 과정.
	z = w->lChild;
	if (!isExternal(z))
		z = w->rChild;
	// 자식 중 외부노드가 존재하면 reduceExternal로 간단히 해결
	if (isExternal(z))
		reduceExternal(tree, z);
	else {
		// 삭제해야 하는 노드의 자식이 둘다 내부노드일 경우, 후계자로 대체
		y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key;
		reduceExternal(tree, z);
	}
    printf("%d\n", k);
}

void	printTree(node* v) {
	if (isInternal(v)) {
		printf(" %d", v->key);
		printTree(v->lChild);
		printTree(v->rChild);
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
			insertItem(tree, key);
		else if (cmd == 'd')
			removeElement(&tree, key);
		else if (cmd == 's')
			findElement(tree, key);
	}
	return (0);
}