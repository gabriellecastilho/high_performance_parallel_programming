#include <stdio.h>
#include <stdlib.h>

void LU_fact(int **A, int **L, int **U, int n)
{
    int sum;
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            sum = 0;
            for (k = 0; k < i; k++)
                sum += (L[i][k] * U[k][j]);
            U[i][j] = A[i][j] - sum;
        }
        
        for (j = i; j < n; j++)
        {
            if (i == j)
                L[i][i] = 1;
            else
            {
                sum = 0;
                for (k = 0; k < i; k++)
                    sum += (L[j][k] * U[k][i]);
                L[j][i] = (A[j][i] - sum) / U[i][i];
            }
        }
    }
}

void LU_print(int **A, int **L, int **U, int n)
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
    {
        for (j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    }

    LU_fact(A, L, U, n);
    LU_print(A, L, U, n);

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
