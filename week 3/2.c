#include <stdio.h>

#define SWAP(a, b) {int tmp=H[a]; H[a]=H[b]; H[b]=tmp;}

#define MAX_SIZE 100

int	H[MAX_SIZE];
int	n = 0;

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

void	printHeap(){
	for (int i = 1; i <= n; ++i)
		printf(" %d", H[i]);
	printf("\n");
}

void buildHeap()
{
    int i = n / 2;

	for ( ; i >= 1; --i)
		downHeap(i);
}

int main()
{
    scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
        scanf("%d", &H[i]);
    buildHeap();
    printHeap();
	return (0);
}
