#pragma once
#include <stack>
#include "MB Lexical analyzer.h"
#include "Atoms.h"

class MINI_BASIC_Syntax_analyzer :
    protected MINI_BASIC_Lexical_analyzer
{
public:

   void PrintTA();
   void PrintStk();

   MINI_BASIC_Syntax_analyzer();

   void start_SA(string name_file);
   
   bool test_flag = 0;

protected:

   vector<Atom> table_atoms;

   typedef void(MINI_BASIC_Syntax_analyzer::* func) ();
   func Control_Table[34][24];

   stack <int> stk;
   int in; //Указатель на вход
   int num_str; //Номер текущей строки
   vector<int> TM; //Таблица меток
   int NTM; //Указатель на первый свободный элемент таблицы меток

   vector<int> TX; //Таблица для хранения результатов атома хранения
   int NTX; //Указатель на первый свободный элемент таблицы результатов атома хранения
   bool flagErr; //Вид обнаружения ошибки
   int NTtemp; //Указатель на первый свободный элемент в таблицы промежуточных результатов
   int NTA; //Указатель на первый свободный элемент таблицы атомов

   int Find_label(int a);

   void Create_Big_Table();

   void Create_Atom(int type, int a = -1, int b = -1, int c = -1, int d = -1);

   void Error(string errMsg);

   void PrintStk_in_file(ofstream& fa);

   void PrintTA_in_file(ofstream& fa);
   
   void F1();
   void F2();
   void F3();
   void F4();
   void F5();
   void F6();
   void F7();
   void F8();
   void F9();
   void F10();
   void F11();
   void F12();
   void F13();
   void F14();
   void F15();
   void F16();
   void F17();
   void F18();
   void F19();
   void F20();
   void F21();
   void F22();
   void F23();
   void F24();
   void F25();//Attention! 
   void F26();
   void F27();
   void F28();

   void a();
   void b();
   void c();
   void d();
   void e();
   void f();
   void g();
   void h();
   void i();
   void j();
   void k();
   void l();
   void m();
   void n();
   void o();
   void p();
   void q();
   void r();

   void A();

   void B();

   void G1();
   void G2();

   void D();

   void K1();
   void K2();
   void K3();
   void K4();
   void K5();
   void K6();
   void K7();

   void E1();
   void E2();
   void E3();

   void L();

   void M1();
   void M2();
   void M3();
   void M4();

   void N1();
   void N2();

   void K();

   void P1();
   void P2();
   void P3();
   void P4();

   void P();

   void C();

   void T1();
   void T2();
   void T3();

   void O();
};

