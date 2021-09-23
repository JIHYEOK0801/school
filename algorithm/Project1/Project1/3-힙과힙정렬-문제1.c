#pragma warning (disable:4996)
#include <stdio.h>


typedef struct heapType {
	int arr[100]; // �迭
	int n; //������ ���Ұ� ����ִ� n��
}heapType;

void init(heapType* heap) {
	heap->n = 1;
}

void print(heapType* heap) {
	int i;
	for (i = 1; i < heap->n; i++) {
		printf(" %d", heap->arr[i]);
	}
	printf("\n");
}

void swapElements(heapType* heap, int index1, int index2) {
	int temp = heap->arr[index1];
	heap->arr[index1] = heap->arr[index2];
	heap->arr[index2] = temp;
}
void upheap(heapType *heap) {
	int n_child = heap->n;
	int n_parent = heap->n / 2;

	while ( (n_parent > 0) && (heap->arr[n_child] > heap->arr[n_parent])) {
		swapElements(heap, n_child, n_parent);
		n_child = n_parent;
		n_parent /= 2;
	}
}

int insertItem(heapType* heap, int item) {
	//����
	heap->arr[heap->n] = item;
	//upheap
	upheap(heap);
	//n ����
	heap->n += 1;

	//success
	return 0;
}

void downHeap(heapType* heap, int n_parent) {
	int n_child_left = n_parent * 2;
	int n_child_right = n_parent * 2 + 1;

	if (n_child_left >= heap->n && n_child_right >= heap->n) return 0;

	int bigger = heap->arr[n_child_left];
	int n_bigger = n_child_left;

	if (n_child_right < heap->n)
		if (heap->arr[n_child_right] > bigger) {
			bigger = heap->arr[n_child_right];
			n_bigger = n_child_right;
		}
	
	if (heap->arr[n_parent] > heap->arr[n_bigger]) return 0;

	swapElements(heap, n_parent, n_bigger);
	downHeap(heap, n_bigger);
}

int removeRoot(heapType* heap) {
	int response = heap->arr[1];
	if (heap->n == 1) return response;

	//��Ʈ���, ����� �� ��ü
	swapElements(heap, 1, heap->n - 1);
	heap->n -= 1;
	//��Ʈ downheap
	downHeap(heap, 1);
	//success
	printf("%d\n", response);
	return response;
}


int main() {
	heapType heap;
	int item,response;
	char command;
	
	init(&heap);

	while(1){
		
		scanf("%c", &command);
		switch (command) {

		//����
		case 'i':
			scanf("%d", &item);
			response = insertItem(&heap, item);
			printf("%d\n", response);
			break;
			
		//����
		case 'd':
			response = removeRoot(&heap);
			//printf("%d\n", response);
			break;
		
		//�μ�
		case 'p':
			print(&heap);
			break;

		//����
		case 'q':
			return 0;
			break;
		}

		getchar();

	}
}