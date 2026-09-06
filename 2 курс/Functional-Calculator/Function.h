#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <math.h>
using namespace std;


class Function
{
protected:
   double x;
   string name;
public:
   Function() { x = 0;}

   virtual ~Function() { ; }

   virtual const string& Get_Name() const = 0;

   virtual void Set_Arguments() = 0;

   virtual double Calculate() = 0;

   virtual double Calculate(double arg_) = 0;
};

double Factorial(double x)
{
   double checkx = x;
   checkx -= (int)checkx;
   if (checkx != 0)
      throw "Wrong type number! Enter integer";
   
   if (x == 0)
      return 1;

   return x * Factorial(x - 1);
}
