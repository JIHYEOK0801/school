#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* - 해시테이블은 크기가 M인 배열로 동적 할당한다(종료 시 해제).
* - n은 M보다 작은 자연수로 최대 삽입 개수다.
* - 입력 키는 중복이 없는 2자리 이상의 자연수다.
* - 키 x에 대한 첫 번째 해시함수 h(x) = x % M, 두 번째 해시함수 h‘(x) = q – (x % q) 를사용한다. 
*	q는 M보다 조금 작은 소수로 입력으로 주어진다.
* - 저장된 키가 없는 빈 버켓은 0으로 처리한다.
*/

int hx(int x, int M) {
	return x % M;
}
int h2x(int x, int q) {
	return q - (x % q);
}

int searchItem(int* arr, int id, int M, int q) {
	int v = hx(id, M);
	int w = h2x(id, q);
	while (arr[v] != 0) {
		if (arr[v] == id)
			return v;
		v = (v + w) % M;
	}
	return -1;
}
int insertItem(int* arr, int id, int M, int q) {
	int v = hx(id, M);
	int w = h2x(id, q);
	while (arr[v] != 0) {
		printf("C");
		v = (v + w) % M;
	}
	arr[v] = id;
	return v;
}

void print(int* arr, int M) {
	int i;
	for (i = 0; i < M; i++) {
		printf(" %d", arr[i]);
	}
	printf("\n");
}

void init(int* arr, int M) {
	int i;
	for (i = 0; i < M; i++) {
		arr[i] = 0;
	}
}

int main() {
	int M, n, q;
	scanf("%d %d %d", &M, &n, &q);
	getchar();
	int* arr = (int*)malloc(sizeof(int) * M);
	if (arr == NULL) printf("동적할당 에러");

	init(arr, M);

	char c;
	int id;
	int v;
	while (1) {
		scanf("%c", &c);
		switch (c) {
		case 'i':
			scanf("%d", &id);
			printf("%d\n", insertItem(arr, id, M, q));
			n -= 1;
			break;
		case 's':
			scanf("%d", &id);
			v = searchItem(arr, id, M, q);
			printf("%d", v);
			if (v != -1)
				printf(" %d", arr[v]);
			printf("\n");
			break;
		case 'p':
			print(arr, M);
			break;
		case 'e':
			print(arr, M);
			free(arr);
			exit(0);
			break;
		}
		getchar();
	}

}