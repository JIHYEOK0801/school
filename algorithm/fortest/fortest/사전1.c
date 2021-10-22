#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
int answer;
void Bsearch(int* arr, int k, int l, int r) {
	int mid = (l + r) / 2;
	//printf(" l = %d mid = %d r = %d\n",l, mid,r);
	if (l > r) {
		answer = r;
	}
	else {
		if (k >= arr[mid]) {
			Bsearch(arr, k, mid+1, r);
		}
		else {
			Bsearch(arr, k, l, mid - 1);
		}
	}
}
int main() {
	int n, k, i;
	scanf("%d %d", &n, &k);
	
	int* arr = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}

	Bsearch(arr, k, 0, n-1);
	printf(" %d", answer);
}