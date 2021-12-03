#include "fano.h"

#include <stdio.h>

int main() {
	printf("Fano.\n");
	
	int N = 11;

	int* array = calloc(sizeof(int), N);
	for (int i = 0; i < N; ++i)
		array[i] = rand() % N;

	float* P = calloc(sizeof(float), N);
	P[0] = 0.15;
	P[1] = 0.15;
	P[2] = P[3] = P[4] = P[5] = P[6] = 0.1;
	P[7] = P[8] = P[9] = P[10] = 0.05;

	int* Length = calloc(sizeof(int), N);
	int** C = calloc(sizeof(int*), N);
	for (int i = 0; i < N; ++i) C[i] = calloc(sizeof(int), N);
	
	for (int i = 0; i < N; ++i) {
		printf("%.2f\n", P[i]);
	}

	fano(P, 0, N-1, 0, C, Length);

	for (int i = 0; i < N; ++i)
		printf("Length: %d\n", Length[i]);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < Length[i]; ++j)
			printf("%d", C[i][j]);
		putchar('\n');
	}

	float Lmean = 0;
	for (int i = 0; i < N; ++i)
		Lmean += (Length[i] * P[i]);

	printf("Lmean: %f\n", Lmean);
	

	return 0;
}

