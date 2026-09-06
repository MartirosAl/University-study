#pragma once
#include "Base.h"
class Derived :
    public Base
{
public:

   void Modify_x()
   {
      x /= 2;
   }

   void virtualModify_x()
   {
      x /= 2;
   }
};

