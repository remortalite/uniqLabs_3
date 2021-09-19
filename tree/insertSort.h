
int insertSort(int A[], int N)
{
    int i, j, t;
    int C = 0, M = 0;
    for (i = 1; i < N; i++) {
        j = i - 1;
        t = A[i];
        M++;
        C++;
        while ((j >= 0) && (t < A[j])) {
            if (j > 0)
                C++;
            A[j + 1] = A[j];
            M++;
            j -= 1;
        }
        A[j + 1] = t;
        M++;
    }
    return C + M;
}
