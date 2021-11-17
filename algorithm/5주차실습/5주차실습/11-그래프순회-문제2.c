
/*
* 문제2. 인접행렬 표현
*
* 1. 그래프를 입력받고
*	1. 입력 : 정점(n), 간선(m), 순회 시작 정점 번호 (s)
* 2. BFS 구현
*	1. 조사 순서는 인접 정점의 번호가 작은 것 부터
*/

#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct vertex vertex;
typedef struct edge edge;
typedef struct graph graph;

typedef struct vertex {
	int item;
	struct vertex* next;
	int is_visited;
}vertex;
vertex* getvertex() {
	vertex* newnode = (vertex*)malloc(sizeof(vertex));
	return newnode;
}

typedef struct edge {
	vertex* vertex_a, * vertex_b;
	struct edge* next;
	int is_visited;
}edge;
edge* getedge() {
	edge* newnode = (edge*)malloc(sizeof(edge));
	return newnode;
}

typedef struct graph {
	vertex* vertex_head;
	edge* edge_head;
	edge*** map;
}graph;

typedef struct vertexP {
	vertex* vp;
	struct vertexP* next;
}vertexP;
vertexP* getvertexP() {
	vertexP* newnode = (vertexP*)malloc(sizeof(vertexP));
	return newnode;
}


// item = item 인 node를 찾아서 반환. 없으면 생성해서 정점 리스트에 추가하고 반환
vertex* search_vertex(graph* g, int item) {

	vertex* vp = g->vertex_head;
	vertex* vp_previous = NULL;

	// 1. graph 정점 개수 >= 1 일때
	if (g->vertex_head != NULL) {
		while (vp != NULL) {
			if (vp->item == item)
				return vp;
			vp_previous = vp;
			vp = vp->next;
		}
		// 못찾으면 vp = NULL값. 다음단계로.
	}

	// 2. 못찾았으니까 정점 생성
	vertex* v = getvertex();
	v->item = item; // item 초기화
	v->next = NULL; // next 주소값 초기화

	//3. graph에 위치시킨다.
	//	3-1. g->vertex_head == NULL 일경우
	if (vp_previous == NULL) // vp_previous == NULL일 경우는 그래프에 정점이 하나도 없을 때. 1번 순회 참고.
		g->vertex_head = v;
	//	3-2. g->vertex_head != NULL 일경우
	else
		vp_previous->next = v; // vp_previous != NULL일 경우는 vp_previous는 리스트의 제일 끝 노드에 가 있다.

	return v;
}

// 정점 a, 정점 b, 연결.
void make_edge(graph* g, vertex* a, vertex* b) {
	// 1. edge 만들기, 초기화
	// 2. edge를 map에 추가
	// 3. edge를 graph에 추가

	//1. edge 만들기, 초기화
	edge* new_edge = getedge();
	new_edge->vertex_a = a;
	new_edge->vertex_b = b;
	new_edge->next = NULL;

	//2. edge를 map에 추가
	int i = a->item-1;
	int j = b->item-1;
	g->map[i][j] = new_edge;
	g->map[j][i] = new_edge;

	//3. edge를 graph에 추가
	if (g->edge_head == NULL)
		g->edge_head = new_edge;
	else {
		edge* ep = g->edge_head;
		while (ep->next != NULL)
			ep = ep->next;
		ep->next = new_edge;
	}
}

void debug_print(graph* g) {
	// 정점 검사
	vertex* vp = g->vertex_head;
	printf("--정점 검사--\n");
	while (vp != NULL) {
		printf("%d\n", vp->item);
		vp = vp->next;
	}
	printf("\n");

	// 간선 검사
	edge* ep = g->edge_head;
	printf("--간선 검사--\n");
	while (ep != NULL) {
		printf("%d %d 간선존재\n", ep->vertex_a->item, ep->vertex_b->item);
		ep = ep->next;
	}
	printf("\n");
}

vertex* opp(edge* e, vertex* v) {
	vertex* ret = e->vertex_a == v ? e->vertex_b : e->vertex_a;
	return ret;
}

void BFS1(graph *g, vertex *v, int n) {
	vertexP* L = getvertexP();
	L->vp = v;
	L->next = NULL;

	vertexP* L1 = NULL;
	int i;
	v->is_visited = 1;

	while (L != NULL) {
		vertexP *Lhead = L;
		vertexP* L1head = L1;
		while (L != NULL) {
			printf("%d\n", L->vp->item);
			for (i = 0; i < n; i++) {
				edge* e = g->map[i][L->vp->item - 1];
				if (e != NULL) {
					vertex* w = opp(e, L->vp);
					if (e->is_visited == 0 && w->is_visited == 0) {
						if (L1 == NULL) {
							L1 = getvertexP();
							L1->vp = w;
							L1->next = NULL;
							L1head = L1;
						}
						else {
							L1->next = getvertexP();
							L1 = L1->next;
							L1->vp = w;
							L1->next = NULL;
						}
						e->is_visited = 1;
						w->is_visited = 1;
					}
				}
			}
			L = L->next;
		}
		vertexP* head_previous = Lhead;
		while (Lhead != NULL) {
			Lhead = Lhead->next;
			free(head_previous);
			head_previous = Lhead;
		}
		L = L1head;
		L1 = NULL;
	}
	
}

void BFS(graph* g, int s, int n) {
	//vertex is visited 초기화
	vertex* vp = g->vertex_head;
	while (vp != NULL) {
		vp->is_visited = 0;
		vp = vp->next;
	}

	//edge is visited 초기화
	edge* ep = g->edge_head;
	while (ep != NULL) {
		ep->is_visited = 0;
		ep = ep->next;
	}

	// s에 해당 map에서 시작
	vp = g->vertex_head;
	while (vp->item != s)
		vp = vp->next;

	BFS1(g,vp,n);
}

void putnode(graph* g, int n) {
	//정점, incident 해제
	vertex* v = g->vertex_head;
	vertex* v_previous = v;
	while (v != NULL) {
		v = v->next;
		free(v_previous);
		v_previous = v;
	}

	// 간선 해제
	edge* e = g->edge_head;
	edge* e_previous = e;
	while (e != NULL) {
		e = e->next;
		free(e_previous);
		e_previous = e;
	}

	// map 해제
	int i;
	for (i = 0; i < n; i++)
		free(g->map[i]);
	free(g->map);
}

int main() {
	
	graph g;
	g.edge_head = NULL;
	g.vertex_head = NULL;
	g.map = NULL;

	//n : 정점, m : 간선, s : 순회 시작 번호
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);

	// 맵초기화
	int i,j;
	g.map = (edge***)malloc(sizeof(edge**) * n);
	for (i = 0; i < n; i++) {
		g.map[i] = (edge**)malloc(sizeof(edge*) * n);
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			g.map[i][j] = NULL;
		}
	}
	
	int a, b;
	vertex* v1, * v2;
	for (i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		if (a > b) {
			int temp = a;
			a = b;
			b = temp;
		}

		v1 = search_vertex(&g, a);
		v2 = search_vertex(&g, b);
		make_edge(&g, v1, v2);
		
	}
	// 그래프 구현 완료

	//BFS 구현 시작
	BFS(&g, s, n);

	// 메모리 해제
	putnode(&g, n);
}
