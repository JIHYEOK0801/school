#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// node ����ü
typedef struct node {
	int key, height;
	struct node* parent, * lchild, * rchild;
}node;

// root ���ټ����̸� ���� �������� ����
node* root = NULL;

// node ���� �� �ٷ� return. �ʱ�ȭ�ϴ� ������ ����.
node* getNode() {
	node* p = (node*)malloc(sizeof(node));
	return p;
}

// w->key�� k�� setting
void setNode(node* w, int k) {
	w->key = k;
}

// Ʈ�� �ʱ�ȭ �Լ�. �ܺγ�� �Ѱ��� �����Ѵ�.
void init() {
	if (root == NULL) {
		root = getNode();

		root->lchild = NULL;
		root->rchild = NULL;
		root->parent = NULL;
		root->height = 0;
	}
}

// node w�� root���� Ȯ��
int isRoot(node* w) {
	if (w->parent == NULL)
		return 1;
	else
		return 0;
}

// node w�� �ܺγ������ Ȯ��
int isExternal(node* w) {
	if (w->lchild == NULL && w->rchild == NULL)
		return 1;
	else
		return 0;
}

// node w�� ���γ������ Ȯ��
int isInternal(node* w) {
	if (w->lchild != NULL || w->rchild != NULL)
		return 1;
	else
		return 0;
}

// print �Լ�
void print(node* w) {
	if (isExternal(w))
		return;
	//printf("key = %d    height = %d\n", w->key, w->height);
	printf(" %d", w->key);
	print(w->lchild);
	print(w->rchild);
}

// ���� ��带 �˻��ϴ� �Լ� && ���������� �ڵ������� root ��尡 ���� ���� ����.
node* sibling(node* w) {
	if (isRoot(w)) {
		printf("invalidNodeException\n");
		exit(0);
	}
	if (w->parent->lchild == w)
		return w->parent->rchild;
	else
		return w->parent->lchild;
}

// node z�� ���� �ܺγ�� ����.
void expandExternal(node* z) {
	node* l = getNode();
	node* r = getNode();

	l->lchild = NULL;
	l->rchild = NULL;
	l->height = 0;
	l->parent = z;

	r->lchild = NULL;
	r->rchild = NULL;
	r->height = 0;
	r->parent = z;

	z->lchild = l;
	z->rchild = r;
	z->height = 1;
}

// �ܺγ���� z�� ���ִ� �Լ�.
node* reduceExternal(node* z) {
	node* w = z->parent;
	node* zs = sibling(z);
	node* g;
	if (isRoot(w)) {
		root = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		if (w == g->lchild)
			g->lchild = zs;
		else
			g->rchild = zs;
	}

	free(z);
	free(w);
	return zs;
}

// key == k �� node�� Ž���ϴ� �Լ� && key�� �־���� ��带 Ž���ϴ� �Լ�
node* treeSearch(node* v, int k) {
	if (isExternal(v))
		return v;

	if (k == v->key)
		return v;
	else if (k < v->key)
		return treeSearch(v->lchild, k);
	else if (k > v->key)
		return treeSearch(v->rchild, k);
}




int updateHeight(node* root) {
	if ((isExternal(root))) return root->height;

	int lheight = updateHeight(root->lchild);
	int rheight = updateHeight(root->rchild);
	if (lheight > rheight)
		root->height = lheight + 1;
	else
		root->height = rheight + 1;
	return root->height;
}

// ��� w�� ���̱��� ���� ��ȯ
int isBalanced(node* w) {
	if (isExternal(w)) {
		printf("(isBalanced())Invalid Node Exception!!\n");
		exit(0);
	}
	int dif = w->lchild->height - w->rchild->height;
	return (-1 <= dif) && (dif <= 1);
}

//���̰� ū �ڽ� ��ȯ
node* higherChild(node* w) {
	if (w->lchild->height > w->rchild->height)
		return w->lchild;
	else if (w->lchild->height < w->rchild->height)
		return w->rchild;
	else {
		if (w == w->parent->lchild) return w->lchild;
		else return w->rchild;
	}
}

//�θ� �ڽ� ��� ����
void updateParentChild(node* p, node* c1, node* c2) {
	p->lchild = c1;
	p->rchild = c2;
	c1->parent = p;
	c2->parent = p;
}

