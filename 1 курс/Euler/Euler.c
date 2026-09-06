#include <stdlib.h>
#include "Euler.h"
#include "Math.h"
#include "Functions.h"

unsigned long long Problem_1(const unsigned int number_, const unsigned int* multiples_, const unsigned int size_)
{
   unsigned long long sum = 0;

   for (unsigned int n = 0; n < number_; ++n)
   {
      for (unsigned int i = 0; i < size_; ++i)
      {
         if (n % multiples_[i] == 0)
         {
            sum += n;
            break;
         }
      }
   }
   return sum;
}

unsigned long long Problem_2(const unsigned int number_)
{
   unsigned long long sum = 0;
   unsigned int n1 = 1;
   unsigned int n2 = 2;
   unsigned int i = 0;

   while (i < number_)
   {
      if (n2 % 2 == 0)
         sum = sum + n2;

      i = n2;
      n2 = n2 + n1;
      if (n2 >= number_)
         break;
      n1 = i;
   }

   return sum;

}

unsigned long long Problem_3(const unsigned long long number_)
{
   unsigned long long maxprime_ = 0;
   unsigned long long num = number_;

   for (unsigned long long i = 3; Square(i) - 1 < num; i += 2)
   {
      if (IsPrime(i) && num % i == 0)
         maxprime_ = i;
   }

   return maxprime_;
}

unsigned long long Problem_4(int n_)
{
   int max_number = pow(10,n_);
   int max_palindrom = 0;

   for (int x = 100; x < max_number; x++)
   {
      for (int y = 100; y < max_number; y++)
      {
         if (IsPalindrome(x * y) && ((x * y) > max_palindrom))
         {
            max_palindrom = x * y;
         }
      }
   }

   return max_palindrom;
}

unsigned long long Problem_5(const int number_)
{
   long long smallest_multiple = 0;
   int counter = 0;

   for (long long multiple = 20; multiple < 999999999; multiple += 20)
   {
      counter = 0;

      for (int n = 1; n <= number_; n++)
         if (multiple % n != 0)
            break;
         else
            counter++;

      if (counter == 20)
      {
         smallest_multiple = multiple;
         break;
      }
   }

   return smallest_multiple;
}

int Problem_6(unsigned int n)
{
	unsigned int sum_sqrt = 0;
	unsigned int sqrt_sum = 0;

	for (unsigned int i = 1; i <= n; i++)
	{
		sum_sqrt = sum_sqrt + i * i;
		sqrt_sum = sqrt_sum + i;
	}

	sqrt_sum = sqrt_sum * sqrt_sum;

	return sqrt_sum - sum_sqrt;
}

unsigned int Problem_7(unsigned int n)
{
	if (n == 1)
		return 2;

	unsigned int prime_number = 2;
	unsigned int counter_prime = 1;

	while (counter_prime < n)
	{
		prime_number++;

		if (IsPrime(prime_number) == 1)
			counter_prime++;
	}
	return prime_number;
}

unsigned long long int Problem_8(char* number_, int size)
{
   unsigned long long int num = 0;
   unsigned long long int prod = 1;
   unsigned long long int res = 0;
   for (int i = size; number_[i] != '\0'; i++)
   {
      prod = 1;
      num = From_Char_to_Int(number_, i - size, i);
      while (num)
      {
         prod = prod * (num % 10);
         num = num / 10;
      }
      if (prod > res)
         res = prod;
   }
   return res;
}



int Problem_9(int sum_)
{
   int a = 0;
   int b = 1;
   int c = 2;

   while (c < sum_)
   {
      b = 1;
      while (b < c)
      {
         a = 0;
         while (a < b)
         {
            if (a + b + c == sum_ && Square(a) + Square(b) == Square(c))
               return a * b * c;
            a++;
         }
         b++;
      }
      c++;
   }

   return 0;
}

unsigned long long Problem_10(const unsigned long long n_)
{
   unsigned long long sum = 0;

   char* numbers = (char*)calloc(n_, sizeof(unsigned long long));
   if (numbers == NULL)
      return -2;


   for (unsigned long long x = 2; x < n_; x++)
      numbers[x] = 1;
   numbers[0] = 0;
   numbers[1] = 0;

   for (unsigned long long num = 2; num < n_; num++)
      if (numbers[num] == 1)
         for (unsigned long long i = num; i*num < n_; i++)
            numbers[i * num] = 0;

   for (unsigned long long i = 0; i < n_; i++)
      sum = sum + (numbers[i] == 1 ? i : 0);

   return sum;
}


