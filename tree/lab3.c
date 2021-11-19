#include "tree.h"
#include "sdp.h"

#include <stdio.h>
#include <stdlib.h>

void deleteSDP(int key, pVertex tree) {
	pVertex* p = &tree;
	while (*p != NULL) {
		if (key < (*p)->data)
			p = &((*p)->left);
		else {
			if (key > (*p)->data)
				p = &((*p)->right);
			else
				break;
		}
	}

	if (*p != NULL) {
		pVertex r = NULL;
	       	pVertex s = NULL;
		pVertex q = *p;
		if (q->left == NULL) {
			*p = q->right;
			return;
		}
		else {
			if (q->right == NULL) {
				*p = q->left;
				return;
			}
			else {
				r = q->left;
				s = q;
			}
		}

		if (r->right == NULL) {
			r->right = q->right;
			*p = r;
		}
		else {
			while (r->right != NULL) {
				s = r;
				r = r->right;
			}
			s->right = r->left;
			r->left = q->left;
			r->right = q->right;
			*p = r;
		}
		free(q);
	}
}


int main() {
	printf("Удаление из СДП.\n");

	int* array = calloc(100, sizeof(int));
	for (int i = 0; i < 100; ++i) array[i] = rand() % 100;

	pVertex tree = NULL;	
	for (int i = 0; i < 100; ++i) tree = SDPrec(array[i], tree);

	printTreeLeft(tree);

	for (int i= 0 ; i < 10; ++i) {
		int key;
		printf("\n\nEnter the key: ");
		scanf("%d", &key);
		putchar('\n');
		deleteSDP(key, tree);

		printTreeLeft(tree);
	
	}

	return 0;
}

