#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
void swap(int* heap, int index1, int index2) {
	int temp = heap[index1];
	heap[index1] = heap[index2];
	heap[index2] = temp;
}

void print(int* arr, int n) {
	int i;
	for (i = 1; i <= n; i++)printf(" %d", arr[i]);
	printf("\n");
}

void upheap(int* heap, int v) {
	if (v == 1) return; // isRoot, root�� �׻� 1����. ����
	if (heap[v / 2] > heap[v]) return; // �θ� > �ڽ�(v)���� Ȯ��
	swap(heap, v, v / 2);
	upheap(heap, v / 2);
}
 
void insertHeap(int* heap, int top, int number) {
	heap[top] = number;
	upheap(heap, top);
}

void downheap(int* heap, int root, int top) {
	int left = root * 2;
	int right = root * 2 + 1;
	int max;
	if (left >= top) return;

	max = left;
	if (right < top)
		if (heap[right] > heap[max])
			max = right;

	if (heap[root] > heap[max])return;

	swap(heap, root, max);
	downheap(heap, max, top);
}

void removeRoot(int* heap, int top) { //���⼭�� top�� ���� ������ ����. �̹� -1�Ǿ� �������ϱ�.
	swap(heap, 1, top);
	downheap(heap, 1, top);
}

int main() {
	int i, n;
	int heap[100],top = 1,number;
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		scanf("%d", &number);
		insertHeap(heap, top, number);
		top += 1;
	}
	
	while (top > 1) {
		top -= 1;
		removeRoot(heap, top);
	}

	print(heap, n);
}