#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class basic_chain
{

protected:
   string str;
   //RCH
   string register_number;
   //RS
   int register_count = 0;
   //RP
   string register_order;
   //RZ
   int register_sign = 0;

public:
   bool flag_work_state = true;
   bool flag_work_print = true;
   virtual long double start(string s) = 0;
   void start_with_file(string filename)
   {
      ifstream in(filename);
      if (!in)
      {
         cout << "Не удалось открыть файл " << filename << endl;
         throw "Error";
      }

      string word;

      while (in >> word)
      {
         start(word);
      }
   }

   virtual ~basic_chain() {};
};



