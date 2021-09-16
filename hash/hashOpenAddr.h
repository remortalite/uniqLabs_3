#ifndef HASHOPENADDR
#define HASHOPENADDR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* hashOpenAddrLinear(char* line, int m, int *collisions)
{
	char *hashTable = calloc(sizeof(char), m);
	int length = strlen(line);

	int ost;
	int d = 1;
	int count = 0;
	*collisions = 0;
	for (int i = 0; i < length; ++i) {
		ost = (line[i] - 'a') % m;
		while (count < m) {
			if (hashTable[ost] == line[i]) break;
			if (hashTable[ost] == 0) {
				hashTable[ost] = line[i];
				++count;
				break;
			}
			++(*collisions);
			ost = ost + d;
			if (ost >= m) ost = ost - m;
		}
	}
	return hashTable;
}

char* hashOpenAddrQuadratic(char* line, int m, int *collisions)
{
	char *hashTable = calloc(sizeof(char), m);
	int length = strlen(line);

	int ost;
	int count = 0;
	*collisions = 0;
	for (int i = 0; i < length; ++i) {
		ost = (line[i] - 'a') % m;
		int d = 1;
		while (count < m) {
			//printf("Check element '%c' (%d)\n", hashTable[ost], ost);
			if (hashTable[ost] == line[i]) break;
			if (hashTable[ost] == 0) {
				hashTable[ost] = line[i];
				++count;
				break;
			}
			if (d >= m) break; 
			++(*collisions);
			ost = ost + d;
			d = d + 2;
			if (ost >= m) ost = ost - m;
		}
		if (d >= m) {
			break;
		}
	}
	return hashTable;
}

int searchOpenAddrLinear(char key, char* hashTable, int m)
{
	int ost = (key - 'a') % m;
	int d = 1;
	int count = 0;
	while (count < m) {
		if (hashTable[ost] == key) {
			printf("Element is found.\n");
			printf("Idx: %d\n", ost);
			return ost;
		}
		if (hashTable[ost] == 0) {
			printf("Element '%c' is not found.\n", key);
			return -1;
		}
		if (d >= m) break; 
		ost = ost + d;
		if (ost >= m) ost = ost - m;
		++count;
	}
	printf("Element '%c' is not found.\n", key);
	return -1;
}

int searchOpenAddrQuadratic(char key, char* hashTable, int m)
{
	int ost = (key - 'a') % m;
	int d = 1;
	int count = 0;

	if (hashTable[ost] == 0) {
			printf("Element '%c' is not found.\n", key);
			return -1;
	}

	while (count < m) {
		//printf("Check element '%c' (%d)\n", hashTable[ost], ost);
		if (hashTable[ost] == key) {
			printf("Element is found.\n");
			printf("Idx: %d\n", ost);
			return ost;
		}
		if (d >= m) break; 
		ost = ost + d;
		d = d + 2;
		if (ost >= m) ost = ost - m;
		++count;
	}
	printf("Element '%c' is not found.\n", key);
	return -1;
}

#endif // #ifndef HASHOPENADDR	
