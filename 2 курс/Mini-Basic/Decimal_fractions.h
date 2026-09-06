#pragma once
#include "basic_chain.h"
class Decimal_fractions :
   public basic_chain
{
   void(Decimal_fractions::* q) (char ch);
   
public:
   Decimal_fractions() 
   { 
      q = &Decimal_fractions::q0;
      register_count = 0;
      register_order = '0';
      register_sign = 1;
   }

   void P1(char ch)
   {
      register_number = ch;
      q = &Decimal_fractions::q1;
   }

   void P2(char ch)
   {
      register_number = '0';
      register_count = 0;
      q = &Decimal_fractions::q6;
   }

   void P3(char ch)
   {
      register_number += ch;
      q = &Decimal_fractions::q1;
   }

   void P4(char ch)
   {
      register_count = 0;
      q = &Decimal_fractions::q3;
   }

   void P5(char ch)
   {
      register_count = 0;
      q = &Decimal_fractions::q2;
   }

   void P6(char ch)
   {
      register_number += ch;
      register_count++;
      q = &Decimal_fractions::q2;
   }

   void P7(char ch)
   {
      q = &Decimal_fractions::q3;
   }

   void P8(char ch)
   {
      register_order = ch;
      register_sign = 1;
      q = &Decimal_fractions::q5;
   }

   void P9(char ch)
   {
      if (ch == '-')
         register_sign = -1;
      else
         register_sign = 1;

      q = &Decimal_fractions::q4;
   }

   void P10(char ch)
   {
      register_order = ch;
      q = &Decimal_fractions::q5;
   }

   void P11(char ch)
   {
      register_order += ch;
      q = &Decimal_fractions::q5;
   }

   void P12(char ch)
   {
      register_number = ch;
      register_count = 1;
      q = &Decimal_fractions::q2;
   }

   long double k1()
   {
      return stold(register_number);
   }

   long double k2()
   {
      string temp;
      if (((int)register_number.size()) - register_count <= 0)
      {
         temp = "0.";

         for (int i = 0; i < abs((int)register_number.size() - register_count)-1; i++)
            temp += '0';
         return stold(temp += register_number);
         
      }
      else
      {
         string temp;
         temp = register_number;
         reverse(temp.begin(), temp.end());

      
         register_number.resize(register_number.size() - register_count);

         temp.resize(register_count);     
         reverse(temp.begin(), temp.end());

         return stold(register_number + '.' + temp);
      }
   }

   long double k3()
   {
      if (register_sign == -1)
         register_count += stoi(register_order);
      else
         register_count -= stoi(register_order);
      
      if (register_count > 0)
      {
         return k2();
      }
      else
      {
         
         for (int i = 0; i < abs(register_count); i++)
            register_number += '0';
         return stold(register_number);
      }
   }

   long double start(string s)
   {
      q = &Decimal_fractions::q0;
      str = s;
      if (flag_work_print)
         cout << str << endl;
      for (int i = 0; i < str.size(); i++)
      {
         (this->*q)(str[i]);
         if (q == &Decimal_fractions::Error1)
            return 0;
         if (flag_work_state)
            cout << str[i] << endl;
      }

      if (q == &Decimal_fractions::q1)
         return k1();
      else if (q == &Decimal_fractions::q2)
         return k2();
      else if (q == &Decimal_fractions::q5)
         return k3();
      else
         cout << "Bad" << endl;
      return 0;

   }

   void q0(char ch)
   {
      if (flag_work_state)
         cout << "work q0" << endl;

      switch (ch)
      {
      case('0'): case('1'): case('2'): case('3'): case('4'): case('5'): case('6'): case('7'): case('8'): case('9'):
         P1(ch);
         break;

      case('.'):
         P2(ch);
         break;

      default:
         Error_q0();
      }
   }

   void q1(char ch)
   {
      if (flag_work_state)
         cout << "work q1" << endl;
      switch (ch)
      {
      case('0'): case('1'): case('2'): case('3'): case('4'): case('5'): case('6'): case('7'): case('8'): case('9'):
         P3(ch);
         break;

      case('E'): case('e'):
         P4(ch);
         break;

      case('.'):
         P5(ch);
         break;

      default:
         Error_q1();
      }
   }

   void q2(char ch)
   {
      if (flag_work_state)
         cout << "work q2" << endl;
      switch (ch)
      {
      case('0'): case('1'): case('2'): case('3'): case('4'): case('5'): case('6'): case('7'): case('8'): case('9'):
         P6(ch);
         break;

      case('E'): case('e'):
         P7(ch);
         break;

      default:
         Error_q2();
      }
   }

   void q3(char ch)
   {
      if (flag_work_state)
         cout << "work q3" << endl;
      switch (ch)
      {
      case('0'): case('1'): case('2'): case('3'): case('4'): case('5'): case('6'): case('7'): case('8'): case('9'):
         P8(ch);
         break;

      case('+'): case('-'):
         P9(ch);
         break;

      default:
         Error_q3();
      }
   }

   void q4(char ch)
   {
      if (flag_work_state)
         cout << "work q4" << endl;
      switch (ch)
      {
      case('0'): case('1'): case('2'): case('3'): case('4'): case('5'): case('6'): case('7'): case('8'): case('9'):
         P10(ch);
         break;

      default:
         Error_q4();
      }
   }

   void q5(char ch)
   {
      if (flag_work_state)
         cout << "work q5" << endl;
      switch (ch)
      {
      case('0'): case('1'): case('2'): case('3'): case('4'): case('5'): case('6'): case('7'): case('8'): case('9'):
         P11(ch);
         break;

      default:
         Error_q5();
      }
   }
   
   void q6(char ch)
   {
      if (flag_work_state)
         cout << "work q6" << endl;
      switch (ch)
      {
      case('0'): case('1'): case('2'): case('3'): case('4'): case('5'): case('6'): case('7'): case('8'): case('9'):
         P12(ch);
         break;

      default:
         Error_q6();
      }
   }

   void Error()
   {
      cout << "wrong simbol" << endl;
      q = &Decimal_fractions::Error1;
   }

   void Error1(char ch)
   {
      cout << "wrong simbol" << ch << endl;
      q = &Decimal_fractions::Error1;
   }

   void Error_q0()
   {
      cout << "The number must start with a digit or a dot." << endl;
      q = &Decimal_fractions::Error1;
   }

   void Error_q1()
   {
      cout << "The sign should only be placed after the E." << endl;
      q = &Decimal_fractions::Error1;
   }

   void Error_q2()
   {
      cout << "There should be a digit or an E after the dot and the digit." << endl;
      q = &Decimal_fractions::Error1;
   }

   void Error_q3()
   {
      cout << "There should be a number or a sign after the E." << endl;
      q = &Decimal_fractions::Error1;
   }

   void Error_q4()
   {
      cout << "There should be only a number after the sign." << endl;
      q = &Decimal_fractions::Error1;
   }

   void Error_q5()
   {
      cout << "There should be only a digit after the E and the digit." << endl;
      q = &Decimal_fractions::Error1;
   }

   void Error_q6()
   {
      cout << "There should be only a number after the dot." << endl;
      q = &Decimal_fractions::Error1;
   }
};

