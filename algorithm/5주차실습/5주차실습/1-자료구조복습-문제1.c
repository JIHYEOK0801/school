//버퍼 신경쓰기!!
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	char elem;
	struct node* prev, * next;
}node;
typedef struct linkedlist{
	int scale;
	struct node* H, * T;
}linkedlist;
node* makeNewNode(char element) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->prev = NULL;
	newnode->next = NULL;
	newnode->elem = element;
}
void init(linkedlist* list) {
	list->scale = 0;
	list->H = makeNewNode('H');
	list->T = makeNewNode('T');
	list->H->next = list->T;
	list->T->prev = list->H;
}
void add(linkedlist* list, int index, char element) {
	node* newnode = makeNewNode(element);

	int i;
	node* p = list->H;
	for (i = 0; i < index; i++) {
		p = p->next;
	}
	p->prev->next = newnode;
	newnode->prev = p->prev;

	p->prev = newnode;
	newnode->next = p;
}
void print(linkedlist* list) {
	node* p = list->H->next;
	while (p->next != NULL) {
		printf("%c",p->elem);
		p = p->next;
	}
	printf("\n");
}
void get_entry(linkedlist* list, int index) {
	node* p = list->H;
	int i;
	for (i =0 ;i<index ; i++){
		p = p->next;
	}
	printf("%c\n", p->elem);
}
void delete(linkedlist* list, int index) {
	node* p = list->H;
	int i;
	for (i = 0; i < index; i++) {
		p = p->next;
	}
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
}
int main() {
	linkedlist list;
	init(&list);
	int n;
	scanf("%d", &n);
	int i;
	int index;
	char command, element;
	for (i = 0; i < n; i++) {
		scanf(" %c", &command);
		switch (command) {
			case 'A':
				scanf("%d %c", &index, &element);
				if ((index > list.scale + 1)||(index < 1)) printf("invalid position\n");
				else {
					add(&list, index, element);
					list.scale += 1;
				}
				break;
			case 'D':
				scanf("%d", &index);
				if ((index > list.scale) || (index < 1)) printf("invalid position\n");
				else {
					delete(&list, index);
					list.scale -= 1;
				}
				break;
			case 'G':
				scanf("%d", &index);
				if ((index > list.scale) || (index < 1)) printf("invalid position\n");
				else {
					get_entry(&list, index);
				}
				break;
			case 'P':
				print(&list);
				break;
		}
		printf("%d ", list.scale);
		printf("%d번째 명령수행 완료\n\n", i);
	}

	
}