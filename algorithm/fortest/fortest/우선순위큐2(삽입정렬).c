#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
void swap(int* arr, int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}
int main() {
	int i, j, n, number;
	int* arr;
	scanf("%d", &n);

	arr = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		scanf("%d", &number);
		arr[i] = number;
	}

	for (i = 1; i < n; i++) {
		for (j = i - 1; j >= 0; j--) {
			if (arr[j + 1] > arr[j])break;
			swap(arr, j, j + 1);
		}
	}

	for (i = 0; i < n; i++)
		printf(" %d", arr[i]);
}