#include <stdio.h>
#include <stdlib.h>

void LU_factorization(double **A, double **L, double **U, int n)
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

void print_matrices(double **A, double **L, double **U, int n)
{
    int i, j;

    printf("Matrix A:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%6f\t", A[i][j]);
        printf("\n");
    }

    printf("Matrix L:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%6f\t", L[i][j]);
        printf("\n");
    }

    printf("Matrix U:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%6f\t", U[i][j]);
        printf("\n");
    }
}

int main(void)
{
    int n = 1000;
    int i, j;
    FILE *file;

    double **A = malloc(n * sizeof(double*));
    double **L = malloc(n * sizeof(double*));
    double **U = malloc(n * sizeof(double*));

    for (i = 0; i < n; i++)
    {
        A[i] = malloc(n * sizeof(double));
        L[i] = malloc(n * sizeof(double*));
        U[i] = malloc(n * sizeof(double*));
    }
    
    file = fopen("matrix_values", "r");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fread(&A[i][j], sizeof(double), 1, file);

    LU_factorization(A, L, U, n);
    //print_matrices(A, L, U, n);

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
