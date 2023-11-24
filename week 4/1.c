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

void	downHeap(int i, int last){
	int bigger, left, right;

    left = 2 * i;
    right = 2 * i + 1;
    // 자식이 없는 경우
    if (left > last)
        return ;
	bigger = left;
	if (right <= last && (H[right] > H[bigger]))
		bigger = right;
	if (H[i] >= H[bigger])
		return ;
	SWAP(i, bigger);
	downHeap(bigger, last);
}

void	insertItem(int key){
	H[++n] = key;
	upHeap(n);
}

int	removeMax(){
	int	key = H[1];

	H[1] = H[n--];
	downHeap(1, n);
	return (key);
}

void	printHeap(){
	for (int i = 1; i <= n; ++i)
		printf(" %d", H[i]);
	printf("\n");
}

void inPlaceHeapSort()
{
    for (int i = n; i >= 2; i--)
    {
        SWAP(1, i);
        downHeap(1, i - 1);
    }
}

int main()
{
    int key, size;

    scanf("%d", &size);
    // key를 입력받아 heap 생성
    for (int i = 1; i <= size; ++i){
        scanf("%d", &key);
		getchar();
		insertItem(key);
    }
    inPlaceHeapSort();
    printHeap();

    return (0);
}
