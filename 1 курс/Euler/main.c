#include <stdio.h>
#include <time.h>
#include "Functions.h"
#include "Euler.h"

#define SIZE 2

int main()
{
   /*
   unsigned int number = 0;
   printf("number = ");
   scanf_s("%du", &number);
   unsigned int multiples[SIZE];
   printf("multiples = ");
   for (unsigned int i = 0; i < SIZE; ++i)
      scanf_s("%du", &multiples[i]);
   time_t start = clock();
   printf("%llu\n", Problem_1(number, multiples, SIZE));
   time_t finish = clock();
   */


   /*
   unsigned int number = 0;
   printf("number = ");
   scanf_s("%du", &number);
   time_t start = clock();
   printf("%llu\n", Problem_2(number));
   time_t finish = clock();
   */

   /*
   time_t start = clock();
   printf("%llu\n", Problem_3(600851475143));
   time_t finish = clock();
   */

   /*
   time_t start = clock();
   printf("%llu\n", Problem_4(3));
   time_t finish = clock();
   */

   /*
   unsigned int number = 0;
   printf("number = ");
   scanf_s("%du", &number);
   unsigned long long number_ = 600851475143;
   time_t start = clock();
   printf("%u\n", Problem_5(20));
   time_t finish = clock();
   */
   

   /*
	unsigned int number;
	printf("Enter number:");
	scanf_s("%u", &number);
   time_t start = clock();
   printf("Difference is: %u\n", Problem_6(number));
   time_t finish = clock();
   */

   /*
	unsigned int number;
	printf("Enter number: ");
	scanf_s("%u", &number);
   time_t start = clock();
   printf("%ust prime is: %u\n", number, Problem_7(number));
   time_t finish = clock();
   */
   

   /*
   char* str = "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450";
   time_t start = clock();
   printf("%llu\n", From_Char_to_Int(str, 0, 13));
   printf("Max product is: %llu \n", Problem_8(str, 13));
   time_t finish = clock();
   */

   /*
   time_t start = clock();
   printf("%u\n", Problem_9(1000));
   time_t finish = clock();
   */


   time_t start = clock();
   printf("%llu\n", Problem_10(2000000));
   time_t finish = clock();


   double time = (double)(finish - start) / CLOCKS_PER_SEC;
   printf("%f\n", time);

   return 0;
}
