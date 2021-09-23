#pragma warning (disable:4996)
#include <stdio.h>

typedef struct heapType {
	int arr[100];
	int n;
}heapType;

void init(heapType* heap, int n) {
	int i, item;
	heap->n = n;

	for (i = 1; i < n + 1; i++) {
		scanf("%d", &item);
		heap->arr[i] = item;
	}
}

void print(heapType* heap) {
	int i;
	for (i = 1; i <= heap->n; i++) {
		printf(" %d", heap->arr[i]);
	}
	printf("\n");
}

void swapElements(heapType* heap, int index1, int index2) {
	int temp = heap->arr[index1];
	heap->arr[index1] = heap->arr[index2];
	heap->arr[index2] = temp;
}



void downHeap(heapType* heap, int n_parent) {
	int n_child_left = n_parent * 2;
	int n_child_right = n_parent * 2 + 1;

	if (n_child_left > heap->n && n_child_right > heap->n) return 0;

	int bigger = heap->arr[n_child_left];
	int n_bigger = n_child_left;

	if (n_child_right <= heap->n)
		if (heap->arr[n_child_right] > bigger) {
			bigger = heap->arr[n_child_right];
			n_bigger = n_child_right;
		}

	if (heap->arr[n_parent] > heap->arr[n_bigger]) return 0;

	swapElements(heap, n_parent, n_bigger);
	downHeap(heap, n_bigger);
}

void rbuildHeap(heapType* heap, int n_parent) {
	int n_child_left = n_parent * 2;
	int n_child_right = n_parent * 2 + 1;
	if (n_parent > heap->n) return 0;

	rbuildHeap(heap, n_child_left);
	rbuildHeap(heap, n_child_right);
	downHeap(heap, n_parent);
}
int main() {
	heapType heap;
	int n, i, item;
	scanf("%d", &n);

	init(&heap, n);
	
	/*
	* ºñÀç±Í
	for (i = heap.n / 2; i >= 1; i--) {
		downHeap(&heap, i);
	}
	*/

	//Àç±Í
	rbuildHeap(&heap,1);
	print(&heap);
}