#ifndef INSERTSORT_H
#define INSERTSORT_H

#include "struct.h"

int insertSort(struct dict* A, int N)
{
    int i, j;
    struct dict t;
    for (i = 1; i < N; i++) {
        j = i - 1;
        t = A[i];
        while ((j >= 0) && (t.n > A[j].n)) {
            A[j + 1] = A[j];
            j -= 1;
        }
        A[j + 1] = t;
    }
}

#endif
