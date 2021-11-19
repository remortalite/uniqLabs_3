#include "tree.h"
#include "avl.h"
#include "sdp.h"

#include <stdio.h>
#include <time.h>

void check() {
	pVertex tree = createVertex(4);
	tree->right = createVertex(6);
	tree->right->right = createVertex(7);

	tree = RR(tree);

	printf("  _____%d_____  \n", tree->data);
	printf("  %d          %d\n", tree->left->data, tree->right->data);

	tree = createVertex(4);
	tree->right = createVertex(6);
	tree->right->left = createVertex(5);

	tree = RL(tree);

	printf("  _____%d_____  \n", tree->data);
	printf("  %d          %d\n", tree->left->data, tree->right->data);
	

	tree = createVertex(4);
	tree->left = createVertex(2);
	tree->left->left = createVertex(1);

	tree = LL(tree);

	printf("  _____%d_____  \n", tree->data);
	printf("  %d          %d\n", tree->left->data, tree->right->data);
	
	tree = createVertex(4);
	tree->left = createVertex(2);
	tree->left->right = createVertex(3);

	tree = LR(tree);

	printf("  _____%d_____  \n", tree->data);
	printf("  %d          %d\n", tree->left->data, tree->right->data);

}

int main() {
	srand(time(0));
	printf("АВЛ дерево\n");

	int *array = calloc(100, sizeof(int));

	for (int i = 0; i < 100; ++i) array[i] = rand() % 100 + 1;
	for (int i = 0; i < 100; ++i) printf("%d ", array[i]);
	putchar('\n');

	pVertex tree = NULL;
	
	for (int i = 0; i < 100; ++i) tree = addAVL(array[i], tree);

	printTreeLeft(tree);
	putchar('\n');

	pVertex treeSDP = NULL;
	for (int i = 0; i < 100; ++i) treeSDP = SDPrec(array[i], treeSDP);

	printf("%-10s|%-10s|%-10s|%-10s|%-10s\n", "n=100", "size", "checksum", 
			"height", "mean height");

	printf("%-10s|%-10d|%-10d|%-10d|%-10f\n", 
			"SDP", 
			treeSize(treeSDP),
			treeChecksum(treeSDP),
			treeHeight(treeSDP),
			treeMeanHeight(treeSDP, 1)
	      );

	printf("%-10s|%-10d|%-10d|%-10d|%-10f\n", 
			"AVL", 
			treeSize(tree),
			treeChecksum(tree),
			treeHeight(tree),
			treeMeanHeight(tree, 1)
	      );


	return 0;
}

