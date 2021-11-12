#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// node ����ü
typedef struct node {
	int key;
	struct node* parent, * lchild, * rchild;
}node;

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
node* init() {
	node* newnode = getNode();
	newnode->lchild = NULL;
	newnode->rchild = NULL;
	newnode->parent = NULL;
	return newnode;
}

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

// node z�� ���� �ܺγ�� ����.
void expandExternal(node* z) {
	node* l = getNode();
	node* r = getNode();

	l->lchild = NULL;
	l->rchild = NULL;
	l->parent = z;

	r->lchild = NULL;
	r->rchild = NULL;
	r->parent = z;

	z->lchild = l;
	z->rchild = r;
}

// �ܺγ���� z�� ���ִ� �Լ�.
node* reduceExternal(node **root, node* z) {
	node* w = z->parent;
	node* zs = sibling(z);
	node* g;
	if (isRoot(w)) {
		*root = zs;
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
node* treeSearch(node *v, int k) {
	if (isExternal(v))
		return v;

	if (k == v->key)
		return v;
	else if (k < v->key)
		return treeSearch(v->lchild, k);
	else if (k > v->key)
		return treeSearch(v->rchild, k);
}

// ���� ��带 �˻��ϴ� �Լ� && ���������� �ڵ������� root ��尡 ���� ���� ����.


// key = k �� node ����
void insertItem(node *root, int k) {
	node* w = treeSearch(root, k);
	if (isInternal(w))
		return;
	else {
		setNode(w, k);
		expandExternal(w);
	}
}

// key == k�� ��� �˻� �� key return
int findElement(node* root, int k) {
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

// key == k�� node�� �����ϴ� �Լ�.
int removeElement(node** root, int k) {
	node* w = treeSearch(*root, k);

	// key == k �� ��尡 ���� ��
	if (isExternal(w)) return -1;

	// key == k �� ��尡 ���� ��
	int e = w->key;
	node* z = w->lchild;
	if (!isExternal(z))
		z = w->rchild;
	node* y;

	if (isExternal(z))
		reduceExternal(root, z);
	else {
		y = inOrderSucc(w);
		z = y->lchild;
		setNode(w, y->key);
		reduceExternal(root, z);
	}
	return e;
}

// print �Լ�
void print(node* w) {
	if (isExternal(w))
		return;

	printf(" %d", w->key);
	print(w->lchild);
	print(w->rchild);
}

// ������ȸ ����
void putnode(node* root) {
	if (root == NULL) return;
	putnode(root->lchild);
	putnode(root->rchild);
	free(root);
}

int main() {
	char command;
	int key;
	int searchKey;
	int deleteKey;
	
	// Ʈ�� ��Ʈ �ʱ�ȭ
	node* root = NULL;
	root = init();
	
	while (1) {
		scanf("%c", &command);
		switch (command) {
		
		// ����
		case 'i':
			scanf("%d", &key);
			insertItem(root, key);
			break;

		//����
		case 'd':
			scanf("%d", &key);
			deleteKey = removeElement(&root, key);
			if (deleteKey == -1) printf("%c\n", 'X');
			else printf("%d\n", deleteKey);
			break;

		//Ž��
		case 's':
			scanf("%d", &key);
			searchKey = findElement(root, key);
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
			putnode(root);
			exit(0);
			break;
		}
		getchar();
	}


}