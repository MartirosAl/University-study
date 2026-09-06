#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Menu.h"


int main()
{
   Line_function line;
   Exponent exp;
   Polynomial pol;

   Calculation cal;
   Tabulation tab;

   Function* func[] = {&line, &exp, &pol};
   Action* act[] = { &cal, &tab };

   Menu menu(func, act);

   while (Function* f_ptr = menu.Selected_Function())
   {
      Action* a_ptr = menu.Selected_Action();
      a_ptr->Operate(f_ptr);
      system("pause");
      system("cls");
   }
   return 0;
}