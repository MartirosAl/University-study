#include <stdio.h>
#include <stdlib.h>
#include "Structura.h"
#include "function.h"

int main()
{
   system("chcp 1251");
   system("cls");

   FILE* file = fopen("text.txt", "r");
   if (file == NULL)
   {
      printf("Невозможно открыть файл. \n");
      return 1;
   }

   struct Machin car[100];
   
   for(int i = 0; fscanf_s(file, "%[^,],%[^,],%[^,],%d,%d,%d,%d", car[i].M_a, (unsigned)_countof(car[i].M_a),
      car[i].proizv, (unsigned)_countof(car[i].proizv),
      car[i].type, (unsigned)_countof(car[i].type),
      &car[i].G_v, &car[i].Data_r.day, &car[i].Data_r.month, &car[i].Data_r.year) > 0; i++)
   {
      if (my_strcmp0(car[i].M_a, "Ford") && car[i].Data_r.year < 2000)
      {
         printf_s("-----------------------------------------\n");
         printf_s("Марка автомобиля: %s\n", car[i].M_a);
         printf_s("Производитель: %s\n", car[i].proizv);
         printf_s("Тип: %s\n", car[i].type);
         printf_s("Год выпуска: %d\n", car[i].G_v);
         printf_s("Дата регистрации: %d %d %d\n", car[i].Data_r.day, car[i].Data_r.month, car[i].Data_r.year);
      }
   }

   fclose(file);

}
