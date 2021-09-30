/*
* ::: ���� ���� :::
* 1. '�־��� ���ڵ��� ��Ÿ���� heap' ---> input �迭�� �ִ��� or �ּ���
* 2. '���γ�尡 �ϳ��� ���� ���� ����' ---> heap ���Ұ� 2�� �̻��̴�.
* 3. '�ߺ� ���ڴ� ���ٰ� ����' ---> �ߺ� ���� x
*/
/*
* �ּҽð� ������
* 1. ��� 1������ �ڽ� 2���� ���ϸ鼭 �������� �Ǹ� �뷫 O(2N) ����
* 2. �ּ���, �ִ���, �������� ������� ���ѻ��¿��� ��带 �������鼭 �Ѱ��� ���� �Ұ�. O(logN) ���� ���̴� �� �Ұ����̶� �Ǵ�
* 3. ���������� �ϳ��� �θ�� ���ϴ°͵� O(N)���� ������ ������?
*/


#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int isParentSmaller(int* heap, int parent, int child) {
	if (heap[parent] > heap[child])
		return 0;
	return 1;
}
void print(char* answer, int lastinnernode) {
	printf("%s\n%d", answer, lastinnernode);
}
int main() {
	int N, i, number, *heap;
	char answer[4];

	scanf("%d", &N);
	
	// heap �ʱ�ȭ
	heap= (int*)malloc(sizeof(int) * (N + 1));
	

	for (i = 1; i < N + 1; i++) {
		scanf("%d", &number);
		heap[i] = number;
	}

	// ������ ���γ����� ����
	int lastinnernode = heap[N / 2];

	// �ּ������� �˻�
	
	for (i = N; i >= 2; i--) {
		if (!isParentSmaller(heap, i / 2, i)){
			print("No", lastinnernode);
			return;
		}
			
	}
	print("Yes", lastinnernode);
}
