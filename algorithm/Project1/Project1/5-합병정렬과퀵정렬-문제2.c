#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int findPivot(int l, int r) {
	srand(time(NULL));
	int num = rand() % r;
	return num;
}

void inPlaceQuickSort(int arr[], int l, int r) {
	if (l >= r)return;

}

int main() {
	int n, *arr, i, number;
	//배열 초기화
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int) * n);
	if (arr == NULL) {
		printf("arr메모리 문제");
		return;
	}

	for (i = 0; i < n; i++) {
		scanf("%d", &number);
		arr[i] = number;
		printf("%d", findPivot(i + 1, n + 1));
	}
	
	//퀵정렬
	inPlaceQuickSort(arr, 0, n - 1);
}
