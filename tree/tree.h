#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex tVertex;
typedef tVertex* pVertex;

struct Vertex {
	int data;
	pVertex left;
	pVertex right;
	int bal;
};

pVertex createVertex(int data) {
	pVertex vertex = calloc(sizeof(tVertex), 1);
	vertex->data = data;
	vertex->left = NULL;
	vertex->right = NULL;
	return vertex;
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
	else sum = p->data + treeChecksum(p->left) + treeChecksum(p->right);
	return sum;
}

int max(int a, int b) {
	return a < b ? b : a;
}

int treeHeight(pVertex p) {
	int height = 0;
	if (p == NULL) return 0;
	else height = 1 + max(treeHeight(p->left), treeHeight(p->right));
	return height;
}

int sumAllLength(pVertex p, int L) {
    int sum = 0;
    if (p == NULL) return 0;
    else sum = L + sumAllLength(p->left, L+1) + sumAllLength(p->right, L+1);
    return sum;
}

float treeMeanHeight(pVertex p, int L) {
    return sumAllLength(p, L) * 1.0 / treeSize(p);
}

void printTreeLeft(pVertex p) {
	if (p != NULL) {
		printTreeLeft(p->left);
		printf("%d ", p->data);
		printTreeLeft(p->right);
	}
}

#endif // #ifndef TREE_H
