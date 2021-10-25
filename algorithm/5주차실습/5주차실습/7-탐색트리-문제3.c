#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// node 구조체
typedef struct node {
	int key, height;
	struct node* parent, * lchild, * rchild;
}node;

// root 접근성용이를 위해 전역변수 설정
node* root = NULL;

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
void init() {
	if (root == NULL) {
		root = getNode();

		root->lchild = NULL;
		root->rchild = NULL;
		root->parent = NULL;
		root->height = 0;
	}
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

// print 함수
void print(node* w) {
	if (isExternal(w))
		return;
	//printf("key = %d    height = %d\n", w->key, w->height);
	printf(" %d", w->key);
	print(w->lchild);
	print(w->rchild);
}

// 형제 노드를 검색하는 함수 && 정상적으로 코딩했으면 root 노드가 들어올 일이 없음.
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

// node z의 양쪽 외부노드 생성.
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

// 외부노드인 z를 없애는 함수.
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

// key == k 인 node를 탐색하는 함수 && key를 넣어야할 노드를 탐색하는 함수
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

// 노드 w의 높이균형 여부 반환
int isBalanced(node* w) {
	if (isExternal(w)) {
		printf("(isBalanced())Invalid Node Exception!!\n");
		exit(0);
	}
	int dif = w->lchild->height - w->rchild->height;
	return (-1 <= dif) && (dif <= 1);
}

//높이가 큰 자식 반환
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

//부모 자식 노드 갱신
void updateParentChild(node* p, node* c1, node* c2) {
	p->lchild = c1;
	p->rchild = c2;
	c1->parent = p;
	c2->parent = p;
}

node* restructure(node* x, node* y, node* z) {
	//중위 순회 순서 a,b,c 찾기
	node* a, * b, * c;
	node* t0, * t1, * t2, * t3;

	//4가지 중위순회 경우의수
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
		printf("중위순회 경우의수 오류\n");
		exit(0);
	}

	//3. z를 b로 교체
	b->parent = z->parent;
	if (!isRoot(z)) {
		if (z->parent->lchild == z) z->parent->lchild = b;
		else z->parent->rchild = b;
	}
	else {
		root = b;
	}

	//4. t0, t1을 a의 왼쪽 오른쪽. t2, t3을 c의 왼쪽 오른쪽. a, c를 b의 왼쪽 오른쪽
	updateParentChild(a, t0, t1);
	updateParentChild(c, t2, t3);
	updateParentChild(b, a, c);

	//5. return b
	return b;
}

//균형검사 수행, 불균형시 개조를 통해 높이균형 속성 회복
void searchAndFixAfterInsertion(node* w) {
	//루트까지 갔는데 불균형 노드가 없어서 root->parent인 NULL이 반환 되었을 때
	if (w == NULL) return;

	node* z, * y, * x;
	//w가 균형 노드일 때
	if (isBalanced(w)) searchAndFixAfterInsertion(w->parent);

	//w가 불균형 노드일 때
	else {
		z = w;
		y = higherChild(z);
		x = higherChild(y); // x != w 일수 있음
		restructure(x, y, z);
		updateHeight(root);
		return;
	}
}

// key = k 인 node 삽입
void insertItem(int k) {
	node* w = treeSearch(root, k);
	if (isInternal(w))
		return;
	else {
		setNode(w, k);
		expandExternal(w);
		updateHeight(root);
		searchAndFixAfterInsertion(w);
		//print(root); //node를 삽입할때마다 print 가능.
	}
}

// key == k인 노드 검색 후 key return
int findElement(int k) {
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

void searchAndFixAfterRemoval(node* w) {
	//루트까지 갔는데 불균형 노드가 없어서 root->parent인 NULL이 반환 되었을 때
	if (w == NULL) return;

	node* z, * y, * x, *b;
	//w가 균형 노드일 때
	if (isBalanced(w)) searchAndFixAfterRemoval(w->parent);

	//w가 불균형 노드일 때
	else {
		z = w;
		y = higherChild(z);
		x = higherChild(y); // x != w 일수 있음
		b = restructure(x, y, z);
		updateHeight(root);
		searchAndFixAfterRemoval(b);
	}
}


// key == k인 node를 삭제하는 함수.
int removeElement(int k) {
	node* w = treeSearch(root, k);

	// key == k 인 노드가 없을 때
	if (isExternal(w)) return -1;

	// key == k 인 노드가 있을 때
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

	// 트리 루트 초기화
	init();

	while (1) {
		scanf("%c", &command);
		switch (command) {

			// 삽입
		case 'i':
			scanf("%d", &key);
			insertItem(key);
			break;

			//삭제
		case 'd':
			scanf("%d", &key);
			deleteKey = removeElement(key);
			if (deleteKey == -1) printf("%c\n", 'X');
			else printf("%d\n", deleteKey);
			break;

			//탐색
		case 's':
			scanf("%d", &key);
			searchKey = findElement(key);
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
			exit(0);
			break;
		}
		getchar();
	}
}