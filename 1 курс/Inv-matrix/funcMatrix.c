#include <stdio.h>
#include <math.h>
#include "funcMatrix.h"

// Функция для нахождения определителя матрицы
float The_determinant(float matrix[][100], int n) {
   float det = 0;
   float minor[100][100];

   if (n == 2) {
      return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
   }
   for (int x = 0; x < n; x++) {
      int flagi = 0;
      for (int i = 1; i < n; i++) {
         int flagj = 0;
         for (int j = 0; j < n; j++) {
            if (j == x)
               continue;
            minor[flagi][flagj] = matrix[i][j];
            flagj++;
         }
         flagi++;
      }
      det = det + (x % 2 == 0 ? 1 : -1) * matrix[0][x] * The_determinant(minor, n - 1);
   }
   return det;
}

// Функция для нахождения обратной матрицы
void inverse(float matrix[][100], int n) {
   float det = The_determinant(matrix, n);

   if (det == 0) {
      printf("Not matrix.\n");
      return;
   }

   float adjoint[100][100];

   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         int subi = 0;
         for (int p = 0; p < n; p++) {
            if (p == i)
               continue;
            int subj = 0;
            for (int q = 0; q < n; q++) {
               if (q == j)
                  continue;
               adjoint[subi][subj] = matrix[p][q];
               subj++;
            }
            subi++;
         }

         float cofactor = pow(-1, i + j);
         matrix[j][i] = (cofactor) * (The_determinant(adjoint, n - 1) / det);
      }
   }
}
