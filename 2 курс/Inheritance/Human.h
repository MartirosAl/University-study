#pragma once
#include <iostream>

using namespace std;
class Human
{
protected:

   char* name;
   int age;

public:

   Human(const char* name_, const int age_)
   {

      name = new char[strlen(name_) + 1];
      strcpy(name, name_);

      age = age_;
   }

   virtual ~Human()
   {
      delete[] name;
   }

   virtual void Print()
   {
      cout << age << ' ' << name;
   }

   virtual int income()
   {
      return 0;
   }
};
