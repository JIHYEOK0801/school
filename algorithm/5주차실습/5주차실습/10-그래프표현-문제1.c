#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* ���� ������ �Һ�, ���� ������ ����
* ������ �̸��� ����.
* 
* ������ ������ �ٲ�� �־ 1���� ���Ḯ��Ʈ - ��������Ʈ�� ����
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
	// ��������Ʈ�� ���������
	struct vertexPointer* vP;
	// ��������Ʈ�� ���������
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

	// �׷����� vertex�� �ϳ��� ���� ó���� ���
	if (map->vP == NULL) {
		//����������, ���� ����
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

		
		//����������, ���� ����
		eP = getedgePointer();

		e = getedge();
		e->vertexA = v_a;
		e->vertexB = v_b;
		e->weight = weight;
		eP->e = e;

		// V_Epointer ����
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
		
		// �׷��� - ������������� ����
		map->vP = vP_a;
		vP_a->next = NULL;
		if (item_a != item_b) {
			vP_a->next = vP_b;
			vP_b->next = NULL;
		}

		// �׷��� - ������������� ����
		map->eP = eP;
		eP->next = NULL;
	}



	// �׷����� vertex�� �����ϰ� ���� ��
	else {
		vertexPointer* vP_a_front = NULL;
		vertexPointer* vP_b_front = NULL;

		vP_a = map->vP;
		vP_b = map->vP;

		while (vP_a!= NULL && vP_a->v->item != item_a) {
			vP_a_front = vP_a;
			vP_a = vP_a->next;
		}
		// item_a�� �´� vertex�� ���ٴ� ��
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
		// item_b�� �´� vertex�� ���ٴ� ��
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

		// edge �߰�
		// insert�Լ����� edge�� �׻� �߰��ϴ� ���ۿ� ����
		// ���� vP_a, vP_b�� item_a, item_b�� �´� vertex�� ���� ���ִ� ��Ȳ
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

		// vertexA, vertexB�� ���� edge���� ���� �Ϸ�.
		// V_Epointer�� �����ϸ� ��
		V_EPA = getV_EPointer();
		V_EPA->e = e;
		V_EPA->next = NULL;
		
		// �ش������� ù��° ������ ������ ���
		if (v_a->head == NULL)
		{
			v_a->head = V_EPA;
		}
		// �ش������� �ι�° �̻� ������ ������ ���
		else {
			V_EPointer* temp = v_a->head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = V_EPA;
		}
		
		// �����ο��� ���� ������ �ƴ� ��쿡�� V_EPB�� �Ȱ��� ����
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

//����׿�
void print(graph* map) {
	vertexPointer* vp = map->vP;
	printf("���� vertexPointer����Ʈ->vertex->item :::");
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
		printf("%d�� ������\n", v->item);
		while (V_EP != NULL) {
			edge* e = V_EP->e;
			int notme;
			if (e->vertexA->item == v->item)
				notme = e->vertexB->item;
			else
				notme = e->vertexA->item;
			printf("����: %d�� weight: %d �� ����� �����Դϴ�.\n", notme, e->weight);
			V_EP = V_EP->next;
		}
		vp = vp->next;
		printf("\n");
	}
	printf("\n");

	
	printf("���� edgePointer����Ʈ->edge->weight :::");
	edgePointer* ep = map->eP;
	while (ep != NULL) {
		printf("%d ", ep->e->weight);
		ep = ep->next;
	}
		
	printf("\n");
	printf("\n");
	printf("print �Ϸ�\n");
}

void init(graph *map) {
	// �׷��� �ʱ�ȭ
	map->vP = NULL;
	map->eP = NULL;
	// �׷��� �� �ʱ�ȭ
	insert(map, 1, 2, 1);
	insert(map, 1, 3, 1);
	insert(map, 1, 4, 1);
	insert(map, 1, 6, 2);
	insert(map, 2, 3, 1);
	insert(map, 3, 5, 4);
	insert(map, 5, 5, 4);
	insert(map, 5, 6, 3);
	//debug�� print
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
	* 1. �ϳ��� ������ ���� ���
	* 
	* 2. ������ ��� ���� ���
	*		�ش� ������ �ִ��� üũ
	* 
	*		2-1. ������ ����
	*				weight Ȯ��
	*					2-1-1. ���� ����
	*
	*		2-2. ������ �ִ�
	*				weight Ȯ��
	*					2-2-1. ���� ����
	*					2-2-2. ���� ����
	*		
	*/

	vertexPointer* vpA = map->vP;
	vertexPointer* vpB = map->vP;

	while (vpA != NULL && vpA->v->item != a)
		vpA = vpA->next;

	while (vpB != NULL && vpB->v->item != b)
		vpB = vpB->next;

	// 1. �ϳ��� ������ ���� ���
	if (vpA == NULL || vpB == NULL) {
		printf("%d\n", -1);
		return;
	}
		
	// 2. ������ ��� ���� ���
	edgePointer* ep = map->eP;
	edgePointer* ep_front = NULL;
	vertex* va = vpA->v;
	vertex* vb = vpB->v;
	edge* ed = NULL;

	//�ش� ������ �ִ��� üũ
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
	
	
	// 2-1. ������ ����
	if (ep == NULL) {
		// weight Ȯ��(w==0)
		if (w == 0) {
			printf("%d\n", -1);
			return;
		}
		// weight Ȯ��(w!=0)
		// 2-1-1. ���� ����
		ep = getedgePointer();
		ep->next = NULL;

		//�׷����� ������ �ϳ��� ���� �� ex) ������ �ִ� ���
		if (map->eP == NULL)
			map->eP = ep;
		//�׷����� ������ �Ѱ� �̻� ���� ��
		else
			ep_front->next = ep;
		
		// edge ����	
		edge* e = getedge();
		ep->e = e;
		e->vertexA = va;
		e->vertexB = vb;
		e->weight = w;
	
		// V_EPointer�� va�� �߰�
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

		// va, vb�� ���� �ٸ� ���� ����ų��
		// V_EPointer�� vb�� �߰�
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

	// 2-2. ������ �ִ�

	else {
		// weight Ȯ��
		// 2-2-1. ���� ����
		if (w != 0)
		{
			ep->e->weight = w;
		}

		// 2-2-2. ���� ����
		else {
			//�ش� ������ �׷����� ù �����϶�
			if (ep == map->eP) map->eP = ep->next;
			//�ش� ������ ó���� �ƴҶ�
			else {
				ep_front->next = ep->next;
			}
			
			//va���� edge���� ����
			V_EPointer* tempa = va->head;
			V_EPointer* tempfront = NULL;
			
			while (tempa->e != ed) {
				tempfront = tempa;
				tempa = tempa->next;
			}

			// �ش� ������ ������ ù ������ ��
			if (tempa == va->head)
				va->head = tempa->next;
			// �ش� ������ ó���� �ƴ� ��
			else
				tempfront->next = tempa->next;
			
			
			// va!= vb�� ���. vb���� edge���� ����
			if (va != vb) {
				V_EPointer* tempb = vb->head;
				tempfront = NULL;
				while (tempb->e != ed) {
					tempfront = tempb;
					tempb = tempb->next;
				}
				// �ش� ������ ������ ù ������ ��
				if (tempb == vb->head)
					vb->head = tempb->next;
				// �ش� ������ ó���� �ƴ� ��
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

//�޸� ����
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
	* ������
	* - �ڱ� �ڽſ��� ���� ���� ó�� ����
	*/
}