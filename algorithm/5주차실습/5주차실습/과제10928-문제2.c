#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
int K;
int* heap, size;
void swapElement(int id_1, int id_2) {
	int temp;
	temp = heap[id_1];
	heap[id_1] = heap[id_2];
	heap[id_2] = temp;
}
void print() {
	int i;
	for (i = K; i >= 1; i--) {
		printf(" %d", heap[i]);
	}
	printf("\n");
}
void downHeap(int i_parent) {
	int i_leftchild = i_parent * 2;
	int i_rightchild = i_parent * 2 + 1;

	if (i_leftchild > size && i_rightchild > size)
		return;
	
	int i_smaller = i_leftchild;
	if (i_rightchild <= size && heap[i_rightchild] < heap[i_smaller])
		i_smaller = i_rightchild;

	if (heap[i_parent] < heap[i_smaller]) return;

	swapElement(i_parent, i_smaller);
	downHeap(i_smaller);
}
void BuildHeap(int i_parent) {
	int i_leftchild = i_parent * 2;
	int i_rightchild = i_parent * 2 + 1;

	if (i_parent > size)return;
	
	BuildHeap(i_leftchild);
	BuildHeap(i_rightchild);
	downHeap(i_parent);
}

void Insert(int number) {
	if (number < heap[1])return;
	heap[1] = number;
	downHeap(1);
}

void removeRoot(int lastindex) {
	swapElement(1, lastindex);
	size -= 1;
	downHeap(1);
}

void inPlaceHeapSort() {
	int i;
	for (i = K; i >= 2; i--)
		removeRoot(i);
}

int main() {
	int N, i, number;
	scanf("%d %d", &N, &K);
	size = K;

	// K = 0 일때
	if (K == 0)return;
	

	// K만큼 상향식 힙 생성
	heap = (int*)malloc(sizeof(int) * (K + 1));
	for (i = 0; i < K; i++){
		scanf("%d", &number);
		heap[i + 1] = number;
	}

	BuildHeap(1);

	// N까지 추가 입력 하면서 insert
	for (; i < N; i++) {
		scanf("%d", &number);
		Insert(number);
	}

	// 힙정렬
	inPlaceHeapSort();

	// 내림차순 힙을 끝에서 부터 출력
	print();

	free(heap);
}