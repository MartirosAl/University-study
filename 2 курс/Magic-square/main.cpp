#include <iostream>
#include "Functions.h"
using namespace std;

int main()
{
   const char* namefile = "test.txt";

   int size;
   int** matrix = nullptr;
   if (Create_Matrix_f(namefile, size, matrix))
      return 1;

   if (Is_magic_square(matrix, size))
      cout << "This is magic square" << endl;
   else
      cout << "This is not magic square" << endl;

   Print_Matrix(matrix, size);

   cout << The_same_numbers(matrix, size) << endl;

   return 0;
}