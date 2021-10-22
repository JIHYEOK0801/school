#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

void print(int* arr, int top) {
	int i;
	for (i = 1; i <= top; i++)printf(" %d", arr[i]);
	printf("\n");
}
void swap(int* heap, int index1, int index2) {
	int temp = heap[index1];
	heap[index1] = heap[index2];
	heap[index2] = temp;
}
void downheap(int* heap, int root, int n) {
	int left = root * 2;
	int right = root * 2 + 1;
	int max;
	if (left > n) return;

	max = left;
	if (right <= n)
		if (heap[right] > heap[max])
			max = right;

	if (heap[root] > heap[max])return;

	swap(heap, root, max);
	downheap(heap, max, n);
}
void rbuildheap(int* heap, int root, int n) {
	int left = root * 2;
	int right = root * 2 + 1;

	if (left > n)return;
	rbuildheap(heap, left, n);

	if (right <= n)rbuildheap(heap, right, n);
	
	downheap(heap, root, n);
}
int main() {
	int i, n;
	int heap[100], top = 1;

	scanf("%d", &n);
	for (i = 1; i < n+1; i++) {
		scanf("%d", heap + i);
	}
	//rbuildheap(heap, 1, n); Àç±Í¹æ¹ý
	//¹ØÀº ºñÀç±Í
	for (i = n / 2; i >= 1; i--) {
		downheap(heap, i, n);
	}
	print(heap, n);
}