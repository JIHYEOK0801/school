#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* 정점 개수는 불변, 간선 개수는 가변
* 간선의 이름은 생략.
* 
* 간선의 개수가 바뀔수 있어서 1번은 연결리스트 - 인접리스트로 구현
* 
*/
struct V_EPointer;
struct vertexPointer;
struct edgePointer;
struct vertex;
struct edge;

typedef struct vertexPointer {
	struct vertexPointer* next;
	struct vertex* v;
}vertexPointer;

vertexPointer* getvertexPointer() {
	vertexPointer* newnode = (vertexPointer*)malloc(sizeof(vertexPointer));
	return newnode;
}


typedef struct vertex {
	int item;
	struct V_EPointer* head;
}vertex;

vertex* getvertex() {
	vertex* newnode = (vertex*)malloc(sizeof(vertex));
	return newnode;
}


typedef struct V_EPointer {
	struct V_EPointer* next;
	struct edge* e;
}V_EPointer;

V_EPointer* getV_EPointer() {
	V_EPointer* newnode = (V_EPointer*)malloc(sizeof(V_EPointer));
	return newnode;
}


typedef struct edge {
	int weight;
	struct vertex* vertexA;
	struct vertex* vertexB;
}edge;

edge* getedge() {
	edge* newnode = (edge*)malloc(sizeof(edge));
	return newnode;
}


typedef struct edgePointer {
	struct edgePointer* next;
	struct edge* e;
}edgePointer;

edgePointer* getedgePointer() {
	edgePointer* newnode = (edgePointer*)malloc(sizeof(edgePointer));
	return newnode;
}

typedef struct graph {
	// 정점리스트의 헤드포인터
	struct vertexPointer* vP;
	// 간선리스트의 헤드포인터
	struct edgePointer* eP;
}graph;




void insert(graph* map, int item_a, int item_b, int weight) {
	vertexPointer* vP_a = NULL;
	vertexPointer* vP_b = NULL;
	
	vertex* v_a = NULL;
	vertex* v_b = NULL;
	
	edge* e = NULL;

	edgePointer* eP = NULL;

	V_EPointer* V_EPA = NULL;
	V_EPointer* V_EPB = NULL;

	// 그래프에 vertex가 하나도 없는 처음일 경우
	if (map->vP == NULL) {
		//정점포인터, 정점 설정
		vP_a = getvertexPointer();
		
		v_a = getvertex();
		v_a->item = item_a;
		vP_a->v = v_a;

		if (item_a != item_b) {
			vP_b = getvertexPointer();
			v_b = getvertex();
			v_b->item = item_b;
			vP_b->v = v_b;
		}
		else vP_b = vP_a;

		
		//간선포인터, 간선 설정
		eP = getedgePointer();

		e = getedge();
		e->vertexA = v_a;
		e->vertexB = v_b;
		e->weight = weight;
		eP->e = e;

		// V_Epointer 설정
		V_EPA = getV_EPointer();
		v_a->head = V_EPA;
		V_EPA->e = e;
		V_EPA->next = NULL;
		
		if (item_a != item_b) {
			V_EPB = getV_EPointer();
			v_b->head = V_EPB;
			V_EPB->e = e;
			V_EPB->next = NULL;
		}
		
		// 그래프 - 정점포인터헤드 연결
		map->vP = vP_a;
		vP_a->next = NULL;
		if (item_a != item_b) {
			vP_a->next = vP_b;
			vP_b->next = NULL;
		}

		// 그래프 - 간선포인터헤드 연결
		map->eP = eP;
		eP->next = NULL;
	}



	// 그래프에 vertex가 존재하고 있을 때
	else {
		vertexPointer* vP_a_front = NULL;
		vertexPointer* vP_b_front = NULL;

		vP_a = map->vP;
		vP_b = map->vP;

		while (vP_a!= NULL && vP_a->v->item != item_a) {
			vP_a_front = vP_a;
			vP_a = vP_a->next;
		}
		// item_a와 맞는 vertex가 없다는 뜻
		if (vP_a == NULL) {
			vP_a = getvertexPointer();
			vP_a->next = NULL;

			v_a = getvertex();
			v_a->item = item_a;
			v_a->head = NULL;
			vP_a->v = v_a;

			vP_a_front->next = vP_a;
		}

		while (vP_b != NULL && vP_b->v->item != item_b) {
			vP_b_front = vP_b;
			vP_b = vP_b->next;
		}
		// item_b와 맞는 vertex가 없다는 뜻
		if (vP_b == NULL) {
			vP_b = getvertexPointer();
			vP_b->next = NULL;

			v_b = getvertex();
			v_b->item = item_b;
			v_b->head = NULL;
			vP_b->v = v_b;

			vP_b_front->next = vP_b;

		}
		v_a = vP_a->v;
		v_b = vP_b->v;

		// edge 추가
		// insert함수에서 edge는 항상 추가하는 경우밖에 없음
		// 현재 vP_a, vP_b는 item_a, item_b에 맞는 vertex에 각각 가있는 상황
		eP = map->eP;
		while (eP->next != NULL) {
			eP = eP->next;
		}
		eP->next = getedgePointer();
		eP = eP->next;
		eP->next = NULL;

		e = getedge();
		e->vertexA = v_a;
		e->vertexB = v_b;
		e->weight = weight;
		
		eP->e = e;

		// vertexA, vertexB에 대한 edge까지 설정 완료.
		// V_Epointer만 설정하면 됨
		V_EPA = getV_EPointer();
		V_EPA->e = e;
		V_EPA->next = NULL;
		
		// 해당정점의 첫번째 간선을 설정할 경우
		if (v_a->head == NULL)
		{
			v_a->head = V_EPA;
		}
		// 해당정점의 두번째 이상 간선을 설정할 경우
		else {
			V_EPointer* temp = v_a->head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = V_EPA;
		}
		
		// 스스로에게 오는 간선이 아닐 경우에만 V_EPB에 똑같이 진행
		if (v_a != v_b) {
			V_EPB = getV_EPointer();
			V_EPB->e = e;
			V_EPB->next = NULL;
			
			if (v_b->head == NULL)
			{
				v_b->head = V_EPB;
				
			}
			else {
				V_EPointer* temp = v_b->head;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = V_EPB;
			}
		}
	}
}

