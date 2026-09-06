#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// mod 269
int standart(int a)
{
   return a % 269;
}

// Функция для определения ближайшего простого числа, не меньшего заданного
bool isPrime(size_t n) {
   if (n < 2) return false;
   if (n < 4) return true;
   if (n % 2 == 0 || n % 3 == 0) return false;
   for (size_t i = 5; i * i <= n; i += 6) {
      if (n % i == 0 || n % (i + 2) == 0) return false;
   }
   return true;
}

size_t nextPrime(size_t n) {
   while (!isPrime(n)) {
      ++n;
   }
   return n;
}

// Функция определения размера хеш-таблицы
size_t determineHashTableSize(size_t numElements, double loadFactor = 0.75) {
   if (numElements == 0) return 0;

   size_t estimatedSize = static_cast<size_t>(std::ceil(numElements / loadFactor));
   return nextPrime(estimatedSize);
}

struct Element_hash_table
{
   //Значение
   int value;

   //Индекс в таблице лексем
   int index; 

   //Альтернатива для коллизий || next
   size_t alt;    

};

class Hash_table_internal
{
   Element_hash_table* table;

   int(*function)(int);
   
   //Размер всей таблицы
   size_t size_table;

   //Размер основной области
   size_t size_main_area;

   //Следующая свободная ячейка в таблице альтернатив
   size_t next_in_alt_table;

   void Create_table()
   {
      table = new Element_hash_table[size_table];
      table[0].value = 0;
      table[0].index = 0;
      table[0].alt = 0;
      for (size_t i = 1; i < size_table; i++)
      {
         table[i].value = -1;
         table[i].index = -1;
         table[i].alt = 0;
      }
   }

   void Expansion()
   {
      int new_size = determineHashTableSize(size_table);
      Element_hash_table* new_table = new Element_hash_table[new_size];
      Element_hash_table* temp = table;
      for (size_t i = 0; i < size_table; i++)
      {
         new_table[i].value = table[i].value;
         new_table[i].index = table[i].index;
         new_table[i].alt = table[i].alt;
      }
      for (size_t i = size_table; i < new_size; i++)
      {
         new_table[i].value = -1;
         new_table[i].index = -1;
         new_table[i].alt = 0;
      }

      delete[] temp;

      table = new_table; 
   }

   int Conflict_resolution(int a, int ind)
   {
      if (next_in_alt_table == size_table)
      {
         Expansion();
      }
      
      size_t transp = function(a) + 1;
      
      while (table[transp].alt != 0)
      {
         transp = table[transp].alt;
      }

      if (table[0].alt == 0)
      {
         table[transp].alt = next_in_alt_table;
         table[next_in_alt_table].value = a;
         table[next_in_alt_table].index = ind;
         return next_in_alt_table++;
      }
      else
      {
         int alt_zero = table[0].alt;         

         table[0].alt = table[alt_zero].alt;
         table[alt_zero].alt = 0;

         table[transp].alt = alt_zero;
         table[alt_zero].value = a;
         table[alt_zero].index = ind;

      }
      return transp;
   }

   void Correct_removal(int a)
   {
      size_t transp = function(a) + 1;

      if (table[transp].value == a)
      {
         if (table[transp].alt == 0)
         {
            table[transp].value = -1;
         }
         else
         {
            int prev = transp;

            while (table[table[transp].alt].alt != 0)
            {
               transp = table[transp].alt;
            }

            table[prev].value = table[table[transp].alt].value;

            table[table[transp].alt].alt = table[0].alt;
            table[0].alt = table[transp].alt;

            table[table[transp].alt].value = -1;
            table[table[transp].alt].index = -1;
            table[transp].alt = 0;
         }
      }
      else
      {

         while (table[table[transp].alt].value != a)
         {
            transp = table[transp].alt;
         }

         int temp = table[table[transp].alt].alt;

         table[table[transp].alt].alt = table[0].alt;
         
         table[table[transp].alt].value = -1;
         table[table[transp].alt].index = -1;
         
         table[0].alt = table[transp].alt;

         table[transp].alt = temp;

      }
      return;
   }

