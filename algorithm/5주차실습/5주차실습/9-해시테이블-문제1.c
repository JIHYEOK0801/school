#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* 크기 M인 해시테이블에 여러 개의 키 값을 입력받아 저장하고, 
* 분리연쇄법을 이용하여 충돌을 처리하는 해시테이블 작성
* 
* - 해시테이블은 크기가 M인 배열로 동적 할당한다.
* - 입력 키는 중복이 없는 자연수다.
* - 키 x에 대한 해시함수 h(x) = x % M 을 사용한다.
* - 삽입 시 충돌이 발생하는 경우, 해당 버켓 리스트의 맨 앞에 삽입한다.
*/

typedef struct node {
	int key;
	struct node* next;
}node;

node* getNode(int key) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->key = key;
	newNode->next = NULL;
	return newNode;
}
int hx(int x, int M) {
	return x % M;
}

int removeElement(node** arrv, int k) {
	// 1. arr[v]에 원소가 한개도 없을 때
	if (*arrv == NULL) return 0;

	// 2. arr[v]의 첫번째 원소 == k 일때
	int rank = 1;
	node* p = *arrv;
	if (p->key == k) {
		*arrv = p->next;
		free(p);
		return rank;
	}
	
	// 3. arr[v]의 두번째원소 이상~ == k 일때
	node* q = p;
	p = p->next; // 첫번째 원소는 2.에서 검사했으므로 건너띔
	while (p != NULL) {
		rank += 1;
		if (p->key == k) {
			q->next = p->next;
			free(p);
			return rank;
		}
		q = p;
		p = p->next;
	}

	// 4. arr[v]에서 원소를 발견 못했을 때
	return 0;
}

int removeItem(int k, node** arr, int M) {
	int v = hx(k, M);
	return removeElement(arr + v, k);
}

int findKey(node** arrv, int k) {
	if (*arrv == NULL) return 0;
	
	int	rank = 1;
	node* p = *arrv;
	while (p != NULL) {
		if (p->key == k) {
			return rank;
		}
		rank += 1;
		p = p->next;
	}

	return 0;
}
int findElement(int k, node** arr, int M) {
	int v = hx(k, M);
	return findKey(arr + v, k);
}

void insertKey(node** arrv, int k) {
	node* p;
	if (*arrv == NULL) {
		*arrv = getNode(k);
	}
	else {
		p = getNode(k);
		p->next = *arrv;
		*arrv = p;
	}
}

void insertItem(int k, node **arr, int M) {
	int v = hx(k, M);
	insertKey(arr + v, k);
}

void initBucketArray(node **arr, int M) {
	int i;
	for (i = 0; i < M; i++) {
		*(arr + i) = NULL;
	}
}

void print(node** arr, int M) {
	int i;
	node* p;
	for (i = 0; i < M; i++) {
		p = *(arr + i);
		while (p != NULL)
		{
			printf(" %d", p->key);
			p = p->next;
		}
	}
	printf("\n");
}

void putNode(node** arr, int M) {
	int i;
	node* p, *q;
	for (i = 0; i < M; i++) {
		p = *(arr + i);
		q = p;
		while (p != NULL) {
			p = p->next;
			free(q);
			q = p;
		}
	}
	free(arr);
}
int main() {
	int M;
	scanf("%d", &M);
	getchar();

	node** arr = NULL;
	arr = (node**)malloc(sizeof(node*) * M);
	if (arr == NULL) printf("포인터 배열 동적할당 에러");

	initBucketArray(arr, M);

	char c;
	int k;
	while (1) {
		scanf("%c", &c);
		switch (c) {
		case 'i':
			scanf("%d", &k);
			insertItem(k, arr, M);
			break;
		case 's':
			scanf("%d", &k);
			printf("%d\n",findElement(k, arr, M));
			break;
		case 'd':
			scanf("%d", &k);
			printf("%d\n", removeItem(k, arr, M));
			break;
		case 'p':
			print(arr, M);
			break;
		case 'e':
			putNode(arr, M);
			exit(0);
			break;
		}
		getchar();
	}
	
}