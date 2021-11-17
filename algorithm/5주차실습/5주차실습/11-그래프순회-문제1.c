
/*
* 문제1. 인접리스트 표현
* 
* 1. 그래프를 입력받고
*	1. 입력 : 정점(n), 간선(m), 순회 시작 정점 번호 (s)
* 2. DFS 구현
*	1. 조사 순서는 인접 정점의 번호가 작은 것 부터
*		incident list를 정렬된 순서 설계해야 가능할듯...?
*/

#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct vertex vertex;
typedef struct edge edge;
typedef struct incident incident;
typedef struct graph graph;

typedef struct vertex {
	int item;
	struct vertex* next;
	struct incident* incident_header;
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

typedef struct incident {
	edge* edge_pointer;
	struct incident* next;
}incident;
incident* getincident() {
	incident* newnode = (incident*)malloc(sizeof(incident));
	return newnode;
}

typedef struct graph {
	vertex* vertex_head;
	edge* edge_head;
}graph;





// item = item 인 node를 찾아서 반환. 없으면 생성해서 정점 리스트에 추가하고 반환
vertex* search_vertex(graph *g, int item) {
	
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
	v->incident_header = getincident(); // incident list header 초기화
	v->incident_header->next = NULL;
	v->incident_header->edge_pointer = NULL;
	
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
void make_edge(graph *g, vertex *a, vertex *b) {
	// 1. edge 만들기, 초기화
	// 2. a - incident , b - incident 추가
	// 3. edge를 graph에 추가

	//1. edge 만들기, 초기화
	edge* new_edge = getedge();
	new_edge->vertex_a = a;
	new_edge->vertex_b = b;
	new_edge->next = NULL;

	//2. a - incident, b - incident 추가
	// a에 incident 추가
	incident* new_inci = getincident();
	new_inci->edge_pointer = new_edge;
	new_inci->next = NULL;

	incident* ip = a->incident_header;
	incident* ip_previous = NULL;
	while (ip != NULL) {
		if (ip->edge_pointer != NULL) {
			int edge_a = ip->edge_pointer->vertex_a->item;
			int edge_b = ip->edge_pointer->vertex_b->item;
			int anothernumber = a->item == edge_a ? edge_b : edge_a;
			if (anothernumber > b->item)
				break;
		}
		ip_previous = ip;
		ip = ip->next;
	}
	if (ip == NULL)
		ip_previous->next = new_inci;
	else {
		ip_previous->next = new_inci;
		new_inci->next = ip;
	}

	// b에 incident 추가
	new_inci = getincident();
	new_inci->edge_pointer = new_edge;
	new_inci->next = NULL;

	ip = b->incident_header;
	ip_previous = NULL;
	while (ip != NULL) {
		if (ip->edge_pointer != NULL) {
			int edge_a = ip->edge_pointer->vertex_a->item;
			int edge_b = ip->edge_pointer->vertex_b->item;
			int anothernumber = b->item == edge_a ? edge_b : edge_a;
			if (anothernumber > a->item)
				break;
		}
		ip_previous = ip;
		ip = ip->next;
	}
	
	if (ip == NULL)
		ip_previous->next = new_inci;
	else {
		ip_previous->next = new_inci;
		new_inci->next = ip;
	}
	
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
		printf("%d %d 간선존재\n",ep->vertex_a->item, ep->vertex_b->item);
		ep = ep->next;
	}
	printf("\n");

	// incident 검사
	vp = g->vertex_head;
	printf("--incident list 검사--\n");
	while (vp != NULL) {
		printf("%d 정점은\n", vp->item);
		incident* ip = vp->incident_header->next;
		while (ip != NULL) {
			printf(" %d %d 간선\n", ip->edge_pointer->vertex_a->item, ip->edge_pointer->vertex_b->item);
			ip = ip->next;
		}
		printf("이 있습니다\n\n");
		vp = vp->next;
	}
	printf("\n");
}

vertex* opp(edge * e, vertex * v) {
	vertex* ret = e->vertex_a == v ? e->vertex_b : e->vertex_a;
	return ret;
}

void rDFS(vertex *v) {
	// 1. 정점 방문처리
	v->is_visited = 1;
	printf("%d\n", v->item);
	// 2. incident list 순회
	incident* ip = v->incident_header;
	while (ip != NULL) {
		if (ip->edge_pointer != NULL && ip->edge_pointer->is_visited == 0) { // 헤더노드가 아니고, 간선도 방문한적 없을때
			vertex* op = opp(ip->edge_pointer, v);
			if (op->is_visited == 0) {
				//간선 방문처리
				ip->edge_pointer->is_visited = 1;
				rDFS(op);
			}
		}
		ip = ip->next;
	}
}

void DFS(graph* g, int s) {
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

	// s에 해당 vertex 찾기
	vp = g->vertex_head;
	while (vp->item != s)
		vp = vp->next;

	rDFS(vp);
}

void putnode(graph *g) {
	//정점, incident 해제
	vertex* v = g->vertex_head;
	vertex* v_previous = v;
	while (v != NULL) {
		incident* i = v->incident_header;
		incident* i_previous = i;
		while (i != NULL) {
			i = i->next;
			free(i_previous);
			i_previous = i;
		}
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
}

int main() {
	//n : 정점, m : 간선, s : 순회 시작 번호
	graph g;
	g.edge_head = NULL;
	g.vertex_head = NULL;

	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);
	
	int i;
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
		//debug_print(&g);
	}
	// 그래프 구현 완료

	//DFS 구현 시작
	DFS(&g, s);

	// 메모리 해제
	putnode(&g);
}