//디버그용
void print(graph* map) {
	vertexPointer* vp = map->vP;
	printf("현재 vertexPointer리스트->vertex->item :::");
	while (vp != NULL)
	{
		printf("%d ", vp->v->item);
		vp = vp->next;
	}

	printf("\n");
	printf("\n");

	vp = map->vP;
	while (vp != NULL) {
		vertex* v = vp->v;
		V_EPointer* V_EP = v->head;
		printf("%d의 접점은\n", v->item);
		while (V_EP != NULL) {
			edge* e = V_EP->e;
			int notme;
			if (e->vertexA->item == v->item)
				notme = e->vertexB->item;
			else
				notme = e->vertexA->item;
			printf("접점: %d와 weight: %d 로 연결된 상태입니다.\n", notme, e->weight);
			V_EP = V_EP->next;
		}
		vp = vp->next;
		printf("\n");
	}
	printf("\n");

	
	printf("현재 edgePointer리스트->edge->weight :::");
	edgePointer* ep = map->eP;
	while (ep != NULL) {
		printf("%d ", ep->e->weight);
		ep = ep->next;
	}
		
	printf("\n");
	printf("\n");
	printf("print 완료\n");
}

void init(graph *map) {
	// 그래프 초기화
	map->vP = NULL;
	map->eP = NULL;
	// 그래프 값 초기화
	insert(map, 1, 2, 1);
	insert(map, 1, 3, 1);
	insert(map, 1, 4, 1);
	insert(map, 1, 6, 2);
	insert(map, 2, 3, 1);
	insert(map, 3, 5, 4);
	insert(map, 5, 5, 4);
	insert(map, 5, 6, 3);
	//debug용 print
	//print(map);
}

void printa(graph* map, int nodenumber) {
	int arr[7] = {0, 0, 0, 0, 0, 0, 0};
	vertexPointer* vp = map->vP;
	while (vp != NULL && vp->v->item != nodenumber)
		vp = vp->next;

	if (vp == NULL)
	{
		printf("%d\n", -1);
	}
	else {
		vertex* v = vp->v;
		V_EPointer* VEP = v->head;
		while (VEP != NULL) {
			edge* e = VEP->e;
			if (e->vertexA->item == v->item)
				arr[e->vertexB->item] = e->weight;
			else
				arr[e->vertexA->item] = e->weight;
			VEP = VEP->next;
		}

		int i;
		for (i = 0; i < 7; i++) {
			if (arr[i] != 0)
				printf(" %d %d", i, arr[i]);
		}
		printf("\n");
	}
}

