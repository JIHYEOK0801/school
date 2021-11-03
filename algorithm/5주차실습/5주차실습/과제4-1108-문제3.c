#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
	int s_id;
	char s_name[21];
}student;

// ÀÌÁøÅ½»ö
int binarySearch(student* arr, int l, int r, int search_id) {
	if (l > r) return -1;

	int mid = (l + r) / 2;
	int answer_index;
	if (search_id == (arr + mid)->s_id)
		answer_index = mid;

	else if ( search_id < (arr + mid)->s_id )
		answer_index = binarySearch(arr, l, mid - 1, search_id);
	else
		answer_index = binarySearch(arr, mid + 1, r, search_id);

	return answer_index;
}

int main() {
	int N;
	scanf("%d", &N);

	student* arr = (student*)malloc(sizeof(student) * N);

	int i;
	for (i = 0; i < N; i++) {
		scanf("%d %s", &((arr + i)->s_id), (arr + i)->s_name);
	}

	int search_id;
	scanf("%d", &search_id);

	int answer_index = binarySearch(arr, 0, N - 1, search_id);
	if (answer_index == -1)
		printf("%d", answer_index);
	else
		printf("%d %s", (arr + answer_index)->s_id, (arr + answer_index)->s_name);

	free(arr);
}