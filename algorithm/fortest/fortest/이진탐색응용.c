#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
	int a, b, n, i, mid;
	char command[100];
	scanf("%d %d %d %s", &a, &b, &n, command);
	for (i = 0; i < strlen(command); i++) {
		mid = (a + b) / 2;
		if (command[i] == 'Y') {
			a = mid + 1;
		}
		else {
			b = mid;
		}
	}
	printf("%d %d", a, b);
}