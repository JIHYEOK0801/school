
//selection sort
/*
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
void swap(int* arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
void print(int* arr, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
}
int main(){
	int n, i, j, number,*arr= NULL;
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) {
		scanf("%d", &number);
		arr[i] = number;
	}

	int min;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		swap(arr, i, min);
	}
	print(arr, n);
	free(arr);
}*/

//insertionsort
/*
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
void swap(int* arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void print(int* arr, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
}

int main() {
	int i, j, n, number;
	int* arr = NULL;

	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++) {
		scanf("%d", &number);
		arr[i] = number;
	}

	for (i = 1; i < n; i++) {
		for (j = i - 1; j >= 0; j--) {
			if (arr[j] > arr[j+1]) {
				swap(arr, j, j+1);
			}
		}
	}

	print(arr, n);
}
*/

//heapsort
/*
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct heapType {
	int h[100];
	int top;
}heapType;

void init(heapType* heap) {
	heap->top = 1;
}

void print(heapType* heap, int n) {
	int i;
	for (i = 1; i <= n; i++) {
		printf(" %d", heap->h[i]);
	}
	printf("\n");
}

void swap(heapType* heap, int i, int j) {
	int temp = heap->h[i];
	heap->h[i] = heap->h[j];
	heap->h[j] = temp;
}

void upheap(heapType* heap, int v) {
	if (v == 1) return; // root일 경우
	if (heap->h[v / 2] > heap->h[v]) return; //이미 최대힙 구조를 띔
	swap(heap, v / 2, v);
	upheap(heap, v / 2);
}

void insertHeap(heapType* heap, int number) {
	heap->h[heap->top] = number;
	upheap(heap, heap->top);
	heap->top += 1;
}

void downheap(heapType* heap, int r) {
	int left = r * 2;
	int right = r * 2 + 1;

	if (left > heap->top) return;
	
	int bigger = left;
	if (right <= heap->top) {
		if (heap->h[right] > heap->h[bigger])
			bigger = right;
	}

	if (heap->h[r] > heap->h[bigger]) return;
	
	swap(heap, r, bigger);

	downheap(heap, bigger);
}

void removeRoot(heapType* heap) {
	swap(heap, 1, heap->top);
	heap->top -= 1;
	downheap(heap, 1);
	
}

int main() {
	heapType heap;
	init(&heap);
	int i, n, number;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &number);
		insertHeap(&heap, number);
	}
	
	heap.top -= 1;

	while (heap.top > 0) {
		print(&heap, n);
		removeRoot(&heap);
	}

	print(&heap, n);

}
*/

//merge sort
/*
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int number;
	struct node* next;
}node;

typedef struct L1L2type {
	node* L1, * L2;
}L1L2type;

node* getNode(int number) {
	node* newNode = NULL;
	newNode = (node*)malloc(sizeof(node));
	newNode->number = number;
	newNode->next = NULL;
	return newNode;
}

void print(node* p) {
	while (p != NULL) {
		printf(" %d", p->number);
		p = p->next;
	}
}

L1L2type* partition(node* L, int k) {
	node* p = L, * q = L, *temp = NULL;
	int i;
	for (i = 0; i < k; i++) {
		temp = q;
		q = q->next;
	}
	temp->next = NULL;
	
	L1L2type* L1L2 = (L1L2type*)malloc(sizeof(L1L2type));
	L1L2->L1 = p;
	L1L2->L2 = q;
	return L1L2;
}

node* merge(node* L1, node* L2) {
	node* p = NULL, *head = NULL;
	if (L1->number < L2->number){
		p = L1;
		head = p;
		L1 = L1->next;
	}
		
	else{
		p = L2;
		head = p;
		L2 = L2->next;
	}
	

	while (L1 != NULL && L2 != NULL) {
		if (L1->number < L2->number) {
			p->next = L1;
			p = p->next;
			L1 = L1->next;
		}
		else{
			p->next = L2;
			p = p->next;
			L2 = L2->next;
		}
	}

	while (L1 != NULL) {
		p->next = L1;
		p = p->next;
		L1 = L1->next;
	}
	while (L2 != NULL) {
		p->next = L2;
		p = p->next;
		L2 = L2->next;
	}

	return head;
}

void mergeSort(node** list) {
	int count = 0;
	node* p = *list;
	while (p != NULL) {
		p = p->next;
		count += 1;
	}
	if (count <= 1) return;

	L1L2type* L1L2 = partition(*list, count / 2);
	node* L1 = L1L2->L1;
	node* L2 = L1L2->L2;
	mergeSort(&L1);
	mergeSort(&L2);
	*list = merge(L1, L2);

	free(L1L2);
}

int main() {
	int i, n, number;
	node* p = NULL, *head = NULL;
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		scanf("%d", &number);

		if (p == NULL) {
			p = getNode(number);
			head = p;
			continue;
		}
		p->next = getNode(number);
		p = p->next;
	}
	
	mergeSort(&head);
	print(head);
	
	
	while (head != NULL) {
		p = head;
		head = head->next;
		free(p);
	}
}*/

