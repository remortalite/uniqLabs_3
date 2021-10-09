#include "tree.h"
#include "isdp.h"
#include "insertSort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

pVertex SDP(int data, pVertex root) {
	pVertex *p = &root;
	while (*p != NULL) {
		if (data < (*p)->data) p = &((*p)->left);
		else {
			if (data > (*p)->data) p = &((*p)->right);
			else break;
		}
	}
	if (*p == NULL) {
		(*p) = createVertex(data);
		(*p)->left = NULL;
		(*p)->right = NULL;
	}
	return root;
}

int *createRandArray(int N) {
	int *array = calloc(sizeof(int), N);
	for (int i = 0; i < N; ++i) {
		array[i] = rand() % 960;
	}
	return array;
}

pVertex SDPrec(int data, pVertex p) {
	if (p == NULL) {
		p = createVertex(data);
		p->left = NULL; p->right = NULL;
	} else {
		if (data < p->data)
			p = SDPrec(data, p->left);
		else {
			if (data > p->data)
				p = SDPrec(data, p->right);
			else {
				//printf("Exists\n");;
			}
		}
	}
	return p;
}

int main() {
	srand(time(0));
	printf("Lab2.\n");
	
	pVertex root = NULL;

	printf("Array: ");
	int *array = createRandArray(100);
	for (int i = 0; i < 100; ++i) {
		printf("%d ", array[i]);
	}
	putchar('\n'); putchar('\n');

	for (int i = 0; i < 100; ++i) 
		root = SDP(array[i], root);

	printf("\nPrint SDP: \n");
	printTreeLeft(root);

	/* SDP recursive */
	printf("\nPrint SDPrec: \n");
	pVertex root2 = NULL;
	for (int i = 0; i < 100; ++i)
		root2 = SDPrec(array[i], root2);
	printTreeLeft(root2);

	insertSort(array, 100);
	pVertex isdp_tree = ISDP(array, 0, 99);
	pVertex sdp_tree = NULL;
	for (int i = 0; i < 100; ++i)
		sdp_tree = SDP(array[i], sdp_tree);

	printf("\n\nPrint ISDP: \n");
	printTreeLeft(isdp_tree);

	printf("\n\n");
	printf("%10s|%10s|%10s|%10s|%13s\n", "n=100","size","checksum","height","mean height");
	printf("%10s|%10d|%10d|%10d|%10.3f\n", 
					"isdp",
					treeSize(isdp_tree),
					treeChecksum(isdp_tree),
					treeHeight(isdp_tree),
					treeMeanHeight(isdp_tree,1));

	printf("%10s|%10d|%10d|%10d|%10.3f\n", 
					"sdp",
					treeSize(sdp_tree),
					treeChecksum(sdp_tree),
					treeHeight(sdp_tree),
					treeMeanHeight(sdp_tree,1));


	return 0;
}

