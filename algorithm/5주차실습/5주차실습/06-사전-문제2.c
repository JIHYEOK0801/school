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

	// �迭 �ʱ�ȭ
	arr = (int*)malloc(sizeof(int) * n);
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}
	// ���� Ž��
	BinarySearch();
}
