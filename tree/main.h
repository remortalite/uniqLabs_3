#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define N_DEF 500

// const int n = N_DEF;
// int A[100];

void printArr(int A[], int N)
{
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    putchar('\n');
}

void FillInc(int A[], int N)
{
    for (int i = 0; i < N; i++) {
        A[i] = i;
    }
}

void FillDec(int A[], int N)
{
    for (int i = 0; i < N; i++) {
        A[i] = N - 1 - i;
    }
}

void FillRand(int A[], int N)
{
    for (int i = 0; i < N; i++) {
        A[i] = rand() % (2 * N);
    }
}

void checkSum(int A[], int N)
{
    int finalSum = 0;
    for (int i = 0; i < N; i++) {
        finalSum += A[i];
    }

    printf("checkSum: %d\n", finalSum);
}

void RunNumber(int A[], int N)
{
    int count = 1;

    for (int i = 1; i < N; i++) {
        if (A[i] < A[i - 1]) {
            count += 1;
        }
    }
    printf("runNumber: %d\n", count);
}
