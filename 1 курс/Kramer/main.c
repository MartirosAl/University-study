#include <stdio.h>
#include "funcMatrix.h"
#define MAX_SIZE 10

int main() {
   int n;

   printf("Enter the dimension: ");
   scanf_s("%d", &n);

   if (n <= 0 || n > MAX_SIZE) {
      printf("Incorrect dimension.\n");
      return 0;
   }

   solveSystem(n);

   return 0;
}