   int Alt_find(int a)
   {
       size_t transp = function(a) + 1;

       while (table[transp].alt != 0)
       {
           transp = table[transp].alt;
           if (table[transp].value == a)
               return transp;
       }

       return 0;
   }

public:

   //По умолчанию функция mod 269, st = 1361
   Hash_table_internal()
   {
      function = standart;
      size_table = 1361;
      size_main_area = 269 + 1;
      next_in_alt_table = 269 + 2;

      Create_table();
   }

   Hash_table_internal(int(*func)(int), size_t size_table_, size_t size_area_)
   {
      if (size_area_ >= size_table_)
         throw "There are no cells for alternatives";

      function = func;
      size_table = size_table_;

      //Ячейка 0 и еще n ячеек для функции
      size_main_area = size_area_ + 1; 

      //Ячейка 0 и еще n ячеек для функции и после них первая свободная
      next_in_alt_table = size_area_ + 1;

      Create_table();
   }

   int insert(int a, int ind = -1)
   {
      if (find(a))
          return find(a);
      if (table[function(a) + 1].value == -1)
      {
         table[function(a) + 1].value = a;
         table[function(a) + 1].index = ind;
         return (function(a) + 1);
      }
      else
      {
         return Conflict_resolution(a, ind);
      }

   }

   void remove(int a)
   {
      if (!find(a))
      {
         ;
      }
      else
      {
         Correct_removal(a);
      }
    
   }

   int find(int a)
   {
       if (table[function(a) + 1].value == a)
       {
           return function(a) + 1;
       }
       else
       {
           return Alt_find(a);
       }
   }

   //true - если нашел
   bool error_finder()
   {
      for (int i = 1; i < size_table; i++)
      {
         if (table[i].value != -1 && table[i].index == -1)
            return true;
      }
      return false;
   }

   void Print()
   {
      for (int i = 0; i < size_main_area; i++)
      {
         if (table[i].value == -1 && table[i].alt == 0)
            continue;
         cout << "--------------------------------" << endl;
         cout << i << "\t | " << table[i].value << "\t | " << table[i].alt << endl;
      }
      cout << "===================================" << endl;
      for (int i = size_main_area; i < size_table; i++)
      {
         if (table[i].value == -1 && table[i].alt == 0)
            continue;
         cout << i << "\t | " << table[i].value << "\t | " << table[i].alt << endl;
         cout << "--------------------------------" << endl;
      }
   }

   void Print(int a)
   {
      if (a > size_table)
         return;
      for (int i = 0; i < size_main_area; i++)
      {
         cout << "--------------------------------" << endl;
         cout << i << "\t | " << table[i].value << "\t | " << table[i].alt << endl;
      }
      cout << "===================================" << endl;
      for (int i = size_main_area; i < a; i++)
      {
         cout << i << "\t | " << table[i].value << "\t | " << table[i].alt << endl;
         cout << "--------------------------------" << endl;
      }
   }


   void Print_main()
   {
      for (int i = 0; i < size_main_area; i++)
      {
         cout << "--------------------------------" << endl;
         cout << i << "\t | " << table[i].value << "\t | " << table[i].alt << endl;
      }
   }

   void Print_main(int a)
   {
      if (a > size_main_area)
         return;
      for (int i = 0; i < a; i++)
      {
         cout << "--------------------------------" << endl;
         cout << i << "\t | " << table[i].value << "\t | " << table[i].alt << endl;
      }
   }

   void Print_alt()
   {
      cout << "===================================" << endl;
      for (int i = size_main_area; i < size_table; i++)
      {
         cout << "--------------------------------" << endl;
         cout << i << "\t | " << table[i].value << "\t | " << table[i].alt << endl;
      }
   }

   void Print_alt(int a)
   {
      if (a + size_main_area > size_table)
         return;
      cout << "===================================" << endl;
      for (int i = size_main_area; i < a + size_main_area; i++)
      {
         cout << "--------------------------------" << endl;
         cout << i << "\t | " << table[i].value << "\t | " << table[i].alt << endl;
      }
   }
};

