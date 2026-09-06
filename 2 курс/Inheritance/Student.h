#pragma once
#include "Human.h"
class Student : virtual public Human
{
protected:

   int grants;

public:

   Student(const char* name_, const int age_, const int grants_) : Human(name_, age_)
   {
      grants = grants_;
   }

   void Print() override
   {
      cout << age << ' ' << name << ' ' << grants;
   }

   int income() override
   {
      return grants;
   }
};