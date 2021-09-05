//#define LINE "malanovromanigorevich"
#define LINE "qwertyuiopasdfghjklzxcvbnm"

#ifndef TABLE
#define TABLE 1
#endif

#include "hashOpenAddr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printTable(char* line, int size) {
	int n = -5;
	for (int i = 0; i < size; ++i)
		printf("%*d", n, i);
	putchar('\n');
	for (int i = 0; i < size; ++i)
		printf("%*c", n, line[i] ? line[i] : ' ');
	putchar('\n');
}

int main() {
	printf("Hashing2. Open addressing. Linear and quadratic probing.\n");

	int m;

	printf("Enter m: \n");
	scanf("%d", &m);

	int length = strlen(LINE);
	char *line = calloc(sizeof(int), length);
	for (int i = 0; i < length; ++i)
		line[i] = (char) LINE[i];
	for (int i = 0; i < length; ++i)
		printf("%c", line[i]);
	putchar('\n');
	putchar('\n');

	int coll;

	printf("Linear probing:\n");
	char *hashTable = hashOpenAddrLinear(line, m, &coll);
	printTable(hashTable, m);
	printf("Collisions: %d\n", coll);

	putchar('\n');

	printf("Quadratic probing:\n");
	char *hashTable2 = hashOpenAddrQuadratic(line, m, &coll);
	printTable(hashTable2, m);
	printf("Collisions: %d\n", coll);

	{
		char c;
		while ((c = getchar()) != '\n' && c != EOF) { }
	}

	int key;
	printf("\n--------------\n");
	printf("\nEnter element to find: ");
	scanf("%c", &key);

	printf("\nSearch in linear:\n");
	searchOpenAddrLinear(key, hashTable, m);

	printf("\nSearch in quadratic:\n");
	searchOpenAddrLinear(key, hashTable2, m);


	if (TABLE) {
		printf("\n\n=========\n\n");

		printf("|%-20s|%-20s|%13s %-27s|\n", "Table size", "Symbols", " ", "Collisions");
		printf("|%-20s|%-20s|%-20s|%-20s|\n", " ", " ", "Linear", "Quadratic");
		char *hashTableTest;
		int collLinear;
		int collQuadratic;
		for (int tablesize = 1; tablesize < 50; ++tablesize) {
			hashOpenAddrLinear(line, tablesize, &collLinear);	
			hashOpenAddrQuadratic(line, tablesize, &collQuadratic);		
			printf("|%-20d|%-20d|%-20d|%-20d|\n", tablesize, strlen(line), collLinear, collQuadratic);
		}
	}
	
	return 0;
}

