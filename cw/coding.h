#include "struct.h"
#include "insertSort.h"
#include "fano.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int runCoding() {
	FILE *fp;
	fp = fopen("testBase4.dat", "rb");
	if (fp == NULL) {
		printf("File 'textBase4.dat' not found.\n");
		return 1;
	}

	int allSymbols = 4000*(32+18+10+2);

	printf("Size: %d\n", allSymbols);
	struct record* records = malloc(sizeof(struct record)*4000);
	unsigned char* text = malloc(sizeof(unsigned char)*allSymbols);

	int i = fread(text, sizeof(unsigned char), allSymbols, fp);
	if (i == 4000) printf("Read succesfully!\n");

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

	insertSort(unique, uniqueCount);

	float* P = calloc(sizeof(float), uniqueCount);
	for (int i = 0; i < uniqueCount; ++i) {
		P[i] = unique[i].n*1.0 / allSymbols;
	}

	int** C = calloc(sizeof(int*), uniqueCount);
	for (int i = 0; i < uniqueCount; ++i) C[i] = calloc(sizeof(int), uniqueCount);
	int* Length = calloc(sizeof(int), uniqueCount);

	fano(P, 0, uniqueCount-1, 0, C, Length);

	for (int i = 0; i < uniqueCount; ++i) {
		printf("%.5f\t\t", P[i]);
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

	for (int i = 0; i < uniqueCount; ++i) {
		unique[i].code = calloc(sizeof(char), Length[i]+1);
		for (int j = 0; j < Length[i]; ++j)
			unique[i].code[j] = (char)('0'+C[i][j]);
		unique[i].code[Length[i]] = '\0';
	}

	getchar();

	return 0;
}
