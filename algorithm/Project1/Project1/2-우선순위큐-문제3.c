#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
void sortReverse(int* select, int* insert,int n) {
	int i;
	for (i = 0; i < n; i++) {
		select[i] = insert[n - 1 - i];
	}
	for (i = 0; i < n; i++) {
		insert[i] = select[i];
	}
}
void insertion(int* L, int j, int i) {
	int k;
	int temp = L[i];
	//j 이후로 i 까지 원소를 밀어내는 작업
	for (k = i; k > j; k--) {
		L[k] = L[k - 1];
	}
	//j에 삽입
	L[j] = temp;
}
void swap(int* L, int i, int j) {
	int temp;
	temp = L[i];
	L[i] = L[j];
	L[j] = temp;
}
int main() {
	int n;
	scanf("%d", &n);
	
	/*
	* 배열 초기화
	*/
	int* insert = (int*)malloc(sizeof(int) * n);
	int* select = (int*)malloc(sizeof(int) * n);

	int i,j;
	srand(time(NULL));
	for (i = 0; i < n; i++) {
		insert[i] = rand() % 10000;
		select[i] = insert[i];
	}
	
	/*
	* A번 -- slect, insert배열에 각각의 정렬 수행
	*/

	/*
	* A - 선택정렬 시작
	*/
	printf("A번\n");
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);

	int index = 0;
	int temp;
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j <= i; j++) {
			if (select[j] > select[index]) {
				index = j;
			}
		}
		swap(select, index, i);
		index = 0;
	}
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" selectionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	/*
	* A - 삽입정렬 시작
	*/
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			if (insert[i] < insert[j]) {
				insertion(insert, j, i);
				break;
			}
		}
	}	
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" insertionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	/*
	* B번 -- 정렬된 select, insert 배열에 다시한번 각각의 정렬 수행
	*/
	printf("\nB번\n");
	/*
	* B번 - 선택정렬
	*/
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	index = 0;
	temp;
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j <= i; j++) {
			if (select[j] > select[index]) {
				index = j;
			}
		}
		swap(select, index, i);
		index = 0;
	}
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" selectionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	/*
	* B번 - 삽입정렬
	*/
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			if (insert[i] < insert[j]) {
				insertion(insert, j, i);
				break;
			}
		}
	}
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" insertionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	
	/*
	* C번 -- 이미 정렬된 select, insert배열을 역순 정렬 후, 각각의 정렬 수행
	*/
	printf("\nC번\n");
	//역순정렬
	sortReverse(select, insert, n);

	/*
	* C번 - 선택정렬
	*/
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	index = 0;
	temp;
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j <= i; j++) {
			if (select[j] > select[index]) {
				index = j;
			}
		}
		swap(select, index, i);
		index = 0;
	}
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" selectionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	/*
	* C번 - 삽입정렬
	*/

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			if (insert[i] < insert[j]) {
				insertion(insert, j, i);
				break;
			}
		}
	}
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" insertionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	return 0;
}