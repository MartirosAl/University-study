#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Working_Student.h"
#include "Derived.h"
using namespace std;

int main()
{
   //Human* human1 = new Human("Max", 85);

   //Human* human2 = new Student("Nik", 19, 2700);

   //Human* human3 = new Worker("Dan", 48, 48000, "Tvgu");

   //Human* human4 = new Working_Student("Kii", 22, 2700, 25000, "Mak");

   //cout << human1->income() << endl;
   //cout << human2->income() << endl;
   //cout << human3->income() << endl;
   //cout << human4->income() << endl;
   //return 0;

   Base b;
   Base vb;
   Derived d;
   Derived vd;
   b.Print();
   d.Print();

   cout << "not virtual" << endl;
   Base* pb;
   pb = &b;
   pb->Modify_x();
   pb->Print();
   pb = &d;
   pb->Modify_x();
   pb->Print();

   cout << "virtual" << endl;
   Base* vpb;
   vpb = &vb;
   vpb->virtualModify_x();
   vpb->Print();
   vpb = &vd;
   vpb->virtualModify_x();
   vpb->Print();
   return 0;
}