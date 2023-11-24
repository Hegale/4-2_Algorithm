#include <stdio.h>

#define SWAP(a, b) {int tmp=H[a]; H[a]=H[b]; H[b]=tmp;}

#define MAX_SIZE 100

int	H[MAX_SIZE];
int	n = 0;

void	upHeap(int i){
	if (i == 1 || (H[i] <= H[i / 2]))
		return ;
	SWAP(i, i/2);
	upHeap(i/2);
}

void	downHeap(int i){
	int bigger;

	// 자식이 없는 경우
	if (i * 2 > n)
		return ;
	bigger = i * 2;
	if (i * 2  < n && (H[i * 2 + 1] > H[bigger]))
		bigger = i * 2 + 1;
	if (H[i] >= H[bigger])
		return ;
	SWAP(i, bigger);
	downHeap(bigger);
}

void	insertItem(int key){
	H[++n] = key;
	upHeap(n);
	printf("0\n");
}

int	removeMax(){
	int	key = H[1];

	H[1] = H[n--];
	downHeap(1);
	return (key);
}

void	printHeap(){
	for (int i = 1; i <= n; ++i)
		printf(" %d", H[i]);
	printf("\n");
}

int main()
{
	char	cmd;
	int		key;

	while (1){
		scanf("%c", &cmd);
		getchar();
		if (cmd == 'q')
			break ;
		else if (cmd == 'i'){
			scanf("%d", &key);
			getchar();
			insertItem(key);
		}
		else if (cmd == 'd')
			printf("%d\n", removeMax());
		else if (cmd == 'p')
			printHeap();
	}
	return (0);
}
