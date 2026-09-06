#pragma once

#include <stdbool.h>
#ifndef _Functions_H_
#define _Functions_H_

/*
* @brief Возводит число в квадрат
* @param value_ Число
* @return Квадрат числа
*/
unsigned long long Square(const long long value_);

bool IsPalindrome(const int number_);

int Reverse(const int number_);

bool IsPrime(const unsigned long long number_);

unsigned long long int From_Char_to_Int(const char* c_number, int n1, int n2);

int Count_Char(const char* str);

#endif