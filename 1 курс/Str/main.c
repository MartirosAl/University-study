#include <stdio.h>
#include <stdlib.h>
#include "str.h"

int main()
{
   char str1[100] = "123456789";
   char str2[] = "234";
   char str3[100] = { 0 };


   FILE* file = fopen("text.txt", "r");
   if (file == NULL)
   {
      printf("Невозможно открыть файл. \n");
      return 1;
   }

   printf("%d", my_fgetline(file));

   //printf("%d %d \n", my_strlen(str1), my_strlen(str2));
   //printf("%s \n", my_strcpy(str1, str2)); 
   //printf("%s \n", my_strcat(str1, str2));
   //printf("%d \n", my_strcmp(str1, str2));
   //printf("%s \n", my_strstr(str1, str2));
   //printf("%d \n", fgetline(str3, fp));
   fclose(file);
   return 0;
}
