#include <stdio.h>
int main() {
	int a[2] = { 1,2 };
	int* p[2];
	p[0] = &a[0];
	p[1] = &a[1];
	printf("%p %p %p", p, &p, &p[0]);
}