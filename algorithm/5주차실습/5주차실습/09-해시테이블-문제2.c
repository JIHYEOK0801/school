#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* - �ؽ����̺��� ũ�Ⱑ M�� �迭�� ���� �Ҵ��Ѵ�.
* - n�� M���� ���� �ڿ����� �ִ� ���� ������.
* - �Է� Ű�� �ߺ��� ���� 6�ڸ� �Ǵ� 8�ڸ��� ������ �ڿ���(�й�)��.
* - Ű x�� ���� �ؽ��Լ� h(x) = x % M �� ����Ѵ�.
* - ����� Ű ���� ���� �� ������ 0���� ó���Ѵ�.
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
	if (arr == NULL) printf("�����Ҵ� ����");
	
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