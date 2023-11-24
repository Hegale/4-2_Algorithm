# define SWAP(x, y, temp) ( (temp)=(x), (x)=(y), (y)=(temp) )


void InsertionSort(int* arr,int n) {
	int key;
	for (int i = 1; i < n; i++) {
		key = arr[i];
		int j = i - 1;
        // = for(j = i-1 ; j >=0; j--)
		while (j >= 0 && key < arr[j]) { //key보다 작은 값이 나오면 멈춤
			arr[j + 1] = arr[j]; // 앞자리의 값이 key보다 크다면 하나씩 이동
			j--;
		}
		arr[j + 1] = key; // 그 자리에 삽입
	}
}

void selection_sort(int list[], int n){
  int i, j, least, temp;

  // 마지막 숫자는 자동으로 정렬되기 때문에 (숫자 개수-1) 만큼 반복한다.
  for(i=0; i<n-1; i++){
    least = i;

    // 최솟값을 탐색한다.
    for(j=i+1; j<n; j++){
      if(list[j]<list[least])
        least = j;
    }

    // 최솟값이 자기 자신이면 자료 이동을 하지 않는다.
    if(i != least){
        SWAP(list[i], list[least], temp);
    }
  }
}

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	srand(time(NULL));
	for (int i = 0; i < 30; ++i)
	{
		printf("%d\n", rand());
	}
}
