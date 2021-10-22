#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
int Binarysearch(int* arr, int k, int l, int r) {
	int mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (k > arr[mid]) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	return l;
}
int main() {
	int n, k, i, *arr = NULL;
	scanf("%d %d", &n, &k);
	
	arr = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}

	int answer = Binarysearch(arr, k, 0, n - 1);
	printf(" %d", answer);
}