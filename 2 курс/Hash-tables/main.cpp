#include "hash_tables.h"

int test(int a)
{
   return a % 20;
}

int main()
{
   Hash_table_internal A(test, 100, 20); 
   A.insert(0);
   A.insert(60);
   A.insert(100);
   A.insert(200);
   A.insert(400);
   A.insert(1);
   A.insert(21);
   A.insert(41);
   A.insert(61);
   A.insert(2);
   A.insert(22);
   A.remove(100);
   A.remove(1);
   A.insert(42);
   A.insert(500);
   A.insert(3);
   A.insert(23);
   A.insert(43);
   A.remove(2);
   A.remove(43);
   A.Print();
   return 0;
}