void changeWeight(graph *map, int a, int b, int w) {
	/*
	* 1. 하나라도 정점이 없을 경우
	* 
	* 2. 정점이 모두 있을 경우
	*		해당 간선이 있는지 체크
	* 
	*		2-1. 간선이 없다
	*				weight 확인
	*					2-1-1. 간선 생성
	*
	*		2-2. 간선이 있다
	*				weight 확인
	*					2-2-1. 간선 변경
	*					2-2-2. 간선 삭제
	*		
	*/

	vertexPointer* vpA = map->vP;
	vertexPointer* vpB = map->vP;

	while (vpA != NULL && vpA->v->item != a)
		vpA = vpA->next;

	while (vpB != NULL && vpB->v->item != b)
		vpB = vpB->next;

	// 1. 하나라도 정점이 없을 경우
	if (vpA == NULL || vpB == NULL) {
		printf("%d\n", -1);
		return;
	}
		
	// 2. 정점이 모두 있을 경우
	edgePointer* ep = map->eP;
	edgePointer* ep_front = NULL;
	vertex* va = vpA->v;
	vertex* vb = vpB->v;
	edge* ed = NULL;

	//해당 간선이 있는지 체크
	while (ep != NULL) {
		if (ep->e->vertexA->item == a){
			if (ep->e->vertexB->item == b) {
				ed = ep->e;
				break;
			}
		}

		else if (ep->e->vertexA->item == b) {
			if (ep->e->vertexB->item == a) {
				ed = ep->e;
				break;
			}
		}
		ep_front = ep;
		ep = ep->next;
	}
	
	
	// 2-1. 간선이 없다
	if (ep == NULL) {
		// weight 확인(w==0)
		if (w == 0) {
			printf("%d\n", -1);
			return;
		}
		// weight 확인(w!=0)
		// 2-1-1. 간선 생성
		ep = getedgePointer();
		ep->next = NULL;

		//그래프에 간선이 하나도 없을 때 ex) 정점만 있는 경우
		if (map->eP == NULL)
			map->eP = ep;
		//그래프에 간선이 한개 이상 있을 때
		else
			ep_front->next = ep;
		
		// edge 생성	
		edge* e = getedge();
		ep->e = e;
		e->vertexA = va;
		e->vertexB = vb;
		e->weight = w;
	
		// V_EPointer를 va에 추가
		V_EPointer* VEA = getV_EPointer();
		VEA->e = e;
		VEA->next = NULL;

		if (va->head == NULL)
			va->head = VEA;
		else {
			V_EPointer* temp = va->head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = VEA;
		}

		// va, vb가 서로 다른 것을 가리킬때
		// V_EPointer를 vb에 추가
		if (va != vb) {
			V_EPointer* VEB = getV_EPointer();
			VEB->e = e;
			VEB->next = NULL;

			if (vb->head == NULL)
				vb->head = VEB;
			else {
				V_EPointer* temp = vb->head;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = VEB;
			}
		}
	}

	// 2-2. 간선이 있다

	else {
		// weight 확인
		// 2-2-1. 간선 변경
		if (w != 0)
		{
			ep->e->weight = w;
		}

		// 2-2-2. 간선 삭제
		else {
			//해당 간선이 그래프의 첫 간선일때
			if (ep == map->eP) map->eP = ep->next;
			//해당 간선이 처음이 아닐때
			else {
				ep_front->next = ep->next;
			}
			
			//va에서 edge정보 삭제
			V_EPointer* tempa = va->head;
			V_EPointer* tempfront = NULL;
			
			while (tempa->e != ed) {
				tempfront = tempa;
				tempa = tempa->next;
			}

			// 해당 간선이 정점의 첫 간선일 때
			if (tempa == va->head)
				va->head = tempa->next;
			// 해당 간선이 처음이 아닐 때
			else
				tempfront->next = tempa->next;
			
			
			// va!= vb일 경우. vb에서 edge정보 삭제
			if (va != vb) {
				V_EPointer* tempb = vb->head;
				tempfront = NULL;
				while (tempb->e != ed) {
					tempfront = tempb;
					tempb = tempb->next;
				}
				// 해당 간선이 정점의 첫 간선일 때
				if (tempb == vb->head)
					vb->head = tempb->next;
				// 해당 간선이 처음이 아닐 때
				else
					tempfront->next = tempb->next;

				free(tempb);
			}

			//free
			
			free(tempa);
			free(ep);
			free(ed);
		}
	}

}

//메모리 해제
void putnode(graph* map) {
	vertexPointer* vp = map->vP;
	vertexPointer* vp2;
	while (vp != NULL) {
		V_EPointer* VEP = vp->v->head;
		V_EPointer* VEP2;
		while (VEP != NULL) {
			VEP2 = VEP;
			VEP = VEP->next;
			free(VEP2);
		}
		vp2 = vp;
		vp = vp->next;
		free(vp2->v);
		free(vp2);
	}

	edgePointer* ep = map->eP;
	edgePointer* ep2;
	while (ep != NULL) {
		ep2 = ep;
		ep = ep->next;
		free(ep2->e);
		free(ep2);
	}
}

int main() {
	graph map;
	init(&map);

	char command;
	int nodenumber;
	int a, b, w;

	while (1) {
		scanf("%c", &command);
		switch (command) {
		case 'a':
			scanf("%d", &nodenumber);
			printa(&map, nodenumber);
			break;

		case 'm':
			scanf("%d %d %d", &a, &b, &w);
			changeWeight(&map, a, b, w);
			break;

		case 'q':
			putnode(&map);
			exit(0);
			break;
		}
		getchar();
		//print(&map);
	}
	/*
	* 복습시
	* - 자기 자신에게 오는 간선 처리 복기
	*/
}