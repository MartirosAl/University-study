#pragma once
#include <iostream>
#include <math.h>
using namespace std;
#include "Exñeption.h"

class Matrix
{
protected:
   int row;
   int column;

   double** matrix;

public:

   Matrix(int row_ = 2, int column_ = 3);

   Matrix(const Matrix& other_);

   virtual ~Matrix();

   Matrix operator+(const Matrix& other_) const;

   Matrix& operator+=(const Matrix& other_);

   Matrix operator-(const Matrix& other_) const;

   Matrix& operator-=(const Matrix& other_);

   Matrix operator*(const Matrix& other_) const;

   Matrix& operator*=(const Matrix& other_);

   Matrix operator*(const double& number_) const;

   Matrix& operator*=(const double& number_);

   Matrix& operator=(const Matrix& other_);

   Matrix& operator^(int n_);

   Matrix& operator/(const Matrix& other_) const;

   Matrix& operator/=(const Matrix& other_);

   Matrix& operator/(const double& number_) const;

   Matrix& operator/=(const double& number_) const;

   bool operator==(const Matrix& other_) const;

   bool operator!=(const Matrix& other_) const;

   double* operator[](int index) const;

   double* operator[](int index);

   friend ostream& operator<<(ostream& stream, const Matrix& matrix);

   friend istream& operator>>(istream& stream, Matrix& matrix);

   void Set_Element(int row_, int column_, double value_);
   
   double Get_Element(int row_, int column_) const;

   int Get_Column() const;

   int Get_Row() const;

   Matrix& Input_from_Console();

   Matrix& Print();

   virtual Matrix& Transposition();

   Matrix Inverse_Matrix();

   virtual double Determinant_Matrix();

   virtual double Minor_Matrix(int i, int j);

   double Algebraic_Complement_Matrix();

   Matrix Pow(int n_);

   //friend Matrix* Add_Array_Matrix(Matrix*& array_matrix_, size_t& size_, size_t capasity_, Matrix& matrix_);

   

};

