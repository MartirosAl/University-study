#include "Function.h"

int Reverse(const int number_)
{
	int last_digit = 0;
	int norm_number = number_;
	int reverse_number = 0;
	while (norm_number > 0)
	{
		last_digit = norm_number % 10;
		reverse_number = reverse_number * 10 + last_digit;
		norm_number /= 10;
	}
	return reverse_number;
	// 1234
	// reverse_number = 0.1;
	// last_digit = 4
	// reverse_number = reverse_number * 10 + last_digit
}

bool IsPalindrome(const int number_)
{
	return (number_ == Reverse(number_));
}


