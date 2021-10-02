/*
* ::: 문제 조건 :::
* 1. '주어진 숫자들이 나타내는 heap' ---> input 배열은 최대힙 or 최소힙
* 2. '내부노드가 하나도 없는 경우는 없다' ---> heap 원소가 2개 이상이다.
* 3. '중복 숫자는 없다고 가정' ---> 중복 생각 x
*/
/*
* 최소시간 수정용
* 1. 노드 1개마다 자식 2개와 비교하면서 내려가게 되면 대략 O(2N) 정도
* 2. 최소힙, 최대힙, 힙구조를 보장받지 못한상태에서 노드를 내려가면서 한개만 선택 불가. O(logN) 까지 줄이는 건 불가능이라 판단
* 3. 끝에서부터 하나씩 부모와 비교하는것도 O(N)정도 나오지 않을까?
*/


#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int isParentSmaller(int* heap, int parent, int child) {
	if (heap[parent] > heap[child])
		return 0;
	return 1;
}
void print(char* answer, int lastinnernode) {
	printf("%s\n%d", answer, lastinnernode);
}
int main() {
	int N, i, number, *heap;
	char answer[4];

	scanf("%d", &N);
	
	// heap 초기화
	heap= (int*)malloc(sizeof(int) * (N + 1));
	

	for (i = 1; i < N + 1; i++) {
		scanf("%d", &number);
		heap[i] = number;
	}

	// 마지막 내부노드부터 색출
	int lastinnernode = heap[N / 2];

	// 최소힙인지 검사
	
	for (i = N; i >= 2; i--) {
		if (!isParentSmaller(heap, i / 2, i)){
			print("No", lastinnernode);
			return;
		}
			
	}
	print("Yes", lastinnernode);
}
