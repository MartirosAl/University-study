#include <stdio.h>
#include "Stones.h"


int main()
{
   int flag = 1;
   Data_Base* DB = CreateDB();
   while (flag)
   {
      int question;

      printf("Big Numbers\n What you want do?");
      printf("1. Create element\n 2. Delete element\n");
      printf("3. Find element \n 4. Sorting\n 5. Print\n 6. Close\n");
      scanf_s("%d", &question);
      switch (question)
      {
      case(1):
         printf("Enter Number Color Operation with plus Operation with multiplication\n");
         int a, b, c, d;
         scanf_s("%d %s %d %d", &a, &b, &c, &d);
         Make_Element(DB, a, b, c, d);
         printf("Done\n");
         break;
      case(2):
         printf("What element we want delelte?\n");
         printf("Enter element and type\n 1. Number of stones\n 2.Color");
         void* e;
         int f;
         scanf_s("%v %d", &e, &f);
         Del_Element(DB, e, f);
         printf("Done\n");
         break;
      case(3):
         printf("What element we want find?\n");
         printf("Enter element and type\n 1. Number of stones\n 2.Color");
         void* g;
         int h;
         scanf_s("%v %d", &g, &h);
         if (b == 1)
            Find_Element_number(DB, (int)g);
         if (b == 2)
            Find_Element_color(DB, (char*)g);
         printf("Done\n");
         break;
      case(4):
         SortDB(DB);
         printf("Done\n");
         break;
      case(5):
         PrintDB(a);
         printf("Done\n");
         break;
      case(6):
         flag = 0;
         break;
      default:
         printf("Wrong");
         break;
      }
   }
   DelDB(DB);
   return 0;
}