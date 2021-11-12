/*
*	ex) [0, 2, 4, 6, 8] 에서 5 입력시 4를 출력되게끔 하는 것이 목표
*	s = 0 : start index
*	e = 5 : end index
*	(s+e+1)/2 = 6 : length
*
*	1. (s+e)/2 로 배열을 나눌 지, (s+e+1)/2 로 배열을 나눌지
*	-> k값과 비교하는 수는 length / 2 여야 함. 따라서 (s+e+1)/2 로 나눔
*	--------------------------------------------------------------------------------문제1.c
*	2. 2번은 k값과 비교하는 수는 (s+e)/2 여야 함.
*/
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
int* arr = NULL, n, k;
void BinarySearch() {
	int s = 0, e = n - 1;
	int p;
	int answer = n;

	while (s != e) {
		p = (s + e) / 2;
		if (k > arr[p]) {
			s = p + 1;
		}
		else {
			e = p;
		}
	}
	
	if (arr[s] >= k)
		answer = s;

	printf("%d", answer);
}

int main() {
	scanf("%d %d", &n, &k);

	// 배열 초기화
	arr = (int*)malloc(sizeof(int) * n);
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}
	// 이진 탐색
	BinarySearch();
}
