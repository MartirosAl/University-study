#pragma once
#include <stdio.h>

/**
* @brief Считывает строчку из файла
* @param line_: Строка куда считывается
* @param f_: Файл
* @return Кол-во считаймых символов
*/
unsigned int my_fgetline(FILE* file);

/** 
* @brief Считает кол-во символов в строке
* @param str_: Строка
* @return Длину строки
*/
unsigned int my_strlen(const char* str_);

/** 
* @brief Копирует строку в другую переменную 
* @param toHere Куда копируем
* @param fromHere Откуда копируем
* @return Переменная в которую скопировали 
*/
char* my_strcpy(char* toHere, const char* fromHere);

/** 
* @brief Приписывает к одной строке другую
* @param dest К чему приписываем
* @param src Что приписываем
* @return Переманная к которой приписали другую
*/
char* my_strcat(const char* dest, const char* src);

/**
* @brief лексикографическое сравнение строк (возвращает "0", если строки одинаковые, положительное, если первая строка больше, и отрицательное, если меньше)
* @param Строка 1
* @param Строка 2
* @return Выводит 0 если равны, 1 если строка 1 > строки 2, -1 иначе 
*/
int my_strcmp(const char* str1, const char* str2);

/**
* @brief Находит первое вхождение строки needle в haystack
* @param haystack То где ищем
* @param needle Что ищем
* @return Оставшаяся строка начинающаяся с искомой строки
*/
char* my_strstr(const char* haystack, const char* needle);
