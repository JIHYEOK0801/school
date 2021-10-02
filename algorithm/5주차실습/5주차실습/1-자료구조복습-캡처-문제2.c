#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int elem;
	struct node* next;
}node;

typedef struct NODE {
	node* first;
}NODE;

node* createNode(int n) {
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL) printf("메모리부족");

	newnode->elem = n;
	newnode->next = NULL;
}

void init(NODE* list) {
	int i;
	node* p = NULL,*newnode;
	for (i = 0; i < 10; i++) {
		if (i == 0) {
			list->first = createNode(i);
			p = list->first;
		}
		else {
			newnode = createNode(i);
			p->next = newnode;
			p = p->next;
		}
	}
	p->next = list->first;
}
void print(NODE* list) {
	int count = 0;
	node* p = list->first;
	while (count < 20) {
		printf("%d ", p->elem);
		p = p->next;
		count += 1;
	}
	printf("\n");
}
void findLast(NODE* L) {
	node* p = L->first->next;
	while (p->next->elem != L->first->elem) {
		p = p->next;
	}
	printf("%d", p->elem);
}
int main() {
	NODE list;
	init(&list);
	print(&list);
	NODE* L = &list;
	findLast(L);
	
}