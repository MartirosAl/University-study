#pragma once
#include <stdbool.h>
#include "structs.h"

/*
* @brief Проверка на високосный год
* @param year Год требующий проверки
* @return 1, если год високосный, 0 иначе
*/
bool IsLeapYear(unsigned int year);

/*
* @brief Разница между двумя датами
* @param Data_Time Дата #1
* @param Today_Time Дата #2
*/
void DataDifference(TimeData* Data_Time_1, TimeData* Data_Time_2, TimeData* Data_Time_Dif);

/*
* @brief Количество дней в месяце без учета високосного года
* @param mounth Месяц
* @return Дни в месяце
*/
int DaysInMonth(int month);

/*
* @brief Какая дата больше
* @param Data_Time Дата #1
* @param Today_Time Дата #2
* @return 0, если первая дата больше или равна второй, 1 иначе
*/
int WhichDateIsGreater(TimeData* Data_Time_1, TimeData* Data_Time_2);

//int FromMonthsToDays(int month);

//int CountLeapYears(int year_big, int year_small);

