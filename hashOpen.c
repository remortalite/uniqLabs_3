#define LINE "malanovromanigorevich"

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
}

int main() {
	printf("Hashing2. Open addressing. Linear probing.\n");

	int m;

	printf("Enter m: \n");
	scanf("%d", &m);

	int length = strlen(LINE);
	char *line = calloc(sizeof(int), length);
	for (int i = 0; i < length; ++i)
		line[i] = (char) LINE[i];
	for (int i = 0; i < length; ++i)
		printf("%c", line[i]);

	char *hashTable = hashOpenAddrLinear(line, m);

	putchar('\n');
	printTable(hashTable, m);

	return 0;
}

