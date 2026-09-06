#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

int main()
{
	//Структуры для даты и времени
	TimeData* Data_Time_1 = malloc(sizeof(TimeData));
	if (!Data_Time_1)
		return 0;
	TimeData* Data_Time_2 = malloc(sizeof(TimeData));
	if (!Data_Time_2)
		return 0;
	TimeData* Data_Time_Dif = malloc(sizeof(TimeData));
	if (!Data_Time_Dif)
		return 0;

	printf("Enter first date and time in format day.month.year hours:minutes:seconds: "); //Ввод данных 
	scanf_s("%u.%u.%u %u:%u:%u", &Data_Time_1->day, &Data_Time_1->month, &Data_Time_1->year, &Data_Time_1->hour, &Data_Time_1->minute, &Data_Time_1->second);

	//Проверки на правильность введенных данных 
	if (Data_Time_1->month > 12 || (Data_Time_1->month % 2 == 0 ? Data_Time_1->day > 31 : Data_Time_1->day > 30) ||
		Data_Time_1->hour > 23 || Data_Time_1->minute > 59 || Data_Time_1->second > 59 || Data_Time_1->year == 0 ||
		Data_Time_1->month == 0 || Data_Time_1->day == 0)
	{
		printf("ERROR DATA\n");
		return 0;
	}

	printf("Enter second date and time in format day.month.year hours:minutes:seconds: "); //Ввод данных 
	scanf_s("%u.%u.%u %u:%u:%u", &Data_Time_2->day, &Data_Time_2->month, &Data_Time_2->year, &Data_Time_2->hour, &Data_Time_2->minute, &Data_Time_2->second);

	//Проверки на правильность введенных данных 
	if (Data_Time_2->month > 12 || (Data_Time_2->month % 2 == 0 ? Data_Time_2->day > 31 : Data_Time_2->day > 30) ||
		Data_Time_2->hour > 23 || Data_Time_2->minute > 59 || Data_Time_2->second > 59 || Data_Time_2->year == 0 ||
		Data_Time_2->month == 0 || Data_Time_2->day == 0)
	{
		printf("ERROR DATA\n");
		return 0;
	}

	printf("First date entered: %d.%d.%d %d:%d:%d\n", Data_Time_1->day, Data_Time_1->month, Data_Time_1->year, Data_Time_1->hour, Data_Time_1->minute, Data_Time_1->second);
	printf("Second date entered: %d.%d.%d %d:%d:%d\n", Data_Time_2->day, Data_Time_2->month, Data_Time_2->year, Data_Time_2->hour, Data_Time_2->minute, Data_Time_2->second);

	//Проверка на високосный год и 29 февраля
	if (!IsLeapYear(Data_Time_1->year))
		if (Data_Time_1->month == 2 && Data_Time_1->day > 28)
		{
			printf("ERROR DATA\n");
			return 0;
		}
		else
			printf("It's not a leap year\n");
	else
		printf("It's a leap year\n");

	if (!IsLeapYear(Data_Time_2->year))
		if (Data_Time_2->month == 2 && Data_Time_2->day > 28)
		{
			printf("ERROR DATA\n");
			return 0;
		}
		else
			printf("It's not a leap year\n");
	else
		printf("It's a leap year\n");

	printf("WhichDateIsGreater? %d %d\n", WhichDateIsGreater(Data_Time_1, Data_Time_2), WhichDateIsGreater(Data_Time_2, Data_Time_1));
	DataDifference(Data_Time_1, Data_Time_2, Data_Time_Dif);
	printf("%u years %u months %u days %d hours %u minutes %u seconds", Data_Time_Dif->year, Data_Time_Dif->month, Data_Time_Dif->day, Data_Time_Dif->hour, Data_Time_Dif->minute, Data_Time_Dif->second);
	
	free(Data_Time_1);
	free(Data_Time_2);
	free(Data_Time_Dif);

	return 0;
}
