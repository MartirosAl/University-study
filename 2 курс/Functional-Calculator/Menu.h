#pragma once
#include "Function.h"
#include "Exponent.h"
#include "Line_function.h"
#include "Polynomial.h"
#include "Calculation.h"
#include "Tabulation.h"
#include "Action.h"

class Menu
{
   Function** func;
   Action** act;


   int Get_Index(size_t options_)
   {
      int option;
      cin >> option;

      while (option <= 0 || option > options_)
      {
         cout << "!!!Incorrect Input !!! Try Again" << endl;
         cin >> option;
      }

      return option;
   }

public:

   Menu() { func = nullptr; act = nullptr; }

   Menu(Function** func_, Action** act_) { func = func_; act = act_; }

   Function* Selected_Function()
   {
      int option = 0;
      int arr_size = 4;


      cout << "Which Function Do You Want To Use?" << endl;

      for (int i = 0; i < arr_size - 1; ++i)
         cout << i + 1 << ". " << func[i]->Get_Name() << endl;

      cout << arr_size << ". Exit" << endl;

      return (func[Get_Index(arr_size) - 1]);
   }

   Action* Selected_Action()
   {
      int option = 0;
      int arr_size = 2;

      cout << endl << "Which Action Do You Want To Use?" << endl;

      for (int i = 0; i < arr_size; ++i)
         cout << i + 1 << ". " << act[i]->Get_Name() << endl;

      return (act[Get_Index(arr_size) - 1]);
   }
};

