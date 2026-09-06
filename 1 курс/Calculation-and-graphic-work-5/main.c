#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Function.h"

int main()
{
   char* mainf = "Test.txt";//Доступно только для VS
   FILE* file = fopen(mainf, "r");
   if (file == NULL)
   {
      printf("Не удалось считать файл");
      return -1;
   }

   char s[100] = "";
   char st[200] = "";

   //Вычисление тандемных повторов и их вывод
   while (!feof(file))
   {
      if (fscanf(file, "%s", s) != 1)
         return -2;
      
      if (Is_Tandem_replay(s))//Проверка на то, что слово изначально не является тандемным повтором
      {
         printf("\n");
         continue;
      }

      Find_TR(st, s);

      Print_TR(st, my_strlen(s));
   }

   fclose(file);

   return 0;
}
