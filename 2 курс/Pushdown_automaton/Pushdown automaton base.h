#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
using namespace std;



class Base_PD
{
protected:



   typedef void(*func)(string);

   struct comand
   {
      string name;
      string data;
      func function;
   };

   struct cell
   {
      string input;
      string pd;
      comand cmd;
   };

   vector<vector<vector<cell>>> tables;

   void Accept(string)
   {
      ;
   }

   void Reject(string)
   {
      ;
   }

   void PUSH(string data_)
   {
      ;
   }

   void STATE(string data_)
   {
      ;
   }

   void POP(string)
   {
      ;
   }

   void HOLD(string)
   {
      ;
   }

   void SHIFT(string)
   {
      ;
   }

   Base_PD(string filename)
   {
      ifstream in(filename);
      if (!in)
      {
         cout << "Can't open file" << filename << endl;
         throw "Error";
      }

      while (true)
      {
         //Встречает первую строку
         First_row_in_table(in);

         while (true)
         {
            Other_row_in_table(in);

            if (in.peek() == '\n')
            {
               index_table++;
               index_column = 0;
               index_row = 0;
               max_column = 0;
            }
            else if (in.peek() == EOF)
               break;

         }
      }
            //name_func = Word_detection(simbol);
            //if (name_func == "PUSH" || name_func == "STATE")
            //{
            //   parameter_1(in);
            //   ... = temp_string;
            //}
   }

private:

   string temp_string = '\0';
   int simbol;
   int index_table = 0;
   int index_row = 0;
   int index_column = 0;

   int index_row = 0;
   int max_column = 0;
   string name_func;

   void parameter_1(ifstream &in)
   {
      simbol = in.get();
      if (simbol != '(')
         ERROR();
      simbol = in.get();
      space_skip(in);
      if (simbol == ')')
         ERROR();
      temp_string = '\0';
      while (simbol != ')')
      {
         temp_string += simbol;
         simbol = in.get();
      }
      
   }

   void First_row_in_table(ifstream& in)
   {
      space_skip(in);
      simbol = in.get();

      index_row = 0;

      while (true)
      {
         if (simbol == ' ' || simbol == '\t')
         {
            space_skip(in);
            Checking_uniqueness_input(temp_string);
            tables[index_table][index_row][index_column].input = temp_string;
            temp_string = '\0';
            index_column++;
            max_column++;
         }
         else if (simbol == '\n')
         {
            Checking_uniqueness_input(temp_string);
            tables[index_table][index_row][index_column].input = temp_string;
            temp_string = '\0';
            index_row++;
            return;
         }
         else if (simbol >= 33 && simbol <= 126)
         {
            temp_string += simbol;
         }
         else
            ERROR();

         simbol = in.get();
      }
   }

   void Other_row_in_table(ifstream& in)
   {
      space_skip(in);
      simbol = in.get();

      index_column = 0;

      while (simbol != ' ' || simbol != '\t')
      {
         if (simbol >= 33 && simbol <= 126)
         {
            temp_string += simbol;
         }
         else
            ERROR();
         simbol = in.get();
      }


      for (int i = 1; i < max_column; i++)
      {
         tables[index_table][index_row][i].input = tables[index_table][0][i].input;
      }

      while (true)
      {
         if (simbol == ' ' || simbol == '\t')
         {
            space_skip(in);
            Checking_uniqueness_pd(temp_string);
            tables[index_table][index_row][index_column].input = temp_string;
            temp_string = '\0';
            index_column++;
         }
         else if (simbol == '\n' || simbol == EOF)
         {
            Checking_uniqueness_pd(temp_string);
            tables[index_table][index_row][index_column].input = temp_string;
            temp_string = '\0';
            index_row++;
            return;
         }
         else if (simbol >= 33 && simbol <= 126)
         {
            temp_string += simbol;
         }

         simbol = in.get();
      }


   }

   void Checking_uniqueness_input(string a_)
   {
      for (int i = 0; i < tables[index_table][index_row].size(); i++)
      {
         if (tables[index_table][index_row][i].input == a_)
            ERROR();
      }
   }

   void Checking_uniqueness_pd(string a_)
   {
      for (int i = 0; i < tables[index_table][index_row].size(); i++)
      {
         if (tables[index_table][index_row][i].pd == a_)
            ERROR();
      }
   }

   void space_skip(ifstream& in)
   {
      while (in.peek() == ' ' || in.peek() == '/t')
         in.get();
   }

   string Word_detection(int s_)
   {
      ;
   }
};