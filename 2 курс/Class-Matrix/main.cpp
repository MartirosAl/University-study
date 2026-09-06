#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <math.h>
#include "Matrix.h"
#include "Square_Matrix.h"
#include "Vector.h"
using namespace std; 

double Min(Matrix matrix_)
{
   double min = matrix_[0][0];

   int row = matrix_.Get_Row();
   int column = matrix_.Get_Column();
   for (int i = 1; i < row; i++)
      for (int j = 0; j < column; j++)
         if (min > matrix_[i][j]) min = matrix_[i][j];

   return min;
}

Vector Max_from_Diagonals(Square_Matrix& matrix_)
{
   int size = matrix_.Get_Row() * 2 - 1;
   Vector array(nullptr, (size_t)size);

   int index = 0;

   for (int i = matrix_.Get_Row() - 1; i >= 0; i--)
   {
      double diagonal1 = 0;
      double diagonal2 = 0;
      int temp = i;
      
      for (int j = 0; j < matrix_.Get_Row() - i; j++)
      {
         if (diagonal1 < matrix_[temp][j]) diagonal1 = matrix_[temp][j];
         if (diagonal2 < matrix_[j][temp]) diagonal2 = matrix_[j][temp];

         temp++;
      }
      
      array[index] = diagonal1;
      if (i != 0)
         array[size - 1 - index] = diagonal2;
      index++;
   }


   return array;
}

Matrix Smoothing(Matrix& matrix_)
{
   Matrix result(matrix_);
   for (int i = 0; i < matrix_.Get_Row(); i++)
   {
      double temp1 = 0;
      int tempn = 0;
      for (int j = 0; j < matrix_.Get_Row(); j++)
      {

         for (int di = -1; di <= 1; di++)
            for (int dj = -1; dj <= -1; dj++)
            {
               if (di == dj && dj == 0) continue;

               if (i + di >= 0 && i + di < matrix_.Get_Row() && j + dj >= 0 && j + dj < matrix_.Get_Row())
               {
                  temp1 += matrix_[i + di][j + dj];
                  tempn++;
               }
            }
         
         result[i][j] = temp1/tempn;
      }
   }

   return result;
}

Matrix* Add_Array_Matrix(Matrix*& array_matrix_, size_t& size_, Matrix& matrix_)
{
   Matrix* temp = new Matrix[size_];
   for (int i = 0; i < size_; i++)
      temp[i] = array_matrix_[i];

   delete[] array_matrix_;

   
   array_matrix_ = new Matrix[size_ + 1];
   for (size_t i = 0; i < size_; i++)
      array_matrix_[i] = temp[i];

   array_matrix_[size_] = matrix_;

   size_++;
   return array_matrix_;
}

Matrix* Add_Array_Matrix(Matrix*& array_matrix_, size_t& size_, Square_Matrix& matrix_)
{
   Matrix* temp = new Matrix[size_];
   for (int i = 0; i < size_; i++)
      temp[i] = array_matrix_[i];

   delete[] array_matrix_;

   array_matrix_ = new Matrix[size_ + 1];
   for (size_t i = 0; i < size_; i++)
      array_matrix_[i] = temp[i];

   array_matrix_[size_] = matrix_;

   size_++;
   return array_matrix_;
}

void menu()
{
   cout << "1. Print matrix" << endl;
   cout << "2. Edit elements" << endl;
   cout << "3. Create new matrix" << endl;
   cout << "4. Arithmetic operations" << endl;
   cout << "5. Comparison operations" << endl;
   cout << "6. Transponitoin matrix" << endl;
   cout << "7. Exponentiation matrix" << endl;
   cout << "8. Inverse matrix" << endl;
   cout << "9. Determinant matrix" << endl;
   cout << ">> ";
}

