#include "tree.h"
#include "avl.h"

#include <stdio.h>
#include <time.h>

int check() {
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

	for (int i = 0; i < 100; ++i) array[i] = rand() % 101;
	//for (int i = 0; i < 100; ++i) printf("%d ", array[i]);
	putchar('\n');

	pVertex tree = NULL;
	
	for (int i = 0; i < 100; ++i) tree = addAVL(array[i], tree);

	printTreeLeft(tree);
	putchar('\n');
	printf("MeanHeight: %d\n", treeMeanHeight(tree, 1));
	printf("Height: %d\n", treeHeight(tree));
	printf("heightLeft: %d\n", treeHeight(tree->left));
	printf("heightRight: %d\n", treeHeight(tree->right));

	return 0;
}

