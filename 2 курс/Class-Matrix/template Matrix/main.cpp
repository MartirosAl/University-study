#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Matrix.h"
using namespace std; 

template <typename T>
double Min(Matrix<T> matrix_)
{
   double min = matrix_[0][0];

   int row = matrix_.Get_Row();
   int column = matrix_.Get_Column();
   for (int i = 1; i < row; i++)
      for (int j = 0; j < column; j++)
         if (min > matrix_[i][j]) min = matrix_[i][j];

   return min;
}

template <typename T>
Matrix<T>* Add_Array_Matrix(Matrix<T>*& array_matrix_, size_t& size_, Matrix<T>& matrix_)
{
   Matrix<T>* temp = new Matrix<T>[size_];
   for (int i = 0; i < size_; i++)
      temp[i] = array_matrix_[i];

   delete[] array_matrix_;

   
   array_matrix_ = new Matrix<T>[size_ + 1];
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
   cout << ">> ";
}


int main()
{
   Matrix<double>* array_matrix = new Matrix<double>[1];
   size_t size_array_matrix = 0;
   char sign4 = '\0';
   char sign5 = '\0';

   Matrix<double> temp3;

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
            int index2;
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

            cout << "Enter matrix: " << endl;
            cin >> temp3;
            Add_Array_Matrix(array_matrix, size_array_matrix , temp3);

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

         default:
            continue;
         }
      }
      catch (MatrixExñeption& exception)
      {
         exception.Print();
         system("pause");
      }
   }
   return 0;
}