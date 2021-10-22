#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
void swap(int* arr, int index1, int index2) {
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
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

	int mini;
	for (i = 0; i < n - 1; i++) {
		mini = i;
		for (j = i + 1; j < n; j++) {
			if (arr[j] < arr[mini])
				mini = j;
		}
		swap(arr, i, mini);
	}

	for (i = 0; i < n; i++)
		printf(" %d", arr[i]);
}