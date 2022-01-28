#include <stdio.h>
#include <stdlib.h>
int i, j, k, m, n;
float **a, l, r, t, b;
void main(int argc, char *argv[])
{

   printf("Donner le nombre des lignes de la matrice A\n");
   scanf("%d", &m);
   printf("Donner le nombre des colonnes de la matrice A\n");
   scanf("%d", &n);

   a = (float **)malloc(m * sizeof(float *));

   for (i = 0; i < m; i++)
      a[i] = (float *)malloc(n * sizeof(float));

   printf("\tEnter boundary conditions:les valeures de la température sur les bords \n");
   printf("\tValue on left side: ");
   scanf("%f", &l);
   printf("\tValue on right side: ");
   scanf("%f", &r);
   printf("\tValue on top side: ");
   scanf("%f", &t);
   printf("\tValue on bottom side: ");
   scanf("%f", &b);

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

   for (k = 0; k < 1000; k++)
   {
      for (i = 1; i < m - 1; i++)
      {
         for (j = 1; j < n - 1; j++)
         {
            a[i][j] = (a[i - 1][j] + a[i + 1][j] + a[i][j - 1] + a[i][j + 1]) / 4;
         }
      }
   }

   for (i = 0; i < m; i++)
   {
      for (j = 0; j < n; j++)
      {
         printf("%f| ", a[i][j]);
      }
      printf("\n");
   }

   for (i = 0; i < m; i++)
      free(a[i]);
   free(a);
}
