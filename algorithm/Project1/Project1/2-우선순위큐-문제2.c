#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
void insert(int* L, int j, int i) {
	int k;
	int temp = L[i];
	//j 이후로 i 까지 원소를 밀어내는 작업
	for (k = i; k > j; k--) {
		L[k] = L[k-1];
	}
	//j에 삽입
	L[j] = temp;
}
int main() {
	int n;
	scanf("%d", &n);

	int* L = (int*)malloc(sizeof(int) * n);
	int i, j, number;

	for (i = 0; i < n; i++) {
		scanf("%d", &number);
		L[i] = number;
	}

	//insertionsort
	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			if (L[i] < L[j]) {
				insert(L, j, i);
				break;
			}
		}
	}

	//출력
	for (i = 0; i < n; i++) {
		printf(" %d", L[i]);
	}
}