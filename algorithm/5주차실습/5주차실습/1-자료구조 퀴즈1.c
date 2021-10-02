#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
	char elem[11];
	int n;
	struct node* next;
}node;

typedef struct stackType {
	node* p;
}stackType;

void push(stackType *stack, char *word){
	node* newnode = (node*)malloc(sizeof(node));
	strcpy(newnode->elem,word);
	newnode->next = NULL;


	if (stack->p == NULL) {
		stack->p = newnode;
	}
	else {
		newnode->next = stack->p;
		stack->p = newnode;
	}

}
void pop(stackType* stack) {
	printf("%s\n", stack->p->elem);
	stack->p = stack->p->next;
}
void printall(stackType* stack) {
	node* pointer = stack->p;
	while (pointer != NULL) {
		printf("%s ", pointer->elem);
		pointer = pointer->next;
	}
	printf("\n");
}

int main() {
	char word[11];
	stackType stack; // 스택 생성
	stack.p = NULL; // 리스트 초기화

	while (1)
	{
		scanf("%s", word);
		if (strcmp(word, "*") == 0) {
			while (stack.p != NULL)
			{
				pop(&stack);
			}
			break;
		}
		else {
			push(&stack, word);
			//printall(&stack);
		}
		
	}
}