#include "struct.h"
#include "insertSort.h"
#include "fano.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	printf("Coding.\n");

	FILE *fp;
	fp = fopen("testBase4.dat", "rb");
	if (fp == NULL)
		printf("ERROROROROROROR\n");

	int allSymbols = 4000*(32+18+10+2);

	printf("Size: %d\n", allSymbols);
	char* text = malloc(sizeof(short int)*allSymbols);

	int i = fread(text, sizeof(struct record), allSymbols, fp);
	if (i == allSymbols) printf("Read succesfully!\n");

	struct dict* unique = malloc(sizeof(struct dict)*allSymbols);
	int uniqueCount = 0;

	for (int i = 0; i < allSymbols; ++i) {
		int found = 0;
		for (int j = 0; j < uniqueCount; ++j) {
			if (text[i] == unique[j].c) 
			{
				unique[j].n += 1;
				found = 1;
				break;
			}
		}
		if (found == 0) {
			unique[uniqueCount].c = text[i];
			unique[uniqueCount].n = 1;
			uniqueCount++;
		}
	}
	printf("Unique count: %d\n", uniqueCount);

	// for (int i = 0; i < uniqueCount; ++i) printf("%x %-4d\n", unique[i].c, unique[i].n);

	insertSort(unique, uniqueCount);

	// for (int i = 0; i < uniqueCount; ++i) printf("%x %-4d\n", unique[i].c, unique[i].n);

	float* P = calloc(sizeof(float), uniqueCount);
	for (int i = 0; i < uniqueCount; ++i) {
		P[i] = unique[i].n*1.0 / allSymbols;
	}

	int** C = calloc(sizeof(int*), uniqueCount);
	for (int i = 0; i < uniqueCount; ++i) C[i] = calloc(sizeof(int), uniqueCount);
	int* Length = calloc(sizeof(int), uniqueCount);

	fano(P, 0, uniqueCount-1, 0, C, Length);

	for (int i = 0; i < uniqueCount; ++i) {
		for (int j = 0; j < Length[i]; ++j)
			printf("%d", C[i][j]);
		putchar('\n');
	}

	double H = 0.0;
	double Lmean = 0.0;
	for (int i = 0; i < uniqueCount; ++i) {
		H += ( P[i] * log2(P[i]) );
		Lmean += ( P[i] * Length[i] );
	}

	printf("Entropy \tH = %.4f\n", -H);
	printf("Lmean \t\tL = %.4f\n", Lmean);
	
	#ifdef WRITE_UNIQUE
		FILE* fout;
		fout = fopen("unique.txt", "w");
		for (int i = 0; i < uniqueCount; ++i) {
			fprintf(fout, "%c %d ", unique[i].c, unique[i].n);
			for (int j = 0; j < Length[i]; ++j)
				fprintf(fout, "%d", C[i][j]);
			fprintf(fout, "\n");
		}
		fclose(fout);
		system("iconv -f cp866 -t utf8 unique.txt -o unique.txt");
	#endif


	return 0;
}

