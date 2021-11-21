#ifndef DOP_H
#define DOP_H

int** getAW(int* W) {
	int AW[N][N] = {};
	for (int i = 0; i < N; ++i)
		for (int j = i+1 ; j < N; ++j)
			AW[i][j] = AW[i][j-1] + W[j];
	return AW;
}



#endif // #ifndef DOP_H
