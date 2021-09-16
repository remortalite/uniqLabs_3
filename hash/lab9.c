#define STRING "malanovromanigorevich"

#define ISCHAR 1
#define PRINTNULL 0

#include "list.h"
#include "hash.h"

#include <stdio.h>

int main() {
	printf("Hashing.\n");
	putchar('\n');

	int *word = getArrUnique(STRING);
	int length = word[0];
	word = word+1;
	for (int i = 0; i < length; i++)
		printf("%c ", word[i]);

	int m = 5; 			/**** m *****/
	int ost;
	List ** arrayOfLists = calloc(sizeof(List*), m);
	for (int i =0; i < m; ++i)
		arrayOfLists[i] = NULL;

	for (int i = 0; i < length; ++i) {
		ost = (word[i] - 'a') % m;
		arrayOfLists[ost] = addList(arrayOfLists[ost], word[i]);
	}

	putchar('\n');
	putchar('\n');
	for (int i = 0; i < m; ++i) {
		printf("%d: ", i);
		printList(arrayOfLists[i]);
	}

	putchar('\n');

	printf("Element to find: ");
	char x;
	scanf("%c", &x);
	search(x, arrayOfLists, m);

	return 0;
}

