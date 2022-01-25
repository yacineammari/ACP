#include <mpi.h>
#include <stdio.h>
#define size 6

int main(int argc, char *argv[])
{
    int nb_task, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_task);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int a[size][size], b[size][size], c[size][size];
    int bls = size / nb_task;
    int rcv[bls][size];
    int i, j, k;
    int cpt = 0;
    if (rank == 0)
    {
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                a[i][j] = j + cpt;
                b[i][j] = j;
            }
            cpt++;
        }

        
    }

    MPI_Bcast(&b, size * size, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(a + (rank * size * bls), bls * size, MPI_INT, &rcv, bls * size, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    int sum = 0;
    int tempm[bls][size];
    for (i = 0; i < bls; i++)
    {
        for (j = 0; j < size; j++)
        {
            tempm[i][j] = 0;
        }
    }

    for (int i = 0; i < bls; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < size; ++k)
            {
                tempm[i][j] += rcv[i][k] * b[k][j];
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(tempm, bls * size, MPI_INT, c, bls * size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Matrice A: \n");

        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                printf("%d| ", a[i][j]);
            }
            printf("\n");
        }
        printf("Matrice B: \n");

        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                printf("%d| ", b[i][j]);
            }
            printf("\n");
        }
        printf("Matrice C: \n");

        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                printf("%d| ", c[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
}
