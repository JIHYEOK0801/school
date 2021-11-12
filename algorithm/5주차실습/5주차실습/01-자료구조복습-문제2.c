#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	int elem;
	struct node* left, * right;

}node;
typedef struct treeType {
	node* root;
}treeType;
node* makeNewNode(int elem) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->elem = elem;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}
void connectLeft(node* root, node* left) {
	root->left = left;
}
void connectRight(node* root, node* right) {
	root->right = right;
}
void init(treeType *tree, int rootElem, int leftElem, int rightElem) {
	tree->root = makeNewNode(rootElem);
	node* left = makeNewNode(leftElem);
	node* right = makeNewNode(rightElem);

	connectLeft(tree->root, left);
	connectRight(tree->root, right);
}
void findElement(node* root, int target, int leftElem, int rightElem) {
	node* left, * right;
	if (root != NULL) {
		if (root->elem == target) {
			left = makeNewNode(leftElem);
			right = makeNewNode(rightElem);
			connectLeft(root, left);
			connectRight(root, right);
		}
		else {
			findElement(root->left,target,leftElem,rightElem);
			findElement(root->right,target, leftElem, rightElem);
		}
	}
}
void searchTree(node* root, char* command) {
	node* p = root;
	char* c = command;

	printf(" %d", p->elem);
	while (*c != '\0') {
		if (*c == 'L') {
			p = p->left;
			printf(" %d", p->elem);
		}
		else {
			p = p->right;
			printf(" %d", p->elem);
		}
		c = c + 1;
	}
	printf("\n");
	
}
//확인용 print함수
void print(node* root) {
	if (root != NULL) {
		printf("%d ", root->elem);
		print(root->left);
		print(root->right);
	}
}
int main() {
	treeType tree;
	node* p = NULL, * left, * right;
	int n;
	scanf("%d", &n);

	int i;
	int rootElem, leftElem, rightElem;
	for (i = 0; i < n; i++) {
		scanf("%d %d %d", &rootElem, &leftElem, &rightElem);
		//printf("root : %d left : %d right : %d\n", rootElem, leftElem, rightElem);//확인용도
		//처음이 아닐때
		if (i > 0){
			findElement(tree.root, rootElem, leftElem, rightElem);
		}
		// 처음 : 루트 초기화
		else {
			init(&tree, rootElem, leftElem, rightElem);
		}
		/*
		print(tree.root);//확인용도
		printf("\n");//확인용도
		printf("\n");//확인용도
		*/
	}
	
	
	scanf("%d", &n);

	char command[101];
	for (i = 0; i < n; i++) {
		scanf("%s", command);
		searchTree(tree.root, command);
	}

}

