#include "tree.h"
#include "avl.h"
#include "sdp.h"

#include <stdio.h>
#include <time.h>

int main() {
	srand(time(0));
	printf("АВЛ дерево\n");

	int *array = calloc(100, sizeof(int));
	pVertex tree = NULL;

	for (int i = 0; i < 100; ++i) array[i] = rand() % 200 + 1;
	for (int i = 0; i < 100; ++i) tree = addAVL(array[i], tree);

	printTreeLeft(tree);
	
	return 0;
}

