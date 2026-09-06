#pragma once
#include "Matrix.h"
class Square_Matrix : public Matrix
{
public:
   Square_Matrix(int order_ = 2);

   Square_Matrix(const Square_Matrix& other_);

   Square_Matrix operator+(const Square_Matrix& other_) const;

   Square_Matrix& operator+=(const Square_Matrix& other_);

   Square_Matrix operator-(const Square_Matrix& other_) const;

   Square_Matrix& operator-=(const Square_Matrix& other_);

   Square_Matrix& operator=(const Square_Matrix& other_);

   Square_Matrix& operator=(const Matrix& other_);

   Square_Matrix operator*(const Square_Matrix& other_) const;

   Square_Matrix& operator*=(const Square_Matrix& other_);

   Square_Matrix operator*(const double& number_) const;

   Square_Matrix& operator*=(const double& number_);

   Square_Matrix operator^(int n_);

   bool operator==(const Square_Matrix& other_) const;

   bool operator!=(const Square_Matrix& other_) const;

   double* operator[](int index) const;

   double* operator[](int index);

   friend ostream& operator<<(ostream& stream, const Square_Matrix& matrix);

   friend istream& operator>>(istream& stream, Square_Matrix& matrix);

   Matrix Inverse_Matrix();

   double Determinant_Matrix();

   double Minor_Matrix(int i, int j);

   double Algebraic_Complement_Matrix();

   Matrix Pow(int n_);

   Square_Matrix& Transposition();

   //friend Matrix* Add_Array_Matrix(Matrix*& array_matrix_, size_t& size_, size_t& capasity_, Square_Matrix& matrix_);
};

