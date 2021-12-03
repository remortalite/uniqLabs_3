#include "main.h"
#include "insertSort.h"
#include "tree.h"

#include <stdio.h>
#include <stdlib.h>


void example();

pVertex createISDP(int *array, int idxStart, int idxEnd) {
	if (idxStart > idxEnd) return NULL;
	else {
		int idxMean = (idxEnd + idxStart) / 2;
		pVertex vertex = createVertex(array[idxMean]);
		vertex->left = createISDP(array, idxStart, idxMean-1);
		vertex->right = createISDP(array, idxMean+1, idxEnd);
		return vertex;
	}
}

int main() {
	printf("Lab1.\n");

	int N = 100;
	int *array = calloc(sizeof(int), N);
	
	FillInc(array, N);
	//for (int i = 0; i < N; i++) array[i] = rand() % 2000;
	//insertSort(array, N);

	pVertex root = createISDP(array, 0, N-1);

	printf("Print tree:\n");
	printTreeLeft(root);

	putchar('\n');
	putchar('\n');
	printf("Size: %d\n", treeSize(root));
	printf("Checksum tree: %d\n", treeChecksum(root));
	//checkSum(array, N);
	
	printf("Height: %d\n", treeHeight(root));
	printf("Mean height: %.3f\n", treeMeanHeight(root, 1));

	//example();

	return 0;
}

void example() {

	int N = 16;

	int *array = calloc(sizeof(int), N);
	FillInc(array, N);
	printArr(array, N);

	pVertex root = createISDP(array, 1, N-1);

	printf("%d\n", root->data);
	printf("%d\t\t%d\n", root->left->data, root->right->data);
	printf("%d %d\t\t%d %d\n", 
			root->left->left->data, root->left->right->data, 
			root->right->left->data, root->right->right->data);
	printf("%d %d %d %d\t\t%d %d %d %d\n", 
			root->left->left->left->data, 
			root->left->left->right->data, 
			root->left->right->left->data, 
			root->left->right->right->data, 

			root->right->left->left->data, 
			root->right->left->right->data, 
			root->right->right->left->data, 
			root->right->right->right->data
	      );

	printTreeLeft(root);
}


