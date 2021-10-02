#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	char elem;
	struct node* left, * right;
}NODE;

typedef struct treeType {
	NODE* p;
}treeType;

NODE* getnode(char elem) {
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	newnode->elem = elem;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

NODE* findnode(NODE *root, char elem, NODE **p) {
	if (root != NULL) {
		if (root->elem == elem) {
			*p = root;
		}
		else {
			findnode(root->left, elem, p);
			findnode(root->right, elem, p);
		}
	}
	else return 0;
}
void preorder(NODE * p) {
	if (p->elem != '0') {
		printf("%c", p->elem);
		preorder(p->left);
		preorder(p->right);
	}
	else {
		return 0;
	}
}
void print(treeType* tree) {
	preorder(tree->p);
}
int main() {
	treeType tree;
	tree.p = NULL;

	int n;
	scanf("%d", &n);
	getchar();
	
	int i;
	char rootElem, leftElem, rightElem;
	NODE* root, * left, * right, *p = NULL;
	for (i = 0; i < n; i++) {
		scanf("%c %c %c", &rootElem, &leftElem, &rightElem);
		getchar();
		if (tree.p != NULL) {
			findnode(tree.p, rootElem, &root);
			root->left = getnode(leftElem);
			root->right = getnode(rightElem);
		}
		else {
			//ÃÊ±âÈ­
			root = getnode(rootElem);
			left = getnode(leftElem);
			right = getnode(rightElem);
			
			root->left = left;
			root->right = right;

			tree.p = root;
		}
	}
	print(&tree);
}