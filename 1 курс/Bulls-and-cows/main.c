#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int digit4 = 1;
int digit3 = 1;
int digit2 = 1;
int digit1 = 1;
int cows = 0;
int bulls = 0;

int main()
{
   int error = 518181518;
   system("chcp 1251");
   system("cls");
   int x = 1;
   printf("Игра 'Быки и коровы'\n");
   printf("Введите загаданное число: ");
   scanf_s("%d", &x);
   system("cls");

   //Проверка на длину числа
   if (number_length(x) != 4)
   {
      printf("введите четырехзначное число");
      return (error);
   }

   //Отделяем цифры числа и записываем их по переменным
   int num = x;
   digit4 = num % 10; num /= 10;
   digit3 = num % 10; num /= 10;
   digit2 = num % 10; num /= 10;
   digit1 = num % 10;

   //Проверка на повторяющиеся цифры в числе
   if (digit1 == digit2 || digit1 == digit3 || digit1 == digit4 || digit2 == digit3 || digit2 == digit4 || digit3 == digit4)
   {
      printf("введите число без повторяющихся цифр");
      return (error);
   }

   //Ввод предположений и вывод коров и быков
   int assumption = 1;
   int temp = 0;
   bool flag = true;
   while (flag)
   {
      assumption = 1;
      bulls = 0;
      cows = 0;
      scanf_s("%d", &assumption);
      for (int i = 1; i < 5; i++)
      {
         temp = assumption % 10;
         assumption /= 10;
         cows_bulls(temp, i);
      }
      if (bulls == 4)
      {
         printf("ВЕРНО!");
         return assumption;
      }
      printf("\nБыки: %d", bulls);
      printf("\nКоровы: %d \n", cows);
   }
   printf("%d", digit1); printf("%d", digit2); printf("%d", digit3); printf("%d", digit4);
}

//Подсчет коров и быков
cows_bulls(number_, count)
{
   if (count == 4)
   {
      if (digit1 == number_)
         bulls++;
      else if (digit2 == number_ || digit3 == number_ || digit4 == number_)
         cows++;
   }
   else if (count == 3)
   {
      if (digit2 == number_)
         bulls++;
      else if (digit1 == number_ || digit3 == number_ || digit4 == number_)
         cows++;
   }
   else if (count == 2)
   {
      if (digit3 == number_)
         bulls++;
      else if (digit1 == number_ || digit2 == number_ || digit4 == number_)
         cows++;
   }
   else if (count == 1)
   {
      if (digit4 == number_)
         bulls++;
      else if (digit1 == number_ || digit2 == number_ || digit3 == number_)
         cows++;
   }
   return;
}

//Вычисление длины числа
int number_length(number_)
{
   int test = number_;
   int cnt_test = 0;
   while (test > 0)
   {
      test /= 10;
      cnt_test++;
   }
   return cnt_test;
}
