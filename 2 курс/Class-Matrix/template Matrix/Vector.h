#pragma once
#include <iostream>
using namespace std;

class Vector
{
   double* elements;
   size_t size;
   size_t capasity;

public:

   Vector(double* elements_ = nullptr, size_t size_ = 0);

   Vector(Vector& other_);

   ~Vector();

   Vector operator+(const Vector& other_) const;

   Vector& operator=(const Vector& other_);

   Vector& operator+=(const Vector& other_);

   double operator*(const Vector& other_);

   Vector operator&(const Vector& other_);

   Vector& operator&=(const Vector& other_);

   bool operator==(const Vector& other_);

   bool operator!=(const Vector& other_);

   bool operator!();

   double& operator[](int index) const;

   double& operator[](int index);

   void Push_Back(double elem_);

   void Print_Vectors();
};
