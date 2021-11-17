
/*
* ����1. ��������Ʈ ǥ��
* 
* 1. �׷����� �Է¹ް�
*	1. �Է� : ����(n), ����(m), ��ȸ ���� ���� ��ȣ (s)
* 2. DFS ����
*	1. ���� ������ ���� ������ ��ȣ�� ���� �� ����
*		incident list�� ���ĵ� ���� �����ؾ� �����ҵ�...?
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





// item = item �� node�� ã�Ƽ� ��ȯ. ������ �����ؼ� ���� ����Ʈ�� �߰��ϰ� ��ȯ
vertex* search_vertex(graph *g, int item) {
	
	vertex* vp = g->vertex_head;
	vertex* vp_previous = NULL;

	// 1. graph ���� ���� >= 1 �϶�
	if (g->vertex_head != NULL) {
		while (vp != NULL) {
			if (vp->item == item)
				return vp;
			vp_previous = vp;
			vp = vp->next;
		}
		// ��ã���� vp = NULL��. �����ܰ��.
	}

	// 2. ��ã�����ϱ� ���� ����
	vertex* v = getvertex();
	v->item = item; // item �ʱ�ȭ
	v->next = NULL; // next �ּҰ� �ʱ�ȭ
	v->incident_header = getincident(); // incident list header �ʱ�ȭ
	v->incident_header->next = NULL;
	v->incident_header->edge_pointer = NULL;
	
	//3. graph�� ��ġ��Ų��.
	//	3-1. g->vertex_head == NULL �ϰ��
	if (vp_previous == NULL) // vp_previous == NULL�� ���� �׷����� ������ �ϳ��� ���� ��. 1�� ��ȸ ����.
		g->vertex_head = v;
	//	3-2. g->vertex_head != NULL �ϰ��
	else
		vp_previous->next = v; // vp_previous != NULL�� ���� vp_previous�� ����Ʈ�� ���� �� ��忡 �� �ִ�.

	return v;
}

// ���� a, ���� b, ����.
void make_edge(graph *g, vertex *a, vertex *b) {
	// 1. edge �����, �ʱ�ȭ
	// 2. a - incident , b - incident �߰�
	// 3. edge�� graph�� �߰�

	//1. edge �����, �ʱ�ȭ
	edge* new_edge = getedge();
	new_edge->vertex_a = a;
	new_edge->vertex_b = b;
	new_edge->next = NULL;

	//2. a - incident, b - incident �߰�
	// a�� incident �߰�
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

	// b�� incident �߰�
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
	
	//3. edge�� graph�� �߰�
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
	// ���� �˻�
	vertex* vp = g->vertex_head;
	printf("--���� �˻�--\n");
	while (vp != NULL) {
		printf("%d\n", vp->item);
		vp = vp->next;
	}
	printf("\n");

	// ���� �˻�
	edge* ep = g->edge_head;
	printf("--���� �˻�--\n");
	while (ep != NULL) {
		printf("%d %d ��������\n",ep->vertex_a->item, ep->vertex_b->item);
		ep = ep->next;
	}
	printf("\n");

	// incident �˻�
	vp = g->vertex_head;
	printf("--incident list �˻�--\n");
	while (vp != NULL) {
		printf("%d ������\n", vp->item);
		incident* ip = vp->incident_header->next;
		while (ip != NULL) {
			printf(" %d %d ����\n", ip->edge_pointer->vertex_a->item, ip->edge_pointer->vertex_b->item);
			ip = ip->next;
		}
		printf("�� �ֽ��ϴ�\n\n");
		vp = vp->next;
	}
	printf("\n");
}

vertex* opp(edge * e, vertex * v) {
	vertex* ret = e->vertex_a == v ? e->vertex_b : e->vertex_a;
	return ret;
}

void rDFS(vertex *v) {
	// 1. ���� �湮ó��
	v->is_visited = 1;
	printf("%d\n", v->item);
	// 2. incident list ��ȸ
	incident* ip = v->incident_header;
	while (ip != NULL) {
		if (ip->edge_pointer != NULL && ip->edge_pointer->is_visited == 0) { // �����尡 �ƴϰ�, ������ �湮���� ������
			vertex* op = opp(ip->edge_pointer, v);
			if (op->is_visited == 0) {
				//���� �湮ó��
				ip->edge_pointer->is_visited = 1;
				rDFS(op);
			}
		}
		ip = ip->next;
	}
}

void DFS(graph* g, int s) {
	//vertex is visited �ʱ�ȭ
	vertex* vp = g->vertex_head;
	while (vp != NULL) {
		vp->is_visited = 0;
		vp = vp->next;
	}

	//edge is visited �ʱ�ȭ
	edge* ep = g->edge_head;
	while (ep != NULL) {
		ep->is_visited = 0;
		ep = ep->next;
	}

	// s�� �ش� vertex ã��
	vp = g->vertex_head;
	while (vp->item != s)
		vp = vp->next;

	rDFS(vp);
}

void putnode(graph *g) {
	//����, incident ����
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

	// ���� ����
	edge* e = g->edge_head;
	edge* e_previous = e;
	while (e != NULL) {
		e = e->next;
		free(e_previous);
		e_previous = e;
	}
}

int main() {
	//n : ����, m : ����, s : ��ȸ ���� ��ȣ
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
	// �׷��� ���� �Ϸ�

	//DFS ���� ����
	DFS(&g, s);

	// �޸� ����
	putnode(&g);
}
