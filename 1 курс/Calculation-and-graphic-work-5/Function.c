#include "Function.h"
#include <stdio.h>

unsigned long long my_strlen(const char* str_)
{
   unsigned long long len = 0;
   for (; str_[len] != '\0'; len++);

   return len;
}

short Is_Tandem_replay(char* str_)
{
   unsigned long long x = my_strlen(str_);
   if (x % 2 != 0)
      return 0;

   for (unsigned long long i = 0; 2 * i < x; i++)
      if (str_[i] != str_[x / 2 + i])
         return 0;

   return 1;
}

void my_strcpy(char* toHere, const char* fromHere)
{
   unsigned long long i = 0;
   unsigned long long l = my_strlen(toHere);

   for (; fromHere[i] != '\0'; i++)
      toHere[i] = fromHere[i];

   for (unsigned long long a = i; a < l; a++)
      toHere[a] = '\0';

   return;
}

void Find_TR(char* a_, char* b_)
{
   my_strcpy(a_, b_);

   unsigned short flag = 0;
   unsigned long long temp = 0;

   //Первоначальные длинны слов a_ и b_
   unsigned long long length = my_strlen(a_);

   //Задаю возможную длинну искомой части тандемного повтора 
   for (unsigned long long width = 1; width <= length; width ++) 
   {
      //Двигаюсь по строке и ищу тандемный повтор припысыванием к a_ частей из слова b_ длинной width
      for (unsigned long long i = 0; i + 1 <= length; i++)
      {
         temp = i;
         //Приписываем к a_ части из слова b_ длинной lenght
         for (unsigned long long n = length; n < length + width;)
         {
            a_[n] = b_[temp];
            n++;
            temp++;
         }

         //Нашли тандемный повтор и начинаем выход из функции
         if (Is_Tandem_replay(a_))
         {
            flag = 1;
            return;
         }
      }
   }

   return;
}

void Print_TR(char* a_, unsigned long long n_)
{
   for (unsigned long long i = n_; a_[i] != '\0'; i++)
      printf("%c", a_[i]);
   printf("\n");

   return;
}
