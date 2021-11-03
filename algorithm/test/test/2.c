#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student {
	int s_id;
	char s_name[21];
}student;

// ���� ��ġ �˻�
int search(student* arr, int l, int r, int search_id) {
	if (l >= r) {
		if ((arr + l)->s_id == search_id)
			return l;
		else
			return -1;
	}
	//���ҵ� �� Ž��
	/*
	* �Ʒ��� �ȵǴ� ���� ������ �� üũ�ϱ�
	* int front = search(arr, l, mid - 1, search_id);
	* int back = search(arr, mid, r, search_id);
	*/
	int mid = (l + r) / 2;
	int front = search(arr, l, mid, search_id);
	int back = search(arr, mid + 1, r, search_id);
	
	// �Ѵ� -1 �� ���
	if (front == back)
		return -1;

	// id�� ã�� ��� -1�� �ƴ� ���� ����
	if (front != -1)
		return front;
	else
		return back;
}

int main() {
	int N;
	scanf("%d", &N);

	student* arr = (student*)malloc(sizeof(student) * N);

	int i;
	for (i = 0; i < N; i++) {
		scanf("%d %s", &((arr + i)->s_id), (arr+i)->s_name);
	}

	int search_id;
	scanf("%d", &search_id);
	
	int answer_index = search(arr, 0, N-1, search_id);
	if (answer_index == -1)
		printf("%d", answer_index);
	else
		printf("%d %s", (arr + answer_index)->s_id, (arr + answer_index)->s_name);

	free(arr);
}