
/*
* ����2. ������� ǥ��
*
* 1. �׷����� �Է¹ް�
*	1. �Է� : ����(n), ����(m), ��ȸ ���� ���� ��ȣ (s)
* 2. BFS ����
*	1. ���� ������ ���� ������ ��ȣ�� ���� �� ����
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


// item = item �� node�� ã�Ƽ� ��ȯ. ������ �����ؼ� ���� ����Ʈ�� �߰��ϰ� ��ȯ
vertex* search_vertex(graph* g, int item) {

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
void make_edge(graph* g, vertex* a, vertex* b) {
	// 1. edge �����, �ʱ�ȭ
	// 2. edge�� map�� �߰�
	// 3. edge�� graph�� �߰�

	//1. edge �����, �ʱ�ȭ
	edge* new_edge = getedge();
	new_edge->vertex_a = a;
	new_edge->vertex_b = b;
	new_edge->next = NULL;

	//2. edge�� map�� �߰�
	int i = a->item-1;
	int j = b->item-1;
	g->map[i][j] = new_edge;
	g->map[j][i] = new_edge;

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
		printf("%d %d ��������\n", ep->vertex_a->item, ep->vertex_b->item);
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

	// s�� �ش� map���� ����
	vp = g->vertex_head;
	while (vp->item != s)
		vp = vp->next;

	BFS1(g,vp,n);
}

void putnode(graph* g, int n) {
	//����, incident ����
	vertex* v = g->vertex_head;
	vertex* v_previous = v;
	while (v != NULL) {
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

	// map ����
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

	//n : ����, m : ����, s : ��ȸ ���� ��ȣ
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);

	// ���ʱ�ȭ
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
	// �׷��� ���� �Ϸ�

	//BFS ���� ����
	BFS(&g, s, n);

	// �޸� ����
	putnode(&g, n);
}
