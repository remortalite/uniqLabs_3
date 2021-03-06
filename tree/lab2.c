#include "tree.h"
#include "isdp.h"
#include "insertSort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *createRandArray(int N) {
	int *array = calloc(sizeof(int), N);
	for (int i = 0; i < N; ++i) {
		array[i] = rand() % 960;
	}
	return array;
}

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

pVertex SDPrec(int data, pVertex p) {
	if (p == NULL) {
		p = calloc(sizeof(tVertex), 1);
		p->data = data;
		p->left = NULL; p->right = NULL;
	} else {
		if (data < p->data)
			p->left = SDPrec(data, p->left);
		else {
			if (data > p->data)
				p->right = SDPrec(data, p->right);
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
	printf("\n\nPrint SDPrec: \n");
	pVertex root2 = SDPrec(array[0], NULL);
	for (int i = 1; i < 100; ++i)
		SDPrec(array[i], root2);
	printTreeLeft(root2);
	pVertex sdp_tree = NULL;
	for (int i = 0; i < 100; ++i)
		sdp_tree = SDP(array[i], sdp_tree);


	insertSort(array, 100);
	pVertex isdp_tree = ISDP(array, 0, 99);
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