int main()
{
   Matrix* array_matrix = new Matrix[1];
   Square_Matrix temp;
   size_t size_array_matrix = 0;
   char sign4 = '\0';
   char sign5 = '\0';

   unsigned short int choice;
   while (1)
   {
      try
      {
         system("cls");
         menu();

         cin >> choice;

         system("cls");
         switch (choice)
         {
         case 1:
            for (size_t i = 0; i < size_array_matrix; i++)
               cout << '#' << i << endl << array_matrix[i];
            cout << "Done" << endl;  
            system("pause");
            continue;
         case 2:
            for (size_t i = 0; i < size_array_matrix; i++)
               cout << '#' << i << endl << array_matrix[i];
            unsigned short int index2;
            cout << "Enter number matrix: ";
            cin >> index2;
            array_matrix[index2 - 1].Input_from_Console();
            cout << "Done" << endl;
            system("pause");
            continue;
         case 3:
            int row3, column3;
            cout << "Enter row and column: ";
            cin >> row3 >> column3;
            if (row3 == column3)
            {
               Square_Matrix s_temp3(row3);
               cout << "Enter matrix: " << endl;
               cin >> s_temp3;
               Add_Array_Matrix(array_matrix, size_array_matrix, s_temp3);
            }
            else
            {
               Matrix temp3(row3, column3);
               cout << "Enter matrix: " << endl;
               cin >> temp3;
               Add_Array_Matrix(array_matrix, size_array_matrix , temp3);
            }
            cout << "Done" << endl;
            system("pause");
            continue;
         case 4:
            size_t index4_1;
            size_t index4_2;
            size_t index4_3;

            while (1)
            {
               cout << "Choose arithmetic operation (+, -, *)" << endl;
               cin >> sign4;
               if (sign4 == '+' || sign4 == '-' || sign4 == '*')
                  break;
               cout << "wrong operation" << endl;
               system("pause");
               system("cls");
            }
            system("cls");            
            for (size_t i = 0; i < size_array_matrix; i++)
               cout << '#' << i << endl << array_matrix[i];
            cout << "? " << sign4 << " ? = ?" << endl;
            cout << "Choose first matrix" << endl;
            while (1) 
            {
               cin >> index4_1;
               if (index4_1 < 0 || index4_1 >= size_array_matrix)
               {
                  cout << "wrong index" << endl;

               }
               else
                  break;
            }
            system("cls");
            for (size_t i = 0; i < size_array_matrix; i++)
               cout << '#' << i << endl << array_matrix[i];
            cout << "#" << index4_1 << ' ' << sign4 << " ? = ?" << endl;
            cout << "Choose second matrix" << endl;
            while (1) {
               cin >> index4_2;
               if (index4_2 < 0 || index4_2 >= size_array_matrix)
               {
                  cout << "wrong index" << endl;

               }
               else
                  break;
            }
            system("cls");
            for (size_t i = 0; i < size_array_matrix; i++)
               cout << '#' << i << endl << array_matrix[i];
            cout << "#" << index4_1 << ' ' << sign4 << " #" << index4_2 << " = ? " << endl;
            cout << "Choose third matrix" << endl;
            while (1) 
            {
               cin >> index4_3;
               if (index4_3 < 0 || index4_3 >= size_array_matrix)
               {
                  cout << "wrong index" << endl;

               }
               else
                  break;
            }
            system("cls");
            
            if (index4_1 == index4_3 || index4_2 == index4_3)
            {
               switch (sign4)
               {
               case '+':
                  cout << (array_matrix[index4_1 == index4_3 ? index4_1 : index4_2] += array_matrix[index4_1 != index4_3 ? index4_1 : index4_2]);
                  break;
               case '-':
                  cout << (array_matrix[index4_1 == index4_3 ? index4_1 : index4_2] -= array_matrix[index4_1 != index4_3 ? index4_1 : index4_2]);
                  break;
               case '*':
                  cout << (array_matrix[index4_1 == index4_3 ? index4_1 : index4_2] *= array_matrix[index4_1 != index4_3 ? index4_1 : index4_2]);
                  break;
               }
            }
            else
            {
               switch (sign4)
               {
               case '+':
                  cout << (array_matrix[index4_3] = array_matrix[index4_1] + array_matrix[index4_2]);
                  break;
               case '-':
                  cout << (array_matrix[index4_3] = array_matrix[index4_1] - array_matrix[index4_2]);
                  break;
               case '*':
                  cout << (array_matrix[index4_3] = array_matrix[index4_1] * array_matrix[index4_2]);
                  break;
               }
            }
            cout << "Done" << endl;
            system("pause");
            continue;
         case 5:
            size_t index5_1;
            size_t index5_2;

            while (1)
            {
               cout << "Choose comparation operation (=, !=)" << endl;
               cin >> sign5;
               if (sign5 == '!')
                  cin.ignore();
               if (sign5 == '!' || sign5 == '=')
                  break;
               cout << "wrong operation" << endl;
               system("pause");
               system("cls");
            }
            system("cls");
            for (size_t i = 0; i < size_array_matrix; i++)
               cout << '#' << i << endl << array_matrix[i];
            cout << "? " << ((sign5 == '!')? "!=" : "=") << " ?" << endl;
            cout << "Choose first matrix" << endl;
            while (1) {
               cin >> index5_1;
               if (index5_1 < 0 || index5_1 >= size_array_matrix)
               {
                  cout << "wrong index" << endl;
               }
               else
                  break;
            }
            system("cls");
            for (size_t i = 0; i < size_array_matrix; i++)
               cout << '#' << i << endl << array_matrix[i];
            cout << "#" << index5_1 << ' ' << ((sign5 == '!') ? "!=" : "=") << " ?" << endl;
            cout << "Choose second matrix" << endl;
            while (1) {
               cin >> index5_2;
               if (index5_2 < 0 || index5_2 >= size_array_matrix)
               {
                  cout << "wrong index" << endl;
               }
               else
                  break;
            }
            system("cls");

            switch (sign5)
            {
            case '=':
               cout << ((array_matrix[index5_1] == array_matrix[index5_2]) ? "True" : "False") << endl;
               break;
            default:
               cout << ((array_matrix[index5_1] != array_matrix[index5_2]) ? "True" : "False") << endl;
            }
            system("pause");
            system("cls");
            continue;

         case 6:
            int index6;
            for (size_t i = 0; i < size_array_matrix; i++)
               cout << '#' << i << endl << array_matrix[i];
            cout << "Choose matrix for transponition" << endl;
            while (1) {
               cin >> index6;
               if (index6 < 0 || index6 >= size_array_matrix)
               {
                  cout << "wrong index" << endl;
               }
               else
                  break;
            }
            array_matrix[index6].Transposition();
            cout << "Done" << endl;
            cout << array_matrix[index6] << endl;
            system("pause");
            system("cls");
            continue;

         case 7:
            int index7;
            int degree7;
            for (size_t i = 0; i < size_array_matrix; i++)
               cout << '#' << i << endl << array_matrix[i];
            cout << "Choose matrix for exp" << endl;
            cin >> index7;
            cout << "Choose degree" << endl;
            cin >> degree7;

            temp = array_matrix[index7];
            temp = temp.Pow(degree7);
            array_matrix[index7] = temp;

            cout << temp << endl;
            cout << "Done" << endl;
            system("pause");
            system("cls");
            continue;

         case 8:
            int index8;
            for (size_t i = 0; i < size_array_matrix; i++)
               cout << '#' << i << endl << array_matrix[i];
            cout << "Choose matrix for inverse" << endl;
            cin >> index8;

            temp = array_matrix[index8];
            temp = temp.Inverse_Matrix();
            array_matrix[index8] = temp;

            cout << "Done" << endl;
            cout << array_matrix[index8] << endl;
            system("pause");
            system("cls");
            continue;

         case 9:
            int index9;
            for (size_t i = 0; i < size_array_matrix; i++)
               cout << '#' << i << endl << array_matrix[i];
            cout << "Choose matrix for determinante" << endl;
            cin >> index9;
            temp = array_matrix[index9];
            cout << temp.Determinant_Matrix() << endl;
            system("pause");
            system("cls");
            continue;
         default:
            continue;
         }
      }
      catch (MatrixExсeption& exception)
      {
         exception.Print();
         system("pause");
      }
      catch (int error)
      {
         //throw:
         //1 - Выход за пределы
         //2 - Не одинаковый размер матрицы
         //3 - Колонки не совпадают со строками другой матрицы или наоборот
         //4 - Неправильно введенные данные
         //5 - Неквадратная матрица
         switch (error)
         {
         case 1:
            cout << "Out of order" << endl;
            break;
         case 2:
            cout << "Sizes matrixes are not same" << endl;
            break;
         case 3:
            cout << "Wrong rows and columns in this matrix" << endl;
            break;
         case 4:
            cout << "Wrong enter data" << endl;
            break;
         case 5:
            cout << "Not square matrix" << endl;
            break;
         default:
            cout << "Unknown error" << endl;
            return 1;
         }
         system("pause");
      }
   }
   return 0;
}