//quick sort
/*
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int* arr, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
	printf("\n");
}

void swap(int* arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int findPivot(int l, int r) {
	int dif = r - l + 1;
	int pivot = l + rand() % dif;
	return pivot;
}

int* inPlacePartition(int* arr, int l, int r, int pivot) {
	swap(arr, pivot, r); //hide pivot
	int i = l, j = r - 1;
	int a, b;

	while (i <= j) {
		while (i<=j && arr[i] < arr[r])
			i += 1;
		while (i<=j && arr[j] >= arr[r])
			j -= 1;
		if (i < j)
			swap(arr, i, j);
	}

	a = i;
	j = r - 1;

	while (i <= j) {
		while (i <= j && arr[i] == arr[r])
			i += 1;
		while (i <= j && arr[j] > arr[r])
			j -= 1;
		if (i < j)
			swap(arr, i, j);
	}

	b = i;

	swap(arr, i, r);

	int* ab = (int*)malloc(sizeof(int) * 2);
	ab[0] = a-1;
	ab[1] = b+1;
	return ab;
}

void quickSort(int* arr, int l, int r) {
	if (l >= r)return;
	int pivot = findPivot(l, r);
	int* ab = inPlacePartition(arr, l, r, pivot);
	int a = ab[0];
	int b = ab[1];
	quickSort(arr, l, a);
	quickSort(arr, b, r);	
	free(ab);
}

int main() {
	int i, n, *arr;
	scanf("%d", &n);

	arr = (int*)malloc(sizeof(int) * n);

	srand(time(NULL));
	for (i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}

	quickSort(arr, 0, n - 1);
	print(arr, n);
	free(arr);
}
*/

//b Search
/*
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
int maxBsearch(int* arr, int l, int r, int k) {
	int mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (k >= arr[mid])
			l = mid + 1;
		else
			r = mid - 1;
	}

	return r;
}
int minBsearch(int* arr, int l, int r, int k) {
	int mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (k > arr[mid])
			l = mid + 1;
		else
			r = mid - 1;
	}

	return l;
}
int main() {
	int n, k;
	scanf("%d %d", &n, &k);

	int* arr = (int*)malloc(sizeof(int) * n);

	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}

	int answer1 = maxBsearch(arr, 0, n - 1, k);
	int answer2 = minBsearch(arr, 0, n - 1, k);
	printf(" %d %d", answer1, answer2);
}*/

//상향식 힙 생성
/*
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
void swap(int* heap, int i, int j) {
	int temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;
}

void downheap(int *heap, int root, int n) {
	int left = root * 2;
	int right = root * 2 + 1;
	
	if (left > n) return;
	int bigger = left;
	if (right <= n) {
		if (heap[right] > heap[bigger]) {
			bigger = right;
		}
	}

	if (heap[root] > heap[bigger]) return;

	swap(heap, root, bigger);
	downheap(heap, bigger, n);
}

void buildHeap(int* heap, int root, int n) {
	if (root > n) return;

	int left = root * 2;
	int right = root * 2 + 1;

	buildHeap(heap, left, n);
	buildHeap(heap, right, n);
	downheap(heap, root, n);
}

int main() {
	int n, i, * heap;
	scanf("%d", &n);
	heap = (int*)malloc(sizeof(int) * (n + 1));

	for (i = 1; i <= n; i++) {
		scanf("%d", heap + i);
	}

	buildHeap(heap, 1, n);
	
	for (i = 1; i <= n; i++)
		printf(" %d", heap[i]);
}
*/
/*
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	int number;
	struct node* next;
}node;

typedef struct L1L2Type {
	node* L1, * L2;
}L1L2Type;

void print(node* p) {
	while (p != NULL) {
		printf(" %d", p->number);
		p = p->next;
	}
	printf("\n");
}

node* getNode(int n) {
	node* p = (node*)malloc(sizeof(node));
	p->number = n;
	p->next = NULL;
	return p;
}

L1L2Type* partition(node* L, int k) {
	node* p = L, * q = L, *temp = NULL;
	int i;
	for (i = 0; i < k; i++) {
		temp = q;
		q = q->next;
	}
	temp->next = NULL;

	L1L2Type* L1L2 = (node*)malloc(sizeof(node));
	L1L2->L1 = p;
	L1L2->L2 = q;
	return L1L2;
}

node* merge(node* L1, node* L2) {
	node* p = NULL, * head = NULL;
	if (L1->number < L2->number) {
		p = L1;
		L1 = L1->next;
	}
	else {
		p = L2;
		L2 = L2->next;
	}

	head = p;

	while (L1 != NULL && L2 != NULL) {
		if (L1->number < L2->number) {
			p->next = L1;
			L1 = L1->next;
			p = p->next;
		}
		else{
			p->next = L2;
			L2 = L2->next;
			p = p->next;
		}
	}

	while (L1 != NULL) {
		p->next = L1;
		L1 = L1->next;
		p = p->next;
	}
	while (L2 != NULL) {
		p->next = L2;
		L2 = L2->next;
		p = p->next;
	}

	return head;
}

void mergeSort(node** L) {
	int count = 0;
	node* p = *L;
	while (p != NULL) {
		count += 1;
		p = p->next;
	}
	if (count <= 1) return;

	L1L2Type* L1L2 = partition(*L, count / 2);
	node* L1 = L1L2->L1;
	node* L2 = L1L2->L2;
	mergeSort(&L1);
	mergeSort(&L2);
	*L = merge(L1, L2);

	free(L1L2);
}

int main() {
	int n;
	scanf("%d", &n);

	node* p = NULL;
	
	node* head = NULL;
	int i,number;
	for (i = 0; i < n; i++) {
		scanf("%d", &number);
		if (p == NULL) {
			p = getNode(number);
			head = p;
		}
		else {
			p->next = getNode(number);
			p = p->next;
		}
	}

	mergeSort(&head);
	print(head);

	p = head;
	while (p != NULL) {
		p = p->next;
		free(head);
		head = p;
	}
}
*/


#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int* arr, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
	printf("\n");
}

int findPivot(int l, int r) {
	int dif = r - l + 1;
	int pivot = l + rand() % dif;
	return pivot;
}

void swap(int* arr, int l, int r) {
	int temp = arr[l];
	arr[l] = arr[r];
	arr[r] = temp;
}

int* partition(int* arr, int l, int r, int k) {
	
	swap(arr, k, r); //hide pivot

	int i = l, j = r - 1;
	while (i <= j) {
		while (i <= j && arr[i] <= arr[r])
			i += 1;
		while (i <= j && arr[j] >= arr[r])
			j -= 1;
		if (i < j)swap(arr, i, j);
	}
	swap(arr, i, r);

	int* ab = (int*)malloc(sizeof(int) * 2);
	ab[0] = i - 1;
	ab[1] = i + 1;
	return ab;
}

void quickSort(int* arr, int l, int r) {
	if (l >= r) return;
	int k = findPivot(l, r);
	int* ab = partition(arr, l, r, k);
	quickSort(arr, l, ab[0]);
	quickSort(arr, ab[1], r);
	free(ab);
}

int main() {
	srand(time(NULL));
	int n;
	scanf("%d", &n);

	int* arr = NULL;
	arr = (int*)malloc(sizeof(int) * n);

	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}
	
	quickSort(arr, 0, n - 1);
	print(arr, n);
	free(arr);
}