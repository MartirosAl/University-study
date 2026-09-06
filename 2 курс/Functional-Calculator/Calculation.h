#pragma once
#include "Action.h"
class Calculation : public Action
{
   string name;

public:
   Calculation() : name("Calculation") {}

   const string& Get_Name() override { return name; }
   
   void Operate(Function* function_) override
   {
      cout << "y = " << function_->Calculate() << endl;
   }
};

