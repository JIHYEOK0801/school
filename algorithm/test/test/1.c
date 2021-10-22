// ip : 192.168.0.1
// pw : 4390
// 최종답안
/*
* 1. 과목 ID 오름차순으로 정렬
* 2. 같은 과목 ID면 입력순 (안정적이어야함) 
* 3. 제자리 정렬이어야함.
* 4. 정렬은 1번.
* 5. 시간 복잡도가 NlogN, 공간 복잡도 N, 안정적이어야함, 제자리정렬.
* --> 리스트를 활용한 합병정렬이 알맞다고 생각.
*/
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
	char c_id[11]; // 클래스 iD
	char c_name[21]; // 클래스 name
	char s_id[9]; // student id
	struct student* next;
}student;

student* getNode(char* c_id, char* c_name, char* s_id) {
	student* p = (student*)malloc(sizeof(student));
	strcpy(p->c_id, c_id);
	strcpy(p->c_name, c_name);
	strcpy(p->s_id, s_id);
	p->next = NULL;
	return p;
}

void print(student* p) {
	while (p != NULL) {
		printf("%s %s %s\n", p->c_id, p->c_name, p->s_id);
		p = p->next;
	}
	printf("\n");
}


void partition(student* L, int k, student **L1, student **L2) {
	student* p = L, *q = L, *temp = NULL;
	int i;

	// L1, L2 나눌곳 탐색
	for (i = 0; i < k; i++) {
		temp = q;
		q = q->next;
	}
	temp->next = NULL;
	*L1 = p;
	*L2 = q;
}

student* merge(student* L1, student* L2) {
	student* p = NULL, *head = NULL;
	if (strcmp(L1->c_id, L2->c_id) <= 0) {
		p = L1;
		L1 = L1->next;
	}
	else {
		p = L2;
		L2 = L2->next;
	}

	head = p;
	while (L1 != NULL && L2 != NULL) {
		if (strcmp(L1->c_id, L2->c_id) <= 0) {
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

void mergeSort(student **L) {
	// 리스트의 길이 <= 1 이면 종료.
	int count = 0;
	student* p = *L;
	while (p != NULL) {
		count += 1;
		p = p->next;
	}
	if (count <= 1) return;

	// L1, L2의 부리스트로 나누어 mergeSort 재귀.
	student* L1 = NULL, * L2 = NULL;
	partition(*L, count / 2, &L1, &L2);
	mergeSort(&(L1));
	mergeSort(&(L2));
	*L = merge(L1, L2);
}

int main() {
	int n;
	scanf("%d", &n);

	int i;
	char c_id[11]; // 클래스 iD
	char c_name[21]; // 클래스 name
	char s_id[9]; // student id
	student* p = NULL, *head =NULL;

	// 리스트 초기화
	for (i = 0; i < n; i++) {
		scanf("%s %s %s", c_id, c_name, s_id);
		if (p == NULL) {
			p = getNode(c_id, c_name, s_id);
			head = p;
		}
		else {
			p->next = getNode(c_id, c_name, s_id);
			p = p->next;
		}
	}
	
	// 합병 정렬 시작
	mergeSort(&head);

	//print
	print(head);

	//메모리 해제
	p = head;
	while (p != NULL) {
		p = p->next;
		free(head);
		head = p;
	}
}

/*
요구사항
* 1. 과목(c_id)를 오름차순으로 정렬해라 --> strcmp를 사용하여 오름차순으로 정렬
* 
* 2. 정렬의 시간복잡도가 O(NlogN), 공간 복잡도 O(N), 같은 과목 ID일 경우 입력학생들 입력순대로 출력
* --> 정렬의 시간복잡도가 O(NlogN)이면서, 입력학생들의 순서를 유지해야 하므로 정렬에 안정성이 있으면서
* O(NlogN)인 합병정렬을 사용했다.
* 
* 또한 공간복잡도 O(N)이어야 하기 때문에 연결리스트를 활용하였고 정확히 입력받은 N만큼만 메모리를 동적할당하였으므로
* 이 조건 또한 만족한다.
* 
* 3. 그외 정렬을 1번만 사용, 배치를 위한 다른작업 추가
* -->해당 없음.
*/