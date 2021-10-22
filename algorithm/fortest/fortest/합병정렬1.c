#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int number;
	struct node* next;
}node;

typedef struct L1L2 {
	node* L1, *L2;
}L1L2;

node* getNode(int number) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->number = number;
	newnode->next = NULL;
	return newnode;
}
void print(node* arr) {
	while (arr != NULL) {
		printf(" %d", arr->number);
		arr = arr->next;
	}
	printf("\n");
}

L1L2* partition(node* arr, int k) {
	node* a = arr, * b = arr, *q = NULL;
	L1L2* p = NULL;
	int i;
	
	for (i = 0; i < k; i++) {
		q = b;
		b = b->next;
	}
	q->next = NULL;

	p = (L1L2*)malloc(sizeof(L1L2));
	p->L1 = a;
	p->L2 = b;
	return p;
}
node* merge(node* L1, node* L2) {
	node* a = L1, * b = L2;
	node* p = getNode(-1),*q = p;
	while ((a != NULL) && (b != NULL)) {
		if (a->number < b->number) {
			p->next = a;
			a = a->next;
			p = p->next;
		}
		else {
			p->next = b;
			b = b->next;
			p = p->next;
		}
	}
	while (a != NULL) {
		p->next = a;
		p = p->next;
		a = a->next;
	}
	while (b != NULL) {
		p->next = b;
		p = p->next;
		b = b->next;
	}
	p = q->next;
	free(q);
	return p;
}

void mergeSort(node** arr) {
	int length = 0;
	node* p = *arr, *L1, *L2;
	L1L2* partitioned_arr = NULL;
	while (p != NULL) {
		length += 1;
		p = p->next;
	}
	if (length <= 1)return;
	partitioned_arr = partition(*arr, length / 2);
	L1 = partitioned_arr->L1;
	L2 = partitioned_arr->L2;
	mergeSort(&L1);
	mergeSort(&L2);
	*arr = merge(L1, L2);
	print(*arr);
	free(partitioned_arr);
}
int main() {
	int n,number;
	node* arr = NULL, *p = NULL;
	
	scanf("%d", &n);

	while(n){
		scanf("%d", &number);
		
		if (arr == NULL) {
			arr = getNode(number);
			p = arr;
			n -= 1;
			continue;
		}

		p->next = getNode(number);
		p = p->next;
		n -= 1;
	}
	mergeSort(&arr);
	print(arr);
}