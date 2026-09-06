#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
* @brief Считывает строчку из файла
* @param line_: Строка куда считывается
* @param f_: Файл
* @return Кол-во считаймых символов
*/
unsigned int fgetline(char* line_, FILE* f_);

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