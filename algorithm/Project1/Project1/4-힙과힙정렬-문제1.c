#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct HeapType {
	int H[100];
	int top;
}HeapType;

void printArray(HeapType *heap, int n) {
	int i;
	for (i = 1; i <= n; i++) {
		printf(" %d", heap->H[i]);
	}
	printf("\n");
}

void init(HeapType* heap) {
	heap->top = 1;
}

void swapElements(HeapType* heap, int index1, int index2) {
	int temp = heap->H[index1];
	heap->H[index1] = heap->H[index2];
	heap->H[index2] = temp;
}

void upheap(HeapType* heap) {
	int n_child = heap->top;
	int n_parent = heap->top / 2;

	while ((n_parent > 0) && (heap->H[n_child] > heap->H[n_parent])) {
		swapElements(heap, n_child, n_parent);
		n_child = n_parent;
		n_parent /= 2;
	}
}

int insertItem(HeapType* heap, int item) {
	//삽입
	heap->H[heap->top] = item;
	
	//upheap
	upheap(heap);
	
	//n 갱신
	heap->top += 1;

	//success
	return 0;
}

void downHeap(HeapType* heap, int n_parent) {
	int n_child_left = n_parent * 2;
	int n_child_right = n_parent * 2 + 1;

	if (n_child_left >= heap->top && n_child_right >= heap->top) return 0;

	int bigger = heap->H[n_child_left];
	int n_bigger = n_child_left;

	if (n_child_right < heap->top)
		if (heap->H[n_child_right] > bigger) {
			bigger = heap->H[n_child_right];
			n_bigger = n_child_right;
		}

	if (heap->H[n_parent] > heap->H[n_bigger]) return 0;

	swapElements(heap, n_parent, n_bigger);
	downHeap(heap, n_bigger);
}

void removeRoot(HeapType* heap) {
	//루트노드, 끝노드 값 교체
	swapElements(heap, 1, heap->top - 1);
	heap->top -= 1;
	//루트 downheap
	downHeap(heap, 1);
}

void inPlaceHeapSort(HeapType* heap) {
	while (heap->top > 1) {
		removeRoot(heap);
	}
}

int main() {
	int i, n, item;
	HeapType heap;
	init(&heap);

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &item);
		insertItem(&heap, item);
	}
	inPlaceHeapSort(&heap);
	printArray(&heap, n);
}