#include <iostream>
#include "Decimal_fractions.h"
using namespace std;
int main()
{
   Decimal_fractions obj1;
   obj1.flag_work_state = false;
   obj1.flag_work_print = false;
   obj1.start_with_file("Test3.txt");
   cout << endl;
   return 0;
}