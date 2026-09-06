#include <iostream>
#include "Vector.h"

int main()
{
   const size_t size = 5;
   double arr[size] = { 4, 3, 2, 4.5, 8 };
   Vector vector(arr, size);

   vector.Print_Vectors();

   return 0;
}