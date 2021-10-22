#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(int* arr, int top) {
	int i;
	for (i = 1; i < top; i++)printf(" %d", arr[i]);
	printf("\n");
}
void swap(int* heap, int index1, int index2) {
	int temp = heap[index1];
	heap[index1] = heap[index2];
	heap[index2] = temp;
}
void upheap(int* heap, int v) {
	if (v == 1) return; // isRoot, root는 항상 1부터. 주의
	if (heap[v / 2] > heap[v]) return; // 부모 > 자식(v)인지 확인
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
int removeRoot(int* heap, int top) { //여기서는 top이 제일 마지막 원소. 이미 -1되어 들어왔으니까.
	int answer = heap[1];
	swap(heap, 1, top);
	downheap(heap, 1, top);
	return answer;
}
int main() {
	char command;
	int n,i, number;
	int heap[100], top = 1;

	while (1) {
		scanf("%c", &command);
		switch (command) {
		case 'i':
			scanf("%d", &number);
			insertHeap(heap, top, number);
			printf("0\n");
			top += 1;
			break;
		case 'd':
			if (top <= 1)break;
			top -= 1;
			printf("%d\n",removeRoot(heap, top));
			break;
		case 'p':
			print(heap, top);
			break;
		case 'q':
			return;
		}
		getchar(); //버퍼를 지워준다. 버퍼 지워주는거 기억하기.
	}
}