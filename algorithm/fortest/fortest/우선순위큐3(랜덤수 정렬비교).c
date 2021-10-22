#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
void swap(int* arr, int index1, int index2) {
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}
void insertionSort(int *arr, int n) {
	int i, j;

	for (i = 1; i < n; i++) {
		for (j = i - 1; j >= 0; j--) {
			if (arr[j + 1] > arr[j])break;
			swap(arr, j, j + 1);
		}
	}
}
void selectionSort(int* arr, int n) {
	int i, j;

	int mini;
	for (i = 0; i < n - 1; i++) {
		mini = i;
		for (j = i + 1; j < n; j++) {
			if (arr[j] < arr[mini])
				mini = j;
		}
		swap(arr, i, mini);
	}
}

void makeReverse(int* arr, int n) {
	int i;
	int* temp = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		temp[i] = arr[i];
	}
	for (i = 0; i < n ; i++) {
		arr[i] = temp[n - i - 1];
	}
}
int main() {
	srand(time(NULL));
	int n,i,number;
	scanf("%d", &n);
	int* a, * b;
	a = (int*)malloc(sizeof(int) * n);
	b = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) {
		number = rand() % 100000;
		a[i] = number;
		b[i] = number;
	}

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	// 시간을 측정하고 싶은 작업(예: 함수 호출)을 이곳에 삽입
	selectionSort(a, n);
	QueryPerformanceCounter(&end);
	// 측정값으로부터 실행시간 계산
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("1. selectionsort time: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	// 시간을 측정하고 싶은 작업(예: 함수 호출)을 이곳에 삽입
	insertionSort(b, n);
	QueryPerformanceCounter(&end);
	// 측정값으로부터 실행시간 계산
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("1. insertionsort time: %.12f sec\n\n\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	// 시간을 측정하고 싶은 작업(예: 함수 호출)을 이곳에 삽입
	selectionSort(a, n);
	QueryPerformanceCounter(&end);
	// 측정값으로부터 실행시간 계산
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("2. selectionsort time: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	// 시간을 측정하고 싶은 작업(예: 함수 호출)을 이곳에 삽입
	insertionSort(b, n);
	QueryPerformanceCounter(&end);
	// 측정값으로부터 실행시간 계산
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("2. insertionsort time: %.12f sec\n\n\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	makeReverse(a, n);
	makeReverse(b, n);

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	// 시간을 측정하고 싶은 작업(예: 함수 호출)을 이곳에 삽입
	selectionSort(a, n);
	QueryPerformanceCounter(&end);
	// 측정값으로부터 실행시간 계산
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("3. seletionsort time: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	// 시간을 측정하고 싶은 작업(예: 함수 호출)을 이곳에 삽입
	insertionSort(b, n);
	QueryPerformanceCounter(&end);
	// 측정값으로부터 실행시간 계산
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("3. insertionsort time: %.12f sec\n\n\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	return 0;
}