#include "Euler.h"
unsigned long long Problem_4()
{
	int max_number = 1000;
	int max_palindrom = 0;
	for (int x = 100; x < max_number; x++)
	{
		for (int y = 100; y < max_number; y++)
			if (IsPalindrome(x * y) && x * y > max_palindrom)
				max_palindrom = x * y;
	}
	return max_palindrom;
}

unsigned long long Problem_5(const int number_)
{
	long long smallest_multiple = 0;
	long long multiple = 1;
	int counter = 0;
	for (; multiple > 0; multiple++)
	{
		counter = 0;
		for (int n = 1; n<=number_; n++)
			if (multiple % n != 0)
			{
				break;
			}
			else
			{
				counter++;
			}
		if (counter == 20)
		{
			smallest_multiple = multiple;
			break;
		}
	}
	return smallest_multiple;
}

