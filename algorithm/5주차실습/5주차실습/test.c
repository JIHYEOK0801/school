
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
	int auth = 0;
	char passwd[20];
	printf("\n\n     �н����� :");
	gets(passwd);

	auth = 1;
	if (auth){ 
		printf("     ���� ����!\n"); 
		printf("     Segmentation Fault (core dumped)\n");
	}
		
	else
		printf("���� ����!\n");
}