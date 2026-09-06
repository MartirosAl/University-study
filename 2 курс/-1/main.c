#include<stdio.h>
#include<string.h>

int main()
{
	system("chcp 1251"); //Русский язык
	system("cls");

	char str1[100];	//Переманная с ординарными пробелами
	char str2[200];	//Переманная с двойными пробелами

	printf("Введите строку: ");
	gets(str1);


	two_spaces(str2, str1);
	
	printf("\nРезультат: %s", str2);

	return 0;
}