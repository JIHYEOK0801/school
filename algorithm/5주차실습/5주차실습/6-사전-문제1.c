/*
*	ex) [0, 2, 4, 6, 8] ���� 5 �Է½� 4�� ��µǰԲ� �ϴ� ���� ��ǥ
*	s = 0 : start index
*	e = 5 : end index
*	(s+e+1)/2 = 6 : length
*
*	1. (s+e)/2 �� �迭�� ���� ��, (s+e+1)/2 �� �迭�� ������
*	-> k���� ���ϴ� ���� length / 2 ���� ��. ���� (s+e+1)/2 �� ����
*	--------------------------------------------------------------------------------����1.c
*	2. 2���� k���� ���ϴ� ���� (s+e)/2 ���� ��.
*/
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
int* arr = NULL, n, k;
void rBinarySearch(int s, int e) {
	if (s == e) {
		int answer = -1;
		if (arr[s] <= k)
			answer = s;
		printf(" %d", answer);
	}
	else {
		int p = (s + e + 1) / 2;
		if (k < arr[p]) {
			rBinarySearch(s, p-1);
		}
		else {
			rBinarySearch(p, e);
		}
	}
}

int main() {
	scanf("%d %d", &n, &k);
	
	// �迭 �ʱ�ȭ
	arr = (int*)malloc(sizeof(int) * n);
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}
	// ���� Ž��
	rBinarySearch(0, n-1);
	
}
