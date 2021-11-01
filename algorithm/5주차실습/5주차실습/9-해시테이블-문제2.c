#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* - 해시테이블은 크기가 M인 배열로 동적 할당한다.
* - n은 M보다 작은 자연수로 최대 삽입 개수다.
* - 입력 키는 중복이 없는 6자리 또는 8자리의 임의의 자연수(학번)다.
* - 키 x에 대한 해시함수 h(x) = x % M 을 사용한다.
* - 저장된 키 값이 없는 빈 버켓은 0으로 처리한다.
*/

int hx(int x, int M) {
	return x % M;
}
int searchItem(int* arr, int id, int M) {
	int v = hx(id, M);
	while (arr[v] != 0) {
		if (arr[v] == id)
			return v;
		v = (v + 1) % M;
	}
	return -1;
}
int insertItem(int* arr, int id, int M) {
	int v = hx(id, M);
	while (arr[v] != 0) {
		printf("C");
		v = (v + 1) % M;
	}
	arr[v] = id;
	return v;
}

void init(int* arr, int M) {
	int i;
	for (i = 0; i < M; i++) {
		arr[i] = 0;
	}
}

int main() {
	int M, n;
	scanf("%d %d", &M, &n);
	getchar();
	int* arr = (int*)malloc(sizeof(int) * M);
	if (arr == NULL) printf("동적할당 에러");
	
	init(arr,M);

	char c;
	int id;
	int v;
	while (1) {
		scanf("%c", &c);
		switch (c) {
		case 'i':
			scanf("%d", &id);
			printf("%d\n",insertItem(arr, id, M));
			n -= 1;
			break;
		case 's':
			scanf("%d", &id);
			v = searchItem(arr, id, M);
			printf("%d", v);
			if (v != -1)
				printf(" %d", arr[v]);
			printf("\n");
			break;
		case 'e':
			free(arr);
			exit(0);
			break;
		}
		getchar();
	}
	
}