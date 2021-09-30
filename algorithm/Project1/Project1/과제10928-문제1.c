/*
* ::: ���� ���� :::
* 1. '�־��� ���ڵ��� ��Ÿ���� heap' ---> input �迭�� �ִ��� or �ּ���
* 2. '���γ�尡 �ϳ��� ���� ���� ����' ---> heap ���Ұ� 2�� �̻��̴�.
* 3. '�ߺ� ���ڴ� ���ٰ� ����' ---> �ߺ� ���� x
*/
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int isMinheap(int* heap, int n) {
	int smaller = heap[2];
	if (n > 2) {
		if (heap[3] < smaller) {
			smaller = heap[3];
		}
	}

	if (heap[1] < smaller) return 1;
	else return 0;
}

int isMinheap__CheckAll(int* heap, int n) {
	int smaller = heap[2];
	int i;
	for (i = 2; i <= n; i++) {
		if (heap[i] < smaller)
			smaller = heap[i];
	}
	if (heap[1] < smaller)
		return 1;
	else return 0;
}

int is_heap(int* heap, int n) {
	int i;
	int smaller;
	for (i = n; i >= 1; i--) {
		if ((i * 2 > n) && (i * 2 + 1 > n)) continue;
		
		smaller = i * 2;
		if ((i * 2 + 1) <= n) {
			if (heap[i * 2 + 1] < heap[smaller]) {
				smaller = i * 2 + 1;
			}
		}

		if (heap[i] > heap[smaller]) return 0;
	}
	return 1;
}



int main() {
	int n, i, number;
	int* heap;
	char answer[4];

	scanf("%d", &n);
	heap = (int*)malloc(sizeof(int) * (n + 1));
	for (i = 1; i < n + 1; i++) {
		scanf("%d", &number);
		heap[i] = number;
	}

	if (is_heap(heap,n) && isMinheap(heap, n)) {
		strcpy(answer, "Yes");
	}
	else {
		strcpy(answer, "No");
	}

	printf("%s\n", answer);
	printf("%d", heap[n / 2]);

	free(heap);
}
