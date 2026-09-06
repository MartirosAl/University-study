#include "str.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int my_fgetline(FILE* file) {
   int count = 0;
   int ch;

   while ((ch = fgetc(file)) != EOF) {
      count++;
   }

   return count;
}

unsigned int my_strlen(const char* str_)
{
   unsigned int len = 0;
   for (; str_[len] != '\0'; len++);
   return len;
}

char* my_strcpy(char* toHere, const char* fromHere)
{
   unsigned int i = 0;
   for (; fromHere[i] != '\0'; i++)
      toHere[i] = fromHere[i];

   toHere[i] = '\0';

   return toHere;
}

char* my_strcat(char* dest, const char* src)
{
   unsigned int i = my_strlen(dest);
   unsigned int n = 0;
   for (; src[n] != '\0'; n++)
   {
      dest[n + i] = src[n];
   }
   dest[i + n] = '\0';

   return dest;
}

int my_strcmp(const char* str1, const char* str2)
{
   int i = 0;
   for (; i < my_strlen(str1) || i < my_strlen(str2); i++)
   {
      if (str1[i] < str2[i])
         return -1;
      else if (str1[i] > str2[i])
         return 1;
   }
   if (my_strlen(str1) == my_strlen(str2))
      return 0;

   if (my_strlen(str1) < my_strlen(str2))
      return -1;
   else
      return 1;
}

char* my_strstr(const char* haystack, const char* needle)
{
   char haystack_copy[100] = { 0 };
   unsigned int count = 0;
   short int flag = 1;
   for (int i = 0; i < my_strlen(haystack); i++)
   {
      flag = 1;
      if (haystack[i] == needle[0])
      {
         for (int x = 0; needle[x] != '\0'; x++)
            if (haystack[i + x] != needle[x])
               flag = 0;
         if (flag == 1)
         {
            for (; haystack[i] != '\0'; i++)
            {
               haystack_copy[count] = haystack[i];
               count++;
            }
            return haystack_copy;
         }
      }
   }
   return "NULL";
}
