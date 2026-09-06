#pragma once
#include "Human.h"
class Worker : virtual public Human
{
protected:

   char* name_factory;
   int salary;

public:

   Worker(const char* name_, const int age_, const int salary_, const char* name_factory_) : Human(name_, age_)
   {
      salary = salary_;
      name_factory = new char[strlen(name_factory_)];
      sprintf(name_factory, "%s", name_factory_);
   }

   ~Worker() override
   {
      delete[] name_factory;
      //Деструктор Human вызывается автоматически
   }

   void Print() override
   {
      cout << age << ' ' << name << ' ' << salary;
   }

   int income() override
   {
      return salary;
   }
};