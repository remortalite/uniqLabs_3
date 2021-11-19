#include "main.h"
#include "insertSort.h"
#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXRAND 100

int getRandom() {
	return rand() % MAXRAND;
}

pVertex createTree() {
	pVertex root = createVertex(getRandom());
	//left
	root->left = createVertex(getRandom());
	root->left->left = createVertex(getRandom());
	root->left->right = createVertex(getRandom());
	root->left->right->left = createVertex(getRandom());
	root->left->right->right = createVertex(getRandom());

	//right
	root->right = createVertex(getRandom());
	return root;	
}

void print(pVertex root) {
	printf("        _______%d_______       \n", root->data);
	printf("    ____%d______       %d      \n", root->left->data, root->right->data);
	printf("    %d  _______%d_______       \n", root->left->left->data, root->left->right->data);
	printf("        %d             %d      \n", root->left->right->left->data, root->left->right->right->data);
}

int main() {
	//srand(time(0));
	printf("Lab0.\n");
	
	pVertex root = createTree();
	printTreeLeft(root);

	putchar('\n');
	printf("Size: %d\n", treeSize(root));
	printf("Height: %d\n", treeHeight(root));
	printf("Mean height: %.3f\n", treeMeanHeight(root, 1));
	printf("Checksum: %d\n", treeChecksum(root));

	print(root);

	return 0;
}

