#pragma once
#include "Function.h"


class Line_function : public Function
{
protected:
   double a;
   double b;
public:
   Line_function()
   {
      a = 0;
      b = 0;
      name = "a*x+b";
   }

   const string& Get_Name() const
   {
      return name;
   }

   double Calculate()
   {
      cout << "Calculation for y = " << name << endl;
      cout << "Enter a: ";
      cin >> a;
      cout << "Enter x: ";
      cin >> x;
      cout << "Enter b: ";
      cin >> b;
      return a * x + b;
   }

   double Calculate(double arg_)
   {
      x = arg_;
      return a * x + b;
   }

   void Set_Arguments()
   {
      cout << "Enter a: ";
      cin >> a;
      cout << "Enter b: ";
      cin >> b;
   }
};

