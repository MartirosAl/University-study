#pragma once
#include <iostream>
using namespace std;
class Base
{
protected:   
      int x;
public:
   Base(int x_ = 10)
   {
      x = x_;
   }

   void Print()
   {
      cout << "x=" << x << endl;
   }

   virtual void virtualModify_x()
   {
      x *= 2;
   }

   void Modify_x()
   {
      x *= 2;
   }
};

