#pragma once
#include "Student.h"
#include "Worker.h"
class Working_Student : public Student, public Worker
{
public:

   Working_Student(const char* name_, const int age_, const int grants_, const int salary_, const char* name_factory_) : Student(name_, age_, grants_), Worker(name_, age_, salary_, name_factory_), Human(name_, age_) {}


   void Print() override
   {
      cout << age << ' ' << name << ' ' << grants << ' ' << salary << ' ' << name_factory;
   }

   int income() override
   {
      return salary + grants;
   }
};
