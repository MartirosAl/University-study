#include <stdio.h>
#include <math.h>
#include "funcMatrix.h"

int main() {
   int n;
   float matrix[100][100];

   printf("(n): ");
   scanf_s("%d", &n);

   printf("Enter matrix:\n");
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         scanf_s("%f", &matrix[i][j]);
      }
   }

   inverse(matrix, n);

   printf("Inv matrix:\n");
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         printf("%.4f\t", matrix[i][j]);
      }
      printf("\n");
   }

   return 0;
}