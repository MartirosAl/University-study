#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct comand
{
   char left;
   char centre;
   char right;
   char out;
};

class Base_CA
{
protected:
   string cur_string;
   string next_string;

   Base_CA(string filename, vector<comand> com)
   {
      ;
   }
};