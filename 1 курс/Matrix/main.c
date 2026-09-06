#include <stdio.h>
#include "function.h"

int main()
{
   long int matrix[250][250];
   long int Tmatrix[250][250];

   //Размер матрицы
   int n;  //Длина
   int m;  //Ширина

   printf("Enter length: ");
   scanf_s("%d", &n);
   printf("Enter width: ");
   scanf_s("%d", &m);

   //Ввод значений в матрицу
   for (int i = 0; i < n; ++i)
   {
      for (int j = 0; j < n; ++j)
      {
         scanf_s("%ld", &matrix[i][j]);
         printf("%ld ", matrix[i][j]);
         printf("%d ", i);
         printf("%d \n", n);
      }
      
   }

   //Вывод матрицы
   for (int i = 0; i < n; ++i)
   {
      printf("\n");
      for (int j = 0; j < m; ++j)
      {
         printf(" %ld ", matrix[i][j]);
      }
   }


   //Транспонируем матрицу
   Transp(&Tmatrix, &matrix, n, m);
   //for (int i = 0; i < n; ++i)
   //{
   //   for (int j = 0; j < m; ++j)
   //   {
   //      Tmatrix[j][i] = matrix[i][j];
   //   }
   //}

   for (int i = 0; i < n; ++i)
   {
      printf("\n");
      for (int j = 0; j < m; ++j)
      {
         printf(" %ld ", Tmatrix[i][j]);
      }
   }
}