#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
	int a, b, n;
	char s[101];
	
	scanf("%d %d %d", &a, &b, &n);
	scanf("%s", s);

	int i;
	for (i = 0; i < strlen(s); i++) {
		switch (s[i]){
		case 'Y':
			a = (a + b) / 2 + 1;
			break;
		case 'N':
			b = (a + b) / 2;
			break;
		}
	}
	//printf("%d %d", a, b);
	printf("%d", a);
}