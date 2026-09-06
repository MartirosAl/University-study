#pragma once
#include "Function.h"

class Polynomial : public Function
{
protected:
   double* coefficients;
   int n_coefficients;
public:

   Polynomial()
   {
      coefficients = 0;
      n_coefficients = 0;
      name = "a(0)+...+a(n)*x^n";
   }

   const string& Get_Name() const override { return name; }
   
   double Calculate()
   {
      cout << "Entex x: ";
      cin >> x;

      cout << "Enter number coefficients: ";
      cin >> n_coefficients;
      if (n_coefficients == 0)
         return 0;

      coefficients = new double[n_coefficients + 1];

      cout << "Enter coefficients: ";
      for (int i = n_coefficients - 1; i >= 0; i--)
      {
         cin >> coefficients[i];
         while (!cin.good())
         {
            cout << "Incorrect Input! Try Again" << endl;
            cin >> coefficients[i];
         }
      }

      double result = coefficients[0];
      
      for (int i = 1; i < n_coefficients; i++)
      {
         result *= x;
         result += coefficients[i];
      }

      return result;
   }

   double Calculate(double arg_)
   {
      x = arg_;
      double result = coefficients[0];

      for (int i = 1; i < n_coefficients; i++)
      {
         result *= x;
         result += coefficients[i];
      }

      return result;
   }

   void Set_Arguments()
   {
      cout << "Enter number coefficients: ";
      cin >> n_coefficients;
      if (n_coefficients == 0)
         return;

      coefficients = new double[n_coefficients + 1];

      cout << "Enter coefficients: ";
      for (int i = n_coefficients - 1; i >= 0; i--)
      {
         cin >> coefficients[i];
         while (!cin.good())
         {
            cout << "Incorrect Input! Try Again" << endl;
            cin >> coefficients[i];
         }
      }
   }
};

