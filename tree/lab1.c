#include "main.h"
#include "insertSort.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex tVertex;
typedef tVertex* pVertex;

struct Vertex {
	int data;
	pVertex left;
	pVertex right;
};

void example();
int max(int a, int b) {
	return a < b ? b : a;
}

pVertex createVertex(int data) {
	pVertex vertex = calloc(sizeof(tVertex), 1);
	vertex->data = data;
	vertex->left = NULL;	
	vertex->right = NULL;	
	return vertex;
}

pVertex createTree(int *array, int idxStart, int idxEnd) {
	if (idxStart > idxEnd) return NULL;
	else {
		int idxMean = (idxEnd + idxStart) / 2;
		pVertex vertex = createVertex(array[idxMean]);
		vertex->left = createTree(array, idxStart, idxMean-1);
		vertex->right = createTree(array, idxMean+1, idxEnd);
		return vertex;
	}
}

void printTreeLeft(pVertex p) {
	if (p != NULL) {
		printTreeLeft(p->left);
		printf("%d ", p->data);
		printTreeLeft(p->right);
	}
}

int treeSize(pVertex p) {
	int size = 0;
	if (p == NULL) return 0;
	else {
		size = 1 + treeSize(p->left) + treeSize(p->right);
	}
	return size;
}

int treeChecksum(pVertex p) {
	int sum = 0;
	if (p == NULL) return 0;
	else {
		sum = p->data + treeChecksum(p->left) + treeChecksum(p->right);
	}
	return sum;
}

int treeHeight(pVertex p) {
	int height = 0;
	if (p == NULL) return 0;
	else {
		height = 1 + max(treeHeight(p->left), treeHeight(p->right));
	}
	return height;
}

int treeMeanHeight(pVertex p, int L /*level*/) {
	int sumLength = 0;
	if (p == NULL) return 0;
	else {
		sumLength = L + treeMeanHeight(p->left, L+1) + treeMeanHeight(p->right, L+1);
	}
	return sumLength / treeSize(p);
}


int main() {
	printf("Lab1.\n");

	int N = 100;
	int *array = calloc(sizeof(int), N);
	FillInc(array, N);

	pVertex root = createTree(array, 0, N-1);

	printTreeLeft(root);

	putchar('\n');
	printf("Size: %d\n", treeSize(root));
	printf("Checksum tree: %d\n", treeChecksum(root));
	//checkSum(array, N);
	
	printf("Height: %d\n", treeHeight(root));
	printf("Mean height: %d\n", treeMeanHeight(root, 1));

	//example();

	return 0;
}

void example() {

	int N = 16;

	int *array = calloc(sizeof(int), N);
	FillInc(array, N);
	printArr(array, N);

	pVertex root = createTree(array, 1, N-1);

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


