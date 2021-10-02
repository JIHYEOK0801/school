#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
void swap(int* L, int i, int j) {
	int temp;
	temp = L[i];
	L[i] = L[j];
	L[j] = temp;
}
int main() {
	int n;
	scanf("%d", &n);

	int* L; // 우선순위 큐
	int i, j, number;
	L = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) {
		scanf("%d", &number);
		L[i] = number;
	}
	//초기화 완료
	
	int index = 0;
	int temp;
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j <= i; j++) {
			if (L[j] > L[index]) {
				index = j;
			}
		}
		swap(L, index, i);
		index = 0;
	}

	for (i = 0; i < n; i++) {
		printf(" %d", L[i]);
	}
}