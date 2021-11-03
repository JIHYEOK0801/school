#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student {
	int s_id;
	char s_name[21];
}student;

// 분할 통치 검색
int search(student* arr, int l, int r, int search_id) {
	if (l >= r) {
		if ((arr + l)->s_id == search_id)
			return l;
		else
			return -1;
	}
	//분할될 곳 탐색
	/*
	* 아래가 안되는 이유 복습할 때 체크하기
	* int front = search(arr, l, mid - 1, search_id);
	* int back = search(arr, mid, r, search_id);
	*/
	int mid = (l + r) / 2;
	int front = search(arr, l, mid, search_id);
	int back = search(arr, mid + 1, r, search_id);
	
	// 둘다 -1 일 경우
	if (front == back)
		return -1;

	// id를 찾은 경우 -1이 아닌 것이 정답
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