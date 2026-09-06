#include "str.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int fgetline(char* line_, FILE* f_) 
{
   

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
   dest[i+n] = '\0';

   return dest;
}
