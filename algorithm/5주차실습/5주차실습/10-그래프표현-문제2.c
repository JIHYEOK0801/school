/*
* 정점 개수는 불변, 간선 개수는 가변
* 간선의 이름은 생략.
* 2번은 리스트 - 인접행렬로 구현
* 가중치에 0이 허용되지 않아서 가중치가 들어간 2차원 정수배열로 구현
*
*/
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertice {
	int id;
	int item;
	struct vertice* next;
}vertice;
vertice* getvertice() {
	vertice* newnode = (vertice*)malloc(sizeof(vertice));
	return newnode;
}

typedef struct edge {
	struct vertice* verticeA;
	struct vertice* verticeB;
	int weight;
	struct edge* next;
}edge;
edge* getedge() {
	edge* newnode = (edge*)malloc(sizeof(edge));
	return newnode;
}

typedef struct graph {
	int verticescount;
	vertice* verticelistHead;
	edge* edgelistHead;
	edge* map[6][6];
}graph;






void insertVertices(graph* g, int item) {
	vertice* p;
	if (g->verticelistHead == NULL) {
		p = getvertice();
		p->id = g->verticescount;
		p->item = item;
		p->next = NULL;

		g->verticescount += 1;
		g->verticelistHead = p;
	}
	else {
		p = g->verticelistHead;
		while (p->next != NULL) {
			p = p->next;
		}
		vertice* q = getvertice();
		q->id = g->verticescount;
		q->item = item;
		q->next = NULL;

		g->verticescount += 1;
		p->next = q;
	}
}

vertice* searchvertice(graph* g, int item) {
	vertice* p = g->verticelistHead;
	// graph에 정점이 하나도 없을 때
	if (p == NULL) return NULL;

	// graph에 정점이 있는데
	while (p != NULL && p->item != item) {
		p = p->next;
	}
	// vertice->item != item 일때
	if (p == NULL) return NULL;

	// vertice->item == item 일때
	return p;
}

edge* searchedge(graph* g, int a, int b) {
	edge* p = g->edgelistHead;
	// graph에 간선이 하나도 없을 때
	if (p == NULL) return NULL;

	// graph에 간선이 있어서 순회
	while (p != NULL) {
		if ((p->verticeA->item == a && p->verticeB->item == b) || (p->verticeA->item == b && p->verticeB->item == a) )
				break;
		p = p->next;
	}
	// edge->weight != weight 일때(발견 못했을 때)
	if (p == NULL) return NULL;

	// edge->weight == weight 일때(발견 했을 때)
	return p;
}

void insertEdges(graph* g, int va_item, int vb_item, int weight) {
	edge* e;
	if (g->edgelistHead == NULL) {
		e = getedge();
		e->verticeA = searchvertice(g, va_item);
		e->verticeB = searchvertice(g, vb_item);
		e->weight = weight;
		e->next = NULL;

		g->edgelistHead = e;
	}
	else {
		edge* temp = g->edgelistHead;
		while (temp->next != NULL)
			temp = temp->next;

		e = getedge();
		e->verticeA = searchvertice(g, va_item);
		e->verticeB = searchvertice(g, vb_item);
		e->weight = weight;
		e->next = NULL;

		temp->next = e;
	}
}

void initmap(graph* g) {
	edge* e = g->edgelistHead;
	
	while (e != NULL) {
		int a = e->verticeA->id;
		int b = e->verticeB->id;
		g->map[a][b] = e;
		g->map[b][a] = e;
		e = e->next;
	}
}

void init(graph* g) {
	//1. 간선포인터 2차원배열 초기화
	int i, j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			g->map[i][j] = NULL;
		}
	}
	g->verticelistHead = NULL;
	g->edgelistHead = NULL;
	g->verticescount = 0;
	
	// 2. 모든 정점 넣기
	for (i = 1; i <= 6; i++) 
		insertVertices(g, i);
	
	// 3. 모든 간선 넣기
	insertEdges(g, 1, 2, 1);
	insertEdges(g, 1, 3, 1);
	insertEdges(g, 1, 4, 1);
	insertEdges(g, 1, 6, 2);
	insertEdges(g, 2, 3, 1);
	insertEdges(g, 3, 5, 4);
	insertEdges(g, 5, 5, 4);
	insertEdges(g, 5, 6, 3);

	// 4. 2차원배열에 mapping
	initmap(g);
}

void print(graph* g) {
	vertice* v = g->verticelistHead;
	edge* e = g->edgelistHead;

	// vertice가 모두 있는지 확인
	while (v != NULL)
	{
		printf("vid = %d vitem = %d\n", v->id, v->item);
		v = v->next;
	}
	printf("\n");

	//edge가 모두 있는지 확인
	while (e != NULL) {
		printf("v1 = %d v2 = %d weight = %d\n", e->verticeA->item, e->verticeB->item, e->weight);
		e = e->next;
	}
	printf("\n");

	//mapping이 제대로 되어있는지 확인
	e = g->edgelistHead;
	while (e != NULL) {
		if (g->map[e->verticeA->id][e->verticeB->id] != e || g->map[e->verticeB->id][e->verticeA->id] != e) {
			printf("%d %d , %d %d 문제 발견\n", e->verticeA->id, e->verticeB->id, e->verticeB->id, e->verticeA->id);
		}
		e = e->next;
	}
	printf("\n");
}

void printa(graph* g, int nodenumber) {
	if (nodenumber > 6 || nodenumber < 1) {
		printf("-1\n");
		return;
	}
		

	int i;
	for (i = 0; i < 6; i++) {
		if (g->map[i][nodenumber - 1] != NULL) {
			printf(" %d %d", i + 1, g->map[i][nodenumber - 1]->weight);
			}
	}
	printf("\n");
}

void modify(graph *g, int a, int b, int weight) {
	// a,b 중 하나라도 없는 경우
	if (a > 6 || a < 1 || b> 6 || b < 1) {
		printf("-1\n");
		return;
	}
	
	// a,b 둘다 있을 때
	vertice* va = searchvertice(g, a);
	vertice* vb = searchvertice(g, b);
	edge* e = searchedge(g, a, b);
	
	
	// a, b간선이 없으면
	if (e == NULL) {
		
		// weight 확인
		if (weight == 0) {// 간선이 없는데 삭제는 불가
			printf("-1\n");
		}
		else {// 간선 생성
			edge* newedge = getedge();
			newedge->next = NULL;
			newedge->verticeA = va;
			newedge->verticeB = vb;
			newedge->weight = weight;
			
			// 간선 리스트에 처음 간선을 넣을 경우
			if(g->edgelistHead == NULL)
				g->edgelistHead = newedge;
			// 간선 리스트에 추가 간선을 넣을 경우
			else {
				//넣을 곳 탐색
				edge* p = g->edgelistHead;
				while (p->next != NULL)
					p = p->next;
				p->next = newedge;
			}

			// 간선노드 매핑
			g->map[va->id][vb->id] = newedge;
			g->map[vb->id][va->id] = newedge;
		}
	}
	// a, b간선이 있으면
	else {
		//weight 확인
		if (weight == 0) {// 해당 간선 삭제
			// 해당 간선이 간선 리스트의 첫 간선일 때
			if (g->edgelistHead == e) {
				g->edgelistHead = e->next;
				free(e);
			}
			// 해당 간선이 간선 리스트의 첫 간선이 아닐 때
			else {
				edge* p = g->edgelistHead;
				while (p->next != e)
					p = p->next;
				
				p->next = e->next;
				free(e);
			}
			// 매핑 해제
			g->map[va->id][vb->id] = NULL;
			g->map[vb->id][va->id] = NULL;

		}
		else { // 해당간선 weight 변경
			e->weight = weight;
		}
	}
}


void putnode(graph* g) {
	edge* e = g->edgelistHead;
	edge* efront = NULL;
	while (e != NULL) {
		efront = e;
		e = e->next;
		free(efront);
	}

	vertice* v = g->verticelistHead;
	vertice* vfront = NULL;
	while (v != NULL) {
		vfront = v;
		v = v->next;
		free(vfront);
	}
}
int main() {
	//그래프 초기화
	graph g;
	init(&g);

	//print(&g);//debug용
	char command;
	int nodenumber;
	int a, b, weight;
	while (1) {
		scanf("%c", &command);
		switch (command) {
		case 'a':
			scanf("%d", &nodenumber);
			printa(&g, nodenumber);
			break;
		case 'm':
			scanf("%d %d %d", &a, &b, &weight);
			modify(&g, a, b, weight);
			break;
		case 'q':
			putnode(&g);
			exit(1);
			break;
		case 'p':
			print(&g);
			break;
		}
		getchar();
	}
}