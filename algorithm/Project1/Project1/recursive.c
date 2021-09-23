#pragma warning (disable:4996)
#include <stdio.h>
int plus(int n) {
	if (n == 1) {
		return n;
	}
	else {
		return n + plus(n - 1);
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	int answer;
	answer = plus(n);
	printf("%d",answer);
}