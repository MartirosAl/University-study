#include <stdio.h>
#include "funcMatrix.h"
#define MAX_SIZE 10

void solveSystem(int n) {
   double A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE], X[MAX_SIZE];
   double detA, detX[MAX_SIZE];

   // Ввод системы уравнений
   printf("Enter the coefficients of the system of equations:\n");
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         printf("A[%d][%d] = ", i, j);
         scanf_s("%lf", &A[i][j]);
      }
      printf("B[%d] = ", i);
      scanf_s("%lf", &B[i]);
   }

   // Вычисление определителя матрицы A
   detA = The_determinant(A, n);

   // Проверка на невырожденность системы
   if (detA == 0) {
      printf("The system of equations is degenerate.\n");
      return;
   }

   // Решение системы методом Крамера
   for (int k = 0; k < n; k++) {
      // Создание временной матрицы для вычисления определителя
      double tempA[MAX_SIZE][MAX_SIZE];
      for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) {
            tempA[i][j] = A[i][j];
         }
         tempA[i][k] = B[i];
      }

      // Вычисление определителя матрицы tempA
      detX[k] = The_determinant(tempA, n);
      X[k] = detX[k] / detA;
   }

   // Вывод решений
   printf("Solving a system of equations:\n");
   for (int i = 0; i < n; i++) {
      printf("X[%d] = %lf\n", i, X[i]);
   }
}

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
