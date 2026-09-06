#pragma once
#include <iostream>
class MatrixExñeption
{
public:
   virtual ~MatrixExñeption() {}

   virtual void Print() const
   {
      std::cout << "Error: Unknown error" << std::endl;
   }
   
};

class OutOfRange : public MatrixExñeption
{
public:
   void Print() const override
   {
      std::cout << "Error: Index out of range" << std::endl;
   }
};

class SizeAreNotSame : public MatrixExñeption
{
public:
   void Print() const override
   {
      std::cout << "Error: Sizes matrixes are not same" << std::endl;
   }
};

class WrongRowsColumns : public MatrixExñeption
{
public:
   void Print() const override
   {
      std::cout << "Error: Wrong rows and columns in this matrix" << std::endl;
   }
};

class WrongData : public MatrixExñeption
{
public:
   void Print() const override
   {
      std::cout << "Error: Wrong enter data" << std::endl;
   }
};

class WrongNotSquare : public MatrixExñeption
{
public:
   void Print() const override
   {
      std::cout << "Error: Not square matrix" << std::endl;
   }
};