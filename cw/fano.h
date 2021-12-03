#ifndef FANO_H
#define FANO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int med(float* P, int L, int R) {
	int m;
	float SL, SR;
	SL = 0;
	for (int i = L; i < R; ++i)
		SL += P[i];
	SR = P[R];
	m = R;
	while (SL >= SR) {
		--m;
		SL -= P[m];
		SR += P[m];
	}
	return m;
}

void fano(float* P, int L, int R, int k, int** C, int* Length) {
	int m;
	//printf("fano: left %d -- right %d\n", L, R);

	if (L < R) {
		++k;
		m = med(P, L, R);
		//printf("Median: %d\n", m);
		for (int i = L; i <= R; ++i) {
			if (i <= m) 	C[i][k-1] = 0;
			else 		C[i][k-1] = 1;
			Length[i] += 1;
		}
		fano(P, L, m, k, C, Length);
		fano(P, m+1, R, k, C, Length);
	}
}


#endif // #ifndef FANO_H
