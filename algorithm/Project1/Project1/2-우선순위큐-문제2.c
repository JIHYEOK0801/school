#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
void insert(int* L, int j, int i) {
	int k;
	int temp = L[i];
	//j ���ķ� i ���� ���Ҹ� �о�� �۾�
	for (k = i; k > j; k--) {
		L[k] = L[k-1];
	}
	//j�� ����
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

	//���
	for (i = 0; i < n; i++) {
		printf(" %d", L[i]);
	}
}