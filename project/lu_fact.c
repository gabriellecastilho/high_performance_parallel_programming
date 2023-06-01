#include <stdio.h>
#include <stdlib.h>

void LU_factorization(int **A, int **L, int **U, int n)
{
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j)
                L[i][j] = 1.0;
            else
                L[i][j] = 0.0;
            U[i][j] = A[i][j];
        }
    }

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            L[j][i] = U[j][i] / U[i][i];
            for (k = i; k < n; k++) {
                U[j][k] -= L[j][i] * U[i][k];
            }
        }
    }
}

void print_matrices(int **A, int **L, int **U, int n)
{
    int i, j;

    printf("Matrix A:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%6d\t", A[i][j]);
        printf("\n");
    }

    printf("Matrix L:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%6d\t", L[i][j]);
        printf("\n");
    }

    printf("Matrix U:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%6d\t", U[i][j]);
        printf("\n");
    }
}

int main(void)
{
    int n;
    int i, j;

    printf("Please, add the number n of dimensions: ");
    scanf("%d", &n);
    printf("Please, add matrix values: ");

    int **A = malloc(n * sizeof(int*));
    int **L = malloc(n * sizeof(int*));
    int **U = malloc(n * sizeof(int*));

    for (i = 0; i < n; i++)
    {
        A[i] = malloc(n * sizeof(int));
        L[i] = malloc(n * sizeof(int*));
        U[i] = malloc(n * sizeof(int*));
    }
    
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    LU_factorization(A, L, U, n);
    print_matrices(A, L, U, n);

    for (i = 0; i < n; i++)
    {
        free(A[i]);
        free(L[i]);
        free(U[i]);
    }

    free(A);
    free(L);
    free(U);
    return (0);
}
