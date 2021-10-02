/*
* ::함수 내에서 변수를 생성해서 return하는 것을 주의하자.
* partition 함수내에서 만든 node* L1L2[2]를 반환했다가 한참 헤맸다.
* 
*/
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	int item;
	struct node* next;
}node;

typedef struct NodeList {
	node* p;
}NodeList;

typedef struct L1L2pointer {
	node* pointArr[2];
}L1L2pointer;

node* getNode(int item) {
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL) {
		printf("newnode 생성 불가");
		exit(0);
	}
	newnode->item = item;
	newnode->next = NULL;
	return newnode;
}

void insertNode(NodeList* nodelist, int item) {
	//존재하는 노드가 있을 때
	if (nodelist->p != NULL) {
		node* q = nodelist->p;
		while (q->next != NULL)q = q->next;
		q->next = getNode(item);
	}
	//노드를 처음 삽입할 때
	else {
		nodelist->p = getNode(item);
	}
}


L1L2pointer* partition(node* L, int k) {
	L1L2pointer* L1L2 = (L1L2pointer*)malloc(sizeof(L1L2pointer));
	node* p = NULL;
	int i;
	L1L2->pointArr[0] = L;
	L1L2->pointArr[1] = L;
	
	for (i = 0; i < k; i++) {
		p = L1L2->pointArr[1];
		L1L2->pointArr[1] = L1L2->pointArr[1]->next;
	}
	
	if (p == NULL) {
		printf("partition 포인터 문제\n");
		exit(0);
	}
	p->next = NULL;

	return L1L2;
}

node* merge(node* L1, node* L2) {
	node* emptylist = getNode(-1);
	node* L = emptylist;
	while (L1 != NULL && L2 != NULL) {
		if (L1->item <= L2->item) {
			L->next = L1;
			L1 = L1->next;
			L = L->next;
		}
		else {
			L->next = L2;
			L2 = L2->next;
			L = L->next;
		}	
	}

	while (L1 != NULL) {
		L->next = L1;
		L1 = L1->next;
		L = L->next;
	}

	while (L2 != NULL) {
		L->next = L2;
		L2 = L2->next;
		L = L->next;
	}
	
	L = emptylist->next;
	return L;
}

void mergeSort(node **L) {
	//size check
	node* p = *L;
	int size = 0;
	while (p != NULL) {
		size += 1;
		p = p->next;
	}
	if (size <= 1)return;
	

	//merge sort
	L1L2pointer *L1L2 = partition(*L, size / 2);
	node* L1 = L1L2->pointArr[0];
	node* L2 = L1L2->pointArr[1];
	mergeSort(&L1);
	mergeSort(&L2);
	*L = merge(L1,L2);

	free(L1L2);
}

void print(NodeList* nodelist) {
	node* q = nodelist->p;
	while (q != NULL) { 
		printf(" %d", q->item);
		q = q->next;
	}
}

int main() {
	int n, i,item;
	NodeList nodelist;
	nodelist.p = NULL;

	//리스트 초기화
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &item);
		insertNode(&nodelist, item);
	}
	
	//합병정렬
	mergeSort(&nodelist.p);
	print(&nodelist);

	node* q= nodelist.p;
	while (nodelist.p != NULL) {
		q = q->next;
		free(nodelist.p);
		nodelist.p = q;
	}
}