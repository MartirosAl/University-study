#include "function.h"
#include<stdio.h>
#include<string.h>


char* two_spaces(char* strRes_, const char* str_)
{
	if (!str_ || !strRes_)
		return '1';

	while (*str_)
	{
		*strRes_ = *str_;
		
		if (*str_ == ' ')
		{
			strRes_++;
			*strRes_ = ' ';
		}

		strRes_++;
		str_++;
	}

	*strRes_ = '\0';

	return strRes_;
}