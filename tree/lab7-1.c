#include "tree.h"
#include "dbtree.h"

#include <stdio.h>
#include <time.h>

int main() {
	srand(time(0));
	printf("Двоичное Б-дерево\n");

	int *array = calloc(100, sizeof(int));

	for (int i = 0; i < 100; ++i) array[i] = rand() % 100 + 1;
	for (int i = 0; i < 100; ++i) printf("%d ", array[i]);
	putchar('\n');

	pVertex tree = NULL;
	
	for (int i = 0; i < 100; ++i) tree = addDBtree(array[i], tree);

	printTreeLeft(tree);
	putchar('\n');
/*
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

*/
	return 0;
}

