#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
void swap(int* arr, int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}
int* inPlacePartition(int* arr, int l, int r, int pivot) {
	int i, j;
	swap(arr, r, pivot);
	i = l; j = r - 1;

	while (i <= j) {
		while (i <= j && arr[i] <= arr[pivot])
			i += 1;
		while (j >= i && arr[j] >= arr[pivot])
			j -= 1;
		if (i < j)swap(arr, i, j);
	}

	swap(arr, i, r);

	int* ab = (int*)malloc(sizeof(int) * 2);
	ab[0] = i - 1;
	ab[1] = i + 1;
	return ab;
}
void print(int* arr, int n) {
	int i;
	for (i = 0; i < n; i++)printf(" %d", arr[i]);
	printf("\n");
}
void inPlaceQuickSort(int* arr, int l, int r) {
	if (l >= r)return;
	printf("%d     ", arr[r]);
	print(arr, 10);
	int pivot = r;
	int *ab = inPlacePartition(arr,l,r,pivot);
	inPlaceQuickSort(arr, l, ab[0]);
	inPlaceQuickSort(arr, ab[1], r);
	free(ab);
}

int main() {
	int n,i,*arr;
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}
	inPlaceQuickSort(arr,0,n-1);
	print(arr, n);
}