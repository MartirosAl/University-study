#include "str.h"


int main()
{
   char str1[100] = "1234567";
   char str2[] = "1234";
   printf("%d %d \n", my_strlen(str1), my_strlen(str2));
   //printf("%s \n", my_strcpy(str1, str2)); //Из-за того, что мы меняем в этой функции str1, то все ломается в последующих 
   printf("%s \n", my_strcat(str1, str2));
   return 0;
}


// size_t strlen(const char *);	возвращает длину строки
// char *strcpy(char *toHere, const char *fromHere);	копирует строку из одного места в другое
// char *strcat(char *dest, const char *src);	дописывает строку src в конец dest
// size_t strspn(const char *s, const char *accept);	определяет максимальную длину начальной подстроки, состоящей исключительно из байтов, перечисленных в accept
// char *strstr(const char *haystack, const char *needle);	находит первое вхождение строки needle в haystack