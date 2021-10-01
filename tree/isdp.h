#ifndef ISDP_H
#define ISDP_H

#include "tree.h"

pVertex ISDP(int *array, int idxStart, int idxEnd) {
	if (idxStart > idxEnd) return NULL;
	else {
		int idxMean = (idxEnd + idxStart) / 2;
		pVertex vertex = createVertex(array[idxMean]);
		vertex->left = ISDP(array, idxStart, idxMean-1);
		vertex->right = ISDP(array, idxMean+1, idxEnd);
		return vertex;
	}
}

#endif // #ifndef ISDP_H
