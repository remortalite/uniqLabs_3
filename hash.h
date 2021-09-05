#include "list.h"

#include <string.h>

int isLetterInArray(int letter, int* array) {
	int length = array[0];
	for (int i = 0; i < length; ++i) {
		if (array[i] == letter)
			return 1;
	}
	return 0;
}

int *getArrUnique(char* line) {
	int length = strlen(line);
	int *array = calloc(sizeof(int), length+1);
	array[1] = (int) line[0];
	int counter = 2;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < i; j++)
			if (isLetterInArray(line[i], array+1) == 0)
				array[counter++] = (int) line[i];
	array[0] = counter-1;
	return array;
}

void search(char x, List ** arrayOfLists, int sizeHashTable) {
	int CM = 0;
	int m = sizeHashTable;
	int ost = (x-'a') % m;
	List *el = arrayOfLists[ost];
	for (int idx = 0; el; el = el->next, idx++)
		if (el->num == x) {
			printf("Element '%c' is found. \nList:\t%d \nIdx:\t%d", x, ost, idx);
			return;
		}
	printf("Element '%c' is not found.\n", x);
}
