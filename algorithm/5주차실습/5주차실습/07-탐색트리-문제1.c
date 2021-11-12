#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// node 구조체
typedef struct node {
	int key;
	struct node* parent, * lchild, * rchild;
}node;

// node 생성 후 바로 return. 초기화하는 변수는 없음.
node* getNode() {
	node* p = (node*)malloc(sizeof(node));
	return p;
}

// w->key를 k로 setting
void setNode(node* w, int k) {
	w->key = k;
}

// 트리 초기화 함수. 외부노드 한개만 존재한다.
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

// node w가 root인지 확인
int isRoot(node* w) {
	if (w->parent == NULL)
		return 1;
	else
		return 0;
}

// node w가 외부노드인지 확인
int isExternal(node* w) {
	if (w->lchild == NULL && w->rchild == NULL)
		return 1;
	else
		return 0;
}

// node w가 내부노드인지 확인
int isInternal(node* w) {
	if (w->lchild != NULL || w->rchild != NULL)
		return 1;
	else
		return 0;
}

// node z의 양쪽 외부노드 생성.
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

// 외부노드인 z를 없애는 함수.
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

// key == k 인 node를 탐색하는 함수 && key를 넣어야할 노드를 탐색하는 함수
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

// 형제 노드를 검색하는 함수 && 정상적으로 코딩했으면 root 노드가 들어올 일이 없음.


// key = k 인 node 삽입
void insertItem(node *root, int k) {
	node* w = treeSearch(root, k);
	if (isInternal(w))
		return;
	else {
		setNode(w, k);
		expandExternal(w);
	}
}

// key == k인 노드 검색 후 key return
int findElement(node* root, int k) {
	node* w = treeSearch(root, k);
	if (isExternal(w))
		return -1;
	else
		return w->key;
}

// node w의 중위순위 후계자를 찾는 함수
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

// key == k인 node를 삭제하는 함수.
int removeElement(node** root, int k) {
	node* w = treeSearch(*root, k);

	// key == k 인 노드가 없을 때
	if (isExternal(w)) return -1;

	// key == k 인 노드가 있을 때
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

// print 함수
void print(node* w) {
	if (isExternal(w))
		return;

	printf(" %d", w->key);
	print(w->lchild);
	print(w->rchild);
}

// 후위순회 해제
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
	
	// 트리 루트 초기화
	node* root = NULL;
	root = init();
	
	while (1) {
		scanf("%c", &command);
		switch (command) {
		
		// 삽입
		case 'i':
			scanf("%d", &key);
			insertItem(root, key);
			break;

		//삭제
		case 'd':
			scanf("%d", &key);
			deleteKey = removeElement(&root, key);
			if (deleteKey == -1) printf("%c\n", 'X');
			else printf("%d\n", deleteKey);
			break;

		//탐색
		case 's':
			scanf("%d", &key);
			searchKey = findElement(root, key);
			if (searchKey == -1) printf("%c\n", 'X');
			else printf("%d\n", searchKey);
			break;

		//출력
		case 'p':
			print(root);
			printf("\n");
			break;

		//종료
		case 'q':
			putnode(root);
			exit(0);
			break;
		}
		getchar();
	}


}