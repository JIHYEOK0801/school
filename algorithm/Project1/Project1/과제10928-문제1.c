/*
* ::: 문제 조건 :::
* 1. '주어진 숫자들이 나타내는 heap' ---> input 배열은 최대힙 or 최소힙
* 2. '내부노드가 하나도 없는 경우는 없다' ---> heap 원소가 2개 이상이다.
* 3. '중복 숫자는 없다고 가정' ---> 중복 생각 x
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
