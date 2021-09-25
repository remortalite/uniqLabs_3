#include "main.h"
#include "insertSort.h"
#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXRAND 100

void printTreeLeft(pVertex p) {
	if (p != NULL) {
		printTreeLeft(p->left);
		printf("%d ", p->data);
		printTreeLeft(p->right);
	}
}

int getRandom() {
	return rand() % MAXRAND;
}

pVertex createTree() {
	pVertex root = createVertex(getRandom());
	//left
	root->left = createVertex(getRandom());
	root->left->right = createVertex(getRandom());
	root->left->right->left = createVertex(getRandom());
	root->left->right->right = createVertex(getRandom());

	//right
	root->right = createVertex(getRandom());
	return root;	
}

int main() {
	//srand(time(0));
	printf("Lab1.\n");
	
	pVertex root = createTree();
	printTreeLeft(root);

	printf("Size: %d\n", treeSize(root));
	printf("Height: %d\n", treeHeight(root));

	return 0;
}

