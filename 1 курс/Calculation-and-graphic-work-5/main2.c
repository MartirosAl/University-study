#include <stdio.h>
#include "Function.h"

/** 
* @brief Считает кол-во символов в строке
* @param str_: Строка
* @return Длину строки
*/
unsigned long long my_strlen(const char* str_)
{
   unsigned long long len = 0;
   for (; str_[len] != '\0'; len++);

   return len;
}

/**
* @brief Проверяет является ли строка тандемным повтором
* @param str_: Строка
* @return 1, если строка является тандемным повтором; 0, если не является
*/
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

/**
* @brief Копирует символы из одной строки в другую, а так же очищает то, что было в другой строке раньше
* @param toHere: Строка в которую копируем
* @param fromHere: Строка из которой копируем
*/
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

/**
* @brief Находит недостающую часть тандемного повтора из одной строки и записывает тандемный повтор в другую
* @param a_: Строка которая будет тандемным повтором
* @param b_: Строка из которой мы ищем тандемный повтор
*/
void Find_TR(char* a_, char* b_)
{
   my_strcpy(a_, b_);
   
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
            return;
         }
      }
   }

   return;
}

/**
* @brief Выводит в консоль элементы из строки с какого-то места
* @param a_: Строка которую мы выводим
* @param n_: Число обозначающее место с какого элемента выводим 
*/
void Print_TR(char* a_, unsigned long long n_)
{
   for (unsigned long long i = n_; a_[i] != '\0'; i++)
      printf("%c", a_[i]);
   printf("\n");

   return;
}

int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      printf("I`m lox\n");
      return 1;
   }
   
   FILE* file = fopen(argv[1], "r");
   if (file == NULL)
   {
      printf("Не удалось считать файл");
      return -1;
   }

   char s[1000] = "";//Предположим, что число символов в строке не более 1000
   char st[2000] = "";
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
