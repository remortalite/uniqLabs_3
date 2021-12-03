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
	if (fp == NULL) printf("File 'textBase4.dat' not found.\n");

	int allSymbols = 4000*(32+18+10+3+3+4);

	printf("Size: %d\n", allSymbols);
	//char* text = malloc(sizeof(short int)*allSymbols);
	struct record* records = malloc(sizeof(struct record)*4000);
	char* text = malloc(sizeof(char)*allSymbols);

	int i = fread(records, sizeof(struct record), 4000, fp);
	if (i == 4000) printf("Read succesfully!\n");

	struct dict* unique = malloc(sizeof(struct dict)*allSymbols);
	int uniqueCount = 0;

	int index = 0;
	for (int i = 0; i < 4000; ++i) {
		for (int j = 0; j < 32; ++j) text[index++] = records[i].person[j];
		for (int j = 0; j < 18; ++j) text[index++] = records[i].street[j];
		
		char strHouse[10];
		sprintf(strHouse, "%03d", records[i].house);
		for (int j=0; j < strlen(strHouse); ++j) text[index++] = strHouse[j];

		char strApt[10];
		sprintf(strApt, "%03d", records[i].apt); 
		for (int j=0; j < strlen(strApt); ++j) text[index++] = strApt[j];
	}

	printf("Size (index): %d\n", index);
	allSymbols = index;

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

	// for (int i = 0; i < uniqueCount; ++i) printf("%c %.4f\n", unique[i].c, P[i]);
	
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

	for (int i = 0; i < uniqueCount; ++i) {
		unique[i].code = calloc(sizeof(char), Length[i]+1);
		for (int j = 0; j < Length[i]; ++j)
			unique[i].code[j] = (char)('0'+C[i][j]);
		unique[i].code[Length[i]] = '\0';
	}

	FILE * foutCode;
	foutCode = fopen("code.dat", "wb");
	for (int i = 0; i < allSymbols; ++i) {
		for (int j = 0; j < uniqueCount; ++j)
			if (unique[j].c == text[i]) {
				for (int k = 0; k < Length[j]; ++k) {
					fwrite(unique[j].code+k, 1,1, foutCode);
				}
				continue;
			}
	}

	return 0;
}
