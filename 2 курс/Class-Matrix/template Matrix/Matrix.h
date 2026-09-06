#pragma once
#include <iostream>
#include "Exñeption.h"
#include <math.h>
#include "Vector.h"
using namespace std;

template<typename T>
class Matrix
{
protected:
   int row;
   int column;

   T** matrix;

public:


   Matrix(int row_ = 2, int column_ = 3)
   {
      row = row_;
      column = column_;

      matrix = new double* [row];
      for (int i = 0; i < row; i++)
         matrix[i] = new double[column];
      for (int i = 0; i < row; i++)
         for (int j = 0; j < column; j++)
            matrix[i][j] = 0;
   }

   Matrix(const Matrix<T>& other_)
   {
      row = other_.row;
      column = other_.column;

      matrix = new double* [row];
      for (int i = 0; i < row; i++)
         matrix[i] = new double[column];
      for (int i = 0; i < row; i++)
         for (int j = 0; j < column; j++)
            matrix[i][j] = other_[i][j];
   }

   virtual ~Matrix()
   {
      for (int i = 0; i < row; i++)
         delete[] matrix[i];
      delete[] matrix;
   }


   Matrix<T> operator+(const Matrix<T>& other_) const
   {
      if (row != other_.row || column != other_.column)
         throw SizeAreNotSame();

      Matrix<T> result(row, column);
      for (int i = 0; i < row; i++)
         for (int j = 0; j < column; j++)
            result[i][j] = matrix[i][j] + other_[i][j];

      return result;

   }

   Matrix<T>& operator+=(const Matrix<T>& other_)
   {
      if (row != other_.row || column != other_.column)
         throw SizeAreNotSame();

      for (int i = 0; i < row; i++)
         for (int j = 0; j < column; j++)
            matrix[i][j] += other_[i][j];

      return *this;
   }

   Matrix<T> operator-(const Matrix<T>& other_) const
   {
      if (row != other_.row || column != other_.column)
         throw SizeAreNotSame();

      Matrix<T> result(row, column);
      for (int i = 0; i < row; i++)
         for (int j = 0; j < column; j++)
            result[i][j] = matrix[i][j] - other_[i][j];

      return result;
   }

   Matrix<T>& operator-=(const Matrix<T>& other_)
   {
      if (row != other_.row || column != other_.column)
         throw SizeAreNotSame();

      for (int i = 0; i < row; i++)
         for (int j = 0; j < column; j++)
            matrix[i][j] -= other_[i][j];

      return *this;
   }

   Matrix<T> operator*(const Matrix<T>& other_) const
   {
      if (row != other_.column || column != other_.row)
         throw WrongRowsColumns();

      Matrix<T> result(row, other_.column);

      for (int i = 0; i < result.row; i++)
         for (int j = 0; j < result.column; j++)
            for (int k = 0; k < column; k++)
               result[i][j] += matrix[i][k] * other_[k][j];

      return result;
   }

   Matrix<T>& operator*=(const Matrix<T>& other_)
   {
      if (row != other_.column || column != other_.row)
         throw WrongRowsColumns();

      Matrix<T> result(row, other_.column);

      for (int i = 0; i < result.row; i++)
         for (int j = 0; j < result.column; j++)
            for (int k = 0; k < column; k++)
               result[i][j] += matrix[i][k] * other_[k][j];

      (*this) = result;

      return *this;
   }

   Matrix<T> operator*(const T& number_) const
   {
      Matrix<T> temp(*this);

      for (int i = 0; i < row; i++)
         for (int j = 0; j < column; j++)
            temp[i][j] = number_ * temp[i][j];

      return temp;
   }

   Matrix<T>& operator*=(const T& number_)
   {
      for (int i = 0; i < row; i++)
         for (int j = 0; j < column; j++)
            matrix[i][j] = number_ * matrix[i][j];

      return *this;
   }

   Matrix<T>& operator=(const Matrix<T>& other_)
   {
      if (this == &other_)
         return *this;

      if (row != other_.row || column != other_.column)
      {
         delete[] matrix;
         row = other_.row;
         column = other_.column;
         matrix = new T * [row];
         for (int i = 0; i < row; i++)
            matrix[i] = new T[column];
      }

      for (int i = 0; i < row; i++)
         for (int j = 0; j < column; j++)
            matrix[i][j] = other_[i][j];

      return *this;
   }

   Matrix<T>& operator^(int n_)
   {
      throw WrongNotSquare();
   }

   bool operator==(const Matrix<T>& other_) const
   {
      return ((row == other_.row) && (column == other_.column));
   }

   bool operator!=(const Matrix<T>& other_) const
   {
      return ((row != other_.row) && (column != other_.column));
   }

   T* operator[](int index) const
   {
      return matrix[index];
   }

   T* operator[](int index)
   {
      return matrix[index];
   }

   friend ostream& operator<<(ostream& stream, const Matrix<T>& matrix)
   {
      for (int i = 0; i < matrix.row; i++)
      {
         for (int j = 0; j < matrix.column; j++)
            stream << matrix[i][j] << ' ';
         stream << endl;
      }
      stream << endl;
      return stream;
   }

   friend istream& operator>>(istream& stream, Matrix<T>& matrix)
   {
      for (int i = 0; i < matrix.row; i++)
      {
         for (int j = 0; j < matrix.column; j++)
            stream >> matrix[i][j];
      }
      return stream;
   }

   void Set_Element(int row_, int column_, T value_)
   {
      if ((row_ < 0 || row_ >= row) || (column_ < 0 || column_ >= column))
         throw OutOfRange();
      matrix[row_][column_] = value_;
   }
   
   T Get_Element(int row_, int column_) const
   {
      if ((row_ < 0 || row_ >= row) || (column_ < 0 || column_ >= column))
         throw OutOfRange();
      return matrix[row_][column_];
   }

   int Get_Row() const
   {
      return row;
   }

   int Get_Column() const
   {
      return column;
   }

   Matrix<T>& Input_from_Console()
   {
      for (int i = 0; i < row; i++)
         for (int j = 0; j < column; j++)
            if (!scanf_s("%lf", &matrix[i][j])) throw WrongData();

      return *this;
   }

   Matrix<T>& Print()
   {
      for (int i = 0; i < row; i++)
      {
         for (int j = 0; j < column; j++)
            printf("%lf ", matrix[i][j]);
         printf("\n");
      }
      std::cout << '\n';

      return *this;
   }

   virtual Matrix<T>& Transposition()
   {
      Matrix<T> temp(*this);

      delete[] matrix;
      row = temp.column;
      column = temp.row;

      matrix = new double* [row];
      for (int i = 0; i < row; i++)
         matrix[i] = new double[column];
      for (int i = 0; i < row; i++)
         for (int j = 0; j < column; j++)
            matrix[i][j] = temp[j][i];

      return *this;
   }

   virtual Matrix<T> Inverse_Matrix()
   {
      throw WrongNotSquare();
   }

   virtual T Determinant_Matrix()
   {
      throw WrongNotSquare();
   }

   virtual Matrix<T> Pow(int n_)
   {
      throw WrongNotSquare();
   }

   virtual Matrix<T> Algebraic_Addition()
   {
      throw WrongNotSquare();
   }

   T Minor_Matrix(int i, int j)
   {
      throw WrongNotSquare();
   }

   //friend Matrix* Add_Array_Matrix(Matrix*& array_matrix_, size_t& size_, size_t capasity_, Matrix& matrix_);

   

};



