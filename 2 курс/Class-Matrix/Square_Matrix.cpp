#include "Square_Matrix.h"

Square_Matrix::Square_Matrix(int order_) : Matrix(order_, order_) { ; }

Square_Matrix::Square_Matrix(const Square_Matrix& other_) : Matrix(other_) { ; }

Square_Matrix Square_Matrix::operator+(const Square_Matrix& other_) const
{

   if (row != other_.row)
      throw SizeAreNotSame();

   Square_Matrix result(row);
   for (int i = 0; i < row; i++)
      for (int j = 0; j < row; j++)
         result[i][j] = matrix[i][j] + other_[i][j];

   return result;
}

Square_Matrix& Square_Matrix::operator+=(const Square_Matrix& other_)
{
   if (row != other_.row)
      throw SizeAreNotSame();

   for (int i = 0; i < row; i++)
      for (int j = 0; j < row; j++)
         matrix[i][j] += other_[i][j];

   return *this;
}

Square_Matrix Square_Matrix::operator-(const Square_Matrix& other_) const
{
   if (row != other_.row)
      throw SizeAreNotSame();

   Square_Matrix result(row);
   for (int i = 0; i < row; i++)
      for (int j = 0; j < row; j++)
         result[i][j] = matrix[i][j] - other_[i][j];

   return result;
}

Square_Matrix& Square_Matrix::operator-=(const Square_Matrix& other_)
{
   if (row != other_.row)
      throw SizeAreNotSame();

   for (int i = 0; i < row; i++)
      for (int j = 0; j < row; j++)
         matrix[i][j] -= other_[i][j];

   return *this;
}

double* Square_Matrix::operator[](const int index) const
{
   return matrix[index];
}

double* Square_Matrix::operator[](const int index)
{
   return matrix[index];
}

Square_Matrix& Square_Matrix::operator=(const Square_Matrix& other_)
{
   if (this == &other_)
      return *this;

   if (row != other_.row)
   {
      delete[] matrix;
      row = other_.row;
      column = other_.row;
      matrix = new double* [row];
      for (int i = 0; i < row; i++)
         matrix[i] = new double[row];
   }

   for (int i = 0; i < row; i++)
      for (int j = 0; j < row; j++)
         matrix[i][j] = other_[i][j];

   return *this;
}

Square_Matrix& Square_Matrix::operator=(const Matrix& other_)
{
   if (this == &other_)
      return *this;
   if (other_.Get_Row() != other_.Get_Column())
      throw 5;

   if (row != other_.Get_Row() || column != other_.Get_Column())
   {
      delete[] matrix;
      row = other_.Get_Row();
      column = other_.Get_Row();
      matrix = new double* [row];
      for (int i = 0; i < row; i++)
         matrix[i] = new double[column];
   }

   for (int i = 0; i < row; i++)
      for (int j = 0; j < column; j++)
         matrix[i][j] = other_[i][j];

   return *this;
}

Square_Matrix Square_Matrix::operator*(const Square_Matrix& other_) const
{
   if (row != other_.row)
      throw WrongRowsColumns();

   Square_Matrix result(row);

   for (int i = 0; i < row; i++)
      for (int j = 0; j < row; j++)
         for (int k = 0; k < row; k++)
            result[i][j] += matrix[i][k] * other_[k][j];

   return result;
}

Square_Matrix& Square_Matrix::operator*=(const Square_Matrix& other_)
{
   if (row != other_.row)
      throw WrongRowsColumns();

   Square_Matrix result(row);

   for (int i = 0; i < row; i++)
      for (int j = 0; j < row; j++)
         for (int k = 0; k < row; k++)
            result[i][j] += matrix[i][k] * other_[k][j];

   (*this) = result;

   return *this;
}

Square_Matrix Square_Matrix::operator*(const double& number_) const
{
   Square_Matrix temp(*this);

   for (int i = 0; i < row; i++)
      for (int j = 0; j < row; j++)
         temp[i][j] = number_ * temp[i][j];

   return temp;
}

Square_Matrix& Square_Matrix::operator*=(const double& number_)
{
   for (int i = 0; i < row; i++)
      for (int j = 0; j < row; j++)
         matrix[i][j] = number_ * matrix[i][j];

   return *this;
}

Square_Matrix Square_Matrix::operator^(int n_)
{
   if (n_ < 0) throw WrongData();//Заменить на деление

   Square_Matrix temp(row);
   for (int i = 0; i < row; i++)
      temp.matrix[i][i] = 1;

   for (int i = 1; i <= n_; i++)
      temp = temp * (*this);

   return temp;
}

bool Square_Matrix::operator==(const Square_Matrix& other_) const
{
   return (row == other_.row);
}

bool Square_Matrix::operator!=(const Square_Matrix& other_) const
{
   return (row != other_.row);
}

Matrix Square_Matrix::Inverse_Matrix()
{
   Square_Matrix temp((*this).Transposition());

   temp = temp * (1.0 / (*this).Determinant_Matrix());

   return (Matrix)temp;
}

double Square_Matrix::Determinant_Matrix()
{
   double determinant = 0;

   if (row == 1)
      return matrix[0][0];

   Square_Matrix temp_matrix(row - 1);

   for (int i = 0; i < row; i++)
   {
      int vt = 0;
      for (int v = 1; v < row; v++)
      {
         int wt = 0;
         for (int w = (wt == i) ? (1) : (0); w < row; (wt == i) ? (w = w + 2) : (w++))
         {
            temp_matrix[vt][wt] = matrix[v][w];
            wt++;
         }
         vt++;
      }
      determinant += ((i % 2 ? -1 : 1) * matrix[0][i]) * temp_matrix.Determinant_Matrix();
   }


   return determinant;
}

double Square_Matrix::Minor_Matrix(int i, int j)
{

   Square_Matrix temp_matrix(row - 1);

   int vt = 0;
   for (int v = (vt == i) ? (1) : (0); v < row; (vt == i) ? (v = v + 2) : (v++))
   {
      int wt = 0;
      for (int w = (wt == i) ? (1) : (0); w < row; (wt == i) ? (w = w + 2) : (w++))
      {
         temp_matrix[vt][wt] = matrix[v][w];
         wt++;
      }
      vt++;
   }

   return temp_matrix.Determinant_Matrix();
}

Matrix Square_Matrix::Pow(int n_)
{
   if (n_ < 0) throw WrongData();//Заменить на деление

   Square_Matrix temp(row);
   for (int i = 0; i < row; i++)
      temp.matrix[i][i] = 1;

   for (int i = 1; i <= n_; i++)
      temp = temp * (*this);


   return (Matrix)temp;
}

Square_Matrix& Square_Matrix::Transposition()
{
   double temp;

   for (int i = 0; i < row; i++)
      for (int j = 0; j < i; j++)
      {
         temp = matrix[i][j];
         matrix[i][j] = matrix[j][i];
         matrix[j][i] = temp;
      }

   return *this;
}

ostream& operator<<(ostream& stream, const Square_Matrix& matrix)
{
   for (int i = 0; i < matrix.row; i++)
   {
      for (int j = 0; j < matrix.row; j++)
         stream << matrix[i][j] << ' ';
      stream << endl;
   }
   stream << endl;
   return stream;
}

istream& operator>>(istream& stream, Square_Matrix& matrix)
{
   for (int i = 0; i < matrix.row; i++)
   {
      for (int j = 0; j < matrix.row; j++)
         stream >> matrix[i][j];
   }
   return stream;
}

double Square_Matrix::Algebraic_Complement_Matrix()
{
   double result = 0;
   for (int i = 0; i < row; i++)
   {
      for (int j = 0; j < row; j++)
      {
         result += pow(i + j, -1) * Minor_Matrix(i, j);
      }
   }

   return result;
}