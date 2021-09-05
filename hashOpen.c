#define LINE "malleusmaleficorum"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
		printf("Hashing2.\n");

		int m;

		printf("Enter m: \n");
		scanf("%d", &m);
	
		int * hashTable = calloc(sizeof(int), m);

		int length = strlen(LINE);
		int *line = calloc(sizeof(int), length);
		for (int i = 0; i < length; ++i)
			line[i] = (int) LINE[i];
		for (int i = 0; i < length; ++i)
			printf("%c ", line[i]);

		int ost;
		int d = 1;
		for (int i = 0; i < length && i < m; ++i) {
			ost = i % m;
			while (1) {
				if (hashTable[ost] == line[i]) break;
				if (hashTable[ost] == 0) {
					hashTable[ost] = line[i];
					break;
				}
				if (d >= m) break;
				ost = ost + d;
				if (ost >= m) ost = ost - m;
			}
		}

		putchar('\n');
		for (int i = 0; i < m; ++i)
			printf("%d\t", i);
		putchar('\n');
		for (int i = 0; i < m; ++i)
			printf("%c\t", hashTable[i]);


		return 0;
}

