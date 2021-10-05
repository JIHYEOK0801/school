#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void print(int arr[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
	printf("\n");
}
int findPivot(int l, int r) {
	int index = l + rand() % (r-l);
	return index;
}

void swapElement(int arr[], int i1, int i2) {
	int temp = arr[i1];
	arr[i1] = arr[i2];
	arr[i2] = temp;
}

int* inPlacePartition(int arr[], int l, int r, int k) {
	int p = arr[k]; // pivot ����

	swapElement(arr, k, r); // hide pivot

	int i = l;
	int j = r - 1; // r�� pivot�� ��ġ�ϹǷ� r-1

	while (i <= j) {
		while (i <= j && arr[i] < p) 
			i = i + 1;
		while (j >= i && arr[j] >= p)
			j = j - 1;
		if (i < j)
			swapElement(arr, i, j);
	}
	int a = i;
	j = r - 1;
	while (i <= j) {
		while (i <= j && arr[i] == p) {
			i += 1;
		}
		while (j >= i && arr[j] > p) {
			j -= 1;
		}
		if (i < j)
			swapElement(arr, i, j);
	}
	swapElement(arr, i, r); // pivot ���ڸ��� ��ġ
	int b = i;

	

	int* ab = (int*)malloc(sizeof(int) * 2);
	if (ab == NULL) {
		printf("ab�����Ҵ繮��");
		exit(0);
	}
	ab[0] = a; ab[1] = b;

	return ab;
}

void inPlaceQuickSort(int arr[], int l, int r) {
	if (l >= r)return;
	int k= findPivot(l, r);
	//printf("pivot %d�� inPlacePartition �մϴ�.\n", arr[k]);
	int* ab = inPlacePartition(arr, l, r, k);
	//print(arr, 8);
	//printf("[%d %d][%d %d] ���� inPlaceQuickSort ��� �����մϴ�.\n\n",l, ab[0], ab[1], r);
	inPlaceQuickSort(arr, l, ab[0] - 1);
	inPlaceQuickSort(arr, ab[1] + 1, r);
	free(ab);
}



int main() {
	int n, *arr, i, number;
	//�迭 �ʱ�ȭ
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int) * n);
	if (arr == NULL) {
		printf("arr�޸� ����");
		return;
	}

	for (i = 0; i < n; i++) {
		scanf("%d", &number);
		arr[i] = number;
	}
	
	//������
	srand(time(NULL));
	inPlaceQuickSort(arr, 0, n - 1);
	print(arr,n);
	free(arr);
}
