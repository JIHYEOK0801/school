#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
struct stack {
	int top;
	int capacity;
	int* data;
};
typedef struct stack stackType;
int is_full(stackType* s) {
	if (s->top >= s->capacity - 1) {
		return 1;
	}
	else return 0;
}
void init_stack(stackType* s) {
	s->top = -1;
	s->capacity = 1;
	s->data = (int*)malloc(s->capacity * sizeof(int));
}
void push(stackType* s, int element) {
	if (is_full(s)) {
		s->capacity *= 2;
		s->data = (int*)realloc(s->data, s->capacity * sizeof(int));
	}
	s->data[++(s->top)] = element;
}
int main() {
	stackType st;
	init_stack(&st);

	int n;
	while (1) {
		scanf("%d", &n);
		if (n == -1)break;
		push(&st, n);
	}
	int i;
	for (i = 0; i <= st.top; i++) {
		printf("%d ", st.data[i]);
	}

}