#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char elem;
	struct node* next;
}node;

node* createNode(char elem){
	node* newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL) {
		printf("�޸𸮺���\n");
	}
	//newnode �ʱ�ȭ
	newnode->elem = elem;
	newnode->next = NULL;
	return newnode;
}

typedef struct listType {
	node* head;
}listType;

void init(listType* list) {
	list->head = createNode('H');
	node* p = list->head;
	node* newnode;
	int i;
	for (i = 0; i < 10; i++) {
		newnode = createNode('A' + i);
		p->next = newnode;
		p = p->next;
	}
}
void print(listType* list) {
	node* p = list->head->next;
	while (p != NULL) {
		printf("%c ", p->elem);
		p = p->next;
	}
	printf("\n");
}

void swap1(listType *list, int p, int q) {
	node* pointer = list->head,*temp;
	int i;
	for (i = 0; i < p-1; i++) {
		pointer = pointer->next;
	}
	temp = pointer->next->next;
	printf("������ġ:%c, ���� %c %c�� ��ġ�� �ٲߴϴ�.\n", pointer->elem,pointer->next->elem, pointer->next->next->elem);

	pointer->next->next = pointer->next->next->next;
	temp->next = pointer->next;
	pointer->next = temp;
	
}
int main() {
	int index_1, index_2;
	listType list;
	init(&list);
	print(&list);
	printf("��ȯ�� ��ġ : ");
	scanf("%d %d", &index_1, &index_2);
	swap1(&list, index_1, index_2);
	print(&list);
}