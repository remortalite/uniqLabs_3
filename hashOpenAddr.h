#ifndef HASHOPENADDR
#define HASHOPENADDR

#include <stdlib.h>
#include <string.h>

char* hashOpenAddrLinear(char* line, int m)
{
	char *hashTable = calloc(sizeof(char), m);
	int length = strlen(line);

	int ost;
	int d = 1;
	int count = 0;
	for (int i = 0; i < length; ++i) {
		ost = (line[i] - 'a') % m;
		while (count < m) {
			if (hashTable[ost] == line[i]) break;
			if (hashTable[ost] == 0) {
				hashTable[ost] = line[i];
				++count;
				break;
			}
			ost = ost + d;
			if (ost >= m) ost = ost - m;
		}
	}
	return hashTable;
}

#endif // #ifndef HASHOPENADDR	
