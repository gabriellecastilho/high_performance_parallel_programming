#include <stdio.h>
#include <stdlib.h>

void LU_fact(int **matrix, int n)
{
    int **L = malloc(n * sizeof(int*));
    int **U = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++)
    {
        L[i] = malloc(n * sizeof(int*));
        U[i] = malloc(n * sizeof(int*));
    }

    for (int i = 0; i < n; i++)
    {
        for (int k = i; k < n; k++)
        {
            int sum = 0;
            for (int j = 0; j < i; j++)
                sum += (L[i][j] * U[j][k]);
            U[i][k] = matrix[i][k] - sum;
        }
        
        for (int k = i; k < n; k++)
        {
            if (i == k)
                L[i][i] = 1;
            else
            {
                int sum = 0;
                for (int j = 0; j < i; j++)
                    sum += (L[k][j] * U[j][i]);
                L[k][i] = (matrix[k][i] - sum) / U[i][i];
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%6d\t", L[i][j]);
        printf("\t");

        for (int j = 0; j < n; j++)
            printf("%6d\t", U[i][j]);
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        free(L[i]);
        free(U[i]);
    }
    free(L);
    free(U);
}

int main(void)
{
    int n;
    printf("Please, add the number n of dimensions: ");
    scanf("%d", &n);
    printf("Matrix %d x %d\n", n, n);

    int **matrix = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);
    }

    LU_fact(matrix, n);

    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);

    return 0;
}
