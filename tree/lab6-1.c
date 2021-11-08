#include "tree.h"
#include "avl.h"
#include "avl_delete.h"

#include <stdio.h>

int main() {
	printf("Delete from AVL\n\n");

	pVertex tree = NULL;

	int N = 15;
	int *array = malloc(sizeof(int)*N);
	for (int i = 0; i < N; ++i) array[i] = rand() % 300;
	for (int i = 0; i < N; ++i) tree = addAVL(array[i], tree);
	
	printTreeLeft(tree);

	putchar('\n');
	putchar('\n');

	for (int i = 0; i < 10; ++i) {
		int key;
		printf("\nEnter key: ");
		scanf("%d", &key);
		putchar('\n');
		putchar('\n');

		printf("key: %d\n", key);
		tree = deleteAVL(key, tree);
		putchar('\n');

		printTreeLeft(tree);
		putchar('\n');
		
		printf("treeSize: \t%d\n", treeSize(tree));
		printf("heightLeft: \t%d\n", treeHeight(tree->left));
		printf("heightRight: \t%d\n", treeHeight(tree->right));

	}

	return 0;
}

