#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct linkedlist
{
	int element;
	struct linkedlist* next;
};
typedef struct linkedlist Linkedlist;

Linkedlist*getnode() {
	Linkedlist *node;
	node = (Linkedlist*)malloc(sizeof(Linkedlist));
	if (node == NULL) {
		printf("메모리가 부족합니다.\n");
	}
	node->next = NULL;
	return node;
}
int main()
{
	Linkedlist head = { NULL, NULL };
	Linkedlist* newNode, * p = &head;
	int element = 0;
	int i;
	
	while (1) {
		scanf("%d", &element);
		if (element == 0) { break; }

		newNode = getnode();
		newNode->element = element;
		p->next = newNode;
		p = p->next;
	}
	
	p = head.next;
	while (p != NULL) {
		printf("%d ", p->element);
		p = p->next;
	}

}