#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void main(int argc, char *argv[])
{
    int nb_task, rank;
    int i, j, k, m, n;
    float **a, l, r, t, b;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_task);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Donner le nombre des lignes de la matrice A\n");
        scanf("%d", &m);
        printf("Donner le nombre des colonnes de la matrice A\n");
        scanf("%d", &n);
        printf("Enter boundary conditions:les valeures de la température sur les bords \n");
        printf("Value on left side: \n");
        scanf("%f", &l);
        printf("Value on right side: \n");
        scanf("%f", &r);
        printf("Value on top side: \n");
        scanf("%f", &t);
        printf("Value on bottom side: \n");
        scanf("%f", &b);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(&l, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&r, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&t, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    a = (float **)malloc(m * sizeof(float *));

    for (i = 0; i < m; i++)
        a[i] = (float *)malloc(n * sizeof(float));

    for (i = 0; i < m; i++)
    {
        a[i][0] = b;
        a[i][n - 1] = t;
    }

    for (i = 0; i < n; i++)
    {
        a[0][i] = l;
        a[m - 1][i] = r;
    }

    for (i = 1; i < m - 1; i++)
        for (j = 1; j < n - 1; j++)
            a[i][j] = t;
   

    MPI_Barrier(MPI_COMM_WORLD);

    for (k = 0; k < 1000; k++)
    {
        for (i = 1; i < m - 1; i++)
        {
            for (j = 1; j < n - 1; j++)
            {a[i][j] = (a[i-1][j] + a[i+1][j] + a[i][j-1] + a[i][j+1])/4;}
        }
    }

    if (rank == 0)
    {
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                printf("%f| ", a[i][j]);
            }
            printf("\n");
        }

        
    }

    for (i = 0; i < m; i++)
            free(a[i]);
        free(a);
    MPI_Finalize();
}