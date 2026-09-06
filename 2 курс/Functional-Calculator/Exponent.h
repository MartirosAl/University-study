#pragma once
#include "Function.h"

class Exponent : public Function
{
   double accurancy;
public:
   Exponent()
   { 
      accurancy = 0.00001;
      name = "e^x";
   }

   const string& Get_Name() const
   {
      return name;
   }

   double Calculate()
   {

      cout << "Calculation for y = " << name << endl;
      cout << "Enter x: ";
      cin >> x;
      cout << "y = ";
      if (x = 1)
      {
         cout << 1;
         return 1;
      }
      int temp1 = 1;
      double result;
      double copy = 1;
      double temp2 = 1;

      cout << copy;
      if (copy > accurancy)
         cout << " + ";
      result = copy;

      try
      {
         for (int i = 1; copy > accurancy; i++)
         {
            copy = (temp2 *= x) / (temp1 *= i);
            cout << copy;
            result += copy;
            if (copy > accurancy)
               cout << " + ";
         }
      }
      catch (const char* error)
      {
         cout << error;
      }
      
      cout << endl;

      return result;
   }

   double Calculate(double arg_)
   {
      x = arg_;
      int temp1 = 1;
      double result;
      double copy = 1;
      double temp2 = x;

      if (x = 1)
      {
         cout << 1;
         return 1;
      }

      cout << copy;
      if (copy > accurancy)
         cout << " + ";
      result = copy;


      try
      {
         for (int i = 1; copy > accurancy; i++)
         {
            copy = (temp2 *= x) / (temp1 *= i);
            cout << copy;
            result += copy;
         }
      }

      catch (const char* error)
      {
         cout << error;
      }

      cout << endl;

      return result;
   }

   void Set_Arguments()
   {
      cout << "Enter accurancy";
      cin >> accurancy;
   }
};