node* restructure(node* x, node* y, node* z) {
	//���� ��ȸ ���� a,b,c ã��
	node* a, * b, * c;
	node* t0, * t1, * t2, * t3;

	//4���� ������ȸ ����Ǽ�
	// x<y<z
	if (x->key < y->key && y->key < z->key)
	{
		a = x; b = y; c = z;
		t0 = a->lchild; t1 = a->rchild; t2 = b->rchild; t3 = c->rchild;
	}
	// z<y<x
	else if (z->key < y->key && y->key < x->key) {
		a = z; b = y; c = x;
		t0 = a->lchild; t1 = b->lchild; t2 = c->lchild; t3 = c->rchild;
	}
	// y<x<z
	else if (y->key < x->key && x->key < z->key) {
		a = y; b = x; c = z;
		t0 = a->lchild; t1 = b->lchild; t2 = b->rchild; t3 = c->rchild;
	}
	// z<x<y
	else if (z->key < x->key && x->key < y->key) {
		a = z; b = x; c = y;
		t0 = a->lchild; t1 = b->lchild; t2 = b->rchild; t3 = c->rchild;
	}
	else {
		printf("������ȸ ����Ǽ� ����\n");
		exit(0);
	}

	//3. z�� b�� ��ü
	b->parent = z->parent;
	if (!isRoot(z)) {
		if (z->parent->lchild == z) z->parent->lchild = b;
		else z->parent->rchild = b;
	}
	else {
		root = b;
	}

	//4. t0, t1�� a�� ���� ������. t2, t3�� c�� ���� ������. a, c�� b�� ���� ������
	updateParentChild(a, t0, t1);
	updateParentChild(c, t2, t3);
	updateParentChild(b, a, c);

	//5. return b
	return b;
}

//�����˻� ����, �ұ����� ������ ���� ���̱��� �Ӽ� ȸ��
void searchAndFixAfterInsertion(node* w) {
	//��Ʈ���� ���µ� �ұ��� ��尡 ��� root->parent�� NULL�� ��ȯ �Ǿ��� ��
	if (w == NULL) return;

	node* z, * y, * x;
	//w�� ���� ����� ��
	if (isBalanced(w)) searchAndFixAfterInsertion(w->parent);

	//w�� �ұ��� ����� ��
	else {
		z = w;
		y = higherChild(z);
		x = higherChild(y); // x != w �ϼ� ����
		restructure(x, y, z);
		updateHeight(root);
		return;
	}
}

// key = k �� node ����
void insertItem(int k) {
	node* w = treeSearch(root, k);
	if (isInternal(w))
		return;
	else {
		setNode(w, k);
		expandExternal(w);
		updateHeight(root);
		searchAndFixAfterInsertion(w);
		//print(root); //node�� �����Ҷ����� print ����.
	}
}

// key == k�� ��� �˻� �� key return
int findElement(int k) {
	node* w = treeSearch(root, k);
	if (isExternal(w))
		return -1;
	else
		return w->key;
}

// node w�� �������� �İ��ڸ� ã�� �Լ�
node* inOrderSucc(node* w) {
	w = w->rchild;
	if (isExternal(w)) {
		printf("invalidNodeException\n");
		exit(0);
	}
	while (isInternal(w->lchild))
		w = w->lchild;

	return w;
}

void searchAndFixAfterRemoval(node* w) {
	//��Ʈ���� ���µ� �ұ��� ��尡 ��� root->parent�� NULL�� ��ȯ �Ǿ��� ��
	if (w == NULL) return;

	node* z, * y, * x, *b;
	//w�� ���� ����� ��
	if (isBalanced(w)) searchAndFixAfterRemoval(w->parent);

	//w�� �ұ��� ����� ��
	else {
		z = w;
		y = higherChild(z);
		x = higherChild(y); // x != w �ϼ� ����
		b = restructure(x, y, z);
		updateHeight(root);
		searchAndFixAfterRemoval(b);
	}
}


// key == k�� node�� �����ϴ� �Լ�.
int removeElement(int k) {
	node* w = treeSearch(root, k);

	// key == k �� ��尡 ���� ��
	if (isExternal(w)) return -1;

	// key == k �� ��尡 ���� ��
	int e = w->key;
	node* z = w->lchild;
	if (!isExternal(z))
		z = w->rchild;

	node* y, * zs;
	if (isExternal(z)){
		zs = reduceExternal(z);
	}
		
	else {
		y = inOrderSucc(w);
		z = y->lchild;
		setNode(w, y->key);
		zs = reduceExternal(z);
	}
	updateHeight(root);
	searchAndFixAfterRemoval(zs->parent);
	//print(root);
	//printf("\n");
	return e;
}



int main() {
	char command;
	int key;
	int searchKey;
	int deleteKey;

	// Ʈ�� ��Ʈ �ʱ�ȭ
	init();

	while (1) {
		scanf("%c", &command);
		switch (command) {

			// ����
		case 'i':
			scanf("%d", &key);
			insertItem(key);
			break;

			//����
		case 'd':
			scanf("%d", &key);
			deleteKey = removeElement(key);
			if (deleteKey == -1) printf("%c\n", 'X');
			else printf("%d\n", deleteKey);
			break;

			//Ž��
		case 's':
			scanf("%d", &key);
			searchKey = findElement(key);
			if (searchKey == -1) printf("%c\n", 'X');
			else printf("%d\n", searchKey);
			break;

			//���
		case 'p':
			print(root);
			printf("\n");
			break;

			//����
		case 'q':
			exit(0);
			break;
		}
		getchar();
	}
}