#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* ũ�� M�� �ؽ����̺� ���� ���� Ű ���� �Է¹޾� �����ϰ�, 
* �и�������� �̿��Ͽ� �浹�� ó���ϴ� �ؽ����̺� �ۼ�
* 
* - �ؽ����̺��� ũ�Ⱑ M�� �迭�� ���� �Ҵ��Ѵ�.
* - �Է� Ű�� �ߺ��� ���� �ڿ�����.
* - Ű x�� ���� �ؽ��Լ� h(x) = x % M �� ����Ѵ�.
* - ���� �� �浹�� �߻��ϴ� ���, �ش� ���� ����Ʈ�� �� �տ� �����Ѵ�.
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
	// 1. arr[v]�� ���Ұ� �Ѱ��� ���� ��
	if (*arrv == NULL) return 0;

	// 2. arr[v]�� ù��° ���� == k �϶�
	int rank = 1;
	node* p = *arrv;
	if (p->key == k) {
		*arrv = p->next;
		free(p);
		return rank;
	}
	
	// 3. arr[v]�� �ι�°���� �̻�~ == k �϶�
	node* q = p;
	p = p->next; // ù��° ���Ҵ� 2.���� �˻������Ƿ� �ǳʶ�
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

	// 4. arr[v]���� ���Ҹ� �߰� ������ ��
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
	if (arr == NULL) printf("������ �迭 �����Ҵ� ����");

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