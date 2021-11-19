#include "tree.h"
#include "dbtree.h"
#include "avl.h"

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

	printf("%-10s|%-10s|%-10s|%-10s|%-10s\n", "n=100", "size", "checksum", 
			"height", "mean height");

	pVertex treeAVL = NULL;
	for (int i = 0; i < 100; ++i) treeAVL = addAVL(array[i], treeAVL);

	printf("%-10s|%-10d|%-10d|%-10d|%-10f\n", 
			"AVL", 
			treeSize(treeAVL),
			treeChecksum(treeAVL),
			treeHeight(treeAVL),
			treeMeanHeight(treeAVL, 1)
	      );

	printf("%-10s|%-10d|%-10d|%-10d|%-10f\n", 
			"DBD", 
			treeSize(tree),
			treeChecksum(tree),
			treeHeight(tree),
			treeMeanHeight(tree, 1)
	      );

	return 0;
}

