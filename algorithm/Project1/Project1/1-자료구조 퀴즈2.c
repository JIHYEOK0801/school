#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void printReverse(char s[]) {
	char s_reverse[11] = { '\0', };
	int i;
	for (i = 0; i < strlen(s); i++) {
		s_reverse[i] = s[strlen(s) - 1 - i];
	}
	printf("%s\n", s_reverse);
}
void dequeue(char queue[][11]) {
	int i;
	printReverse(queue[0]);
	for (i = 0; queue[i][0] != '\0'; i++) {
		strcpy(queue[i], queue[i + 1]);
	}

}
int main() {
	char queue[100][11] = { '\0', };
	int i, j, size = 0;

	char word[11];
	for (i = 0; i < 100; i++) {
		scanf("%s",word);
		if (strcmp(word, "*") == 0) {
			while (size > 0) {
				dequeue(queue);
				size -= 1;
			}
			break;
		}
		else {
			strcpy(queue[i], word);
			size += 1;
		}
		
	}
}