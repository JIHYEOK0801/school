
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
	int auth = 0;
	char passwd[20];
	printf("\n\n     패스워드 :");
	gets(passwd);

	auth = 1;
	if (auth){ 
		printf("     인증 성공!\n"); 
		printf("     Segmentation Fault (core dumped)\n");
	}
		
	else
		printf("인증 실패!\n");
}