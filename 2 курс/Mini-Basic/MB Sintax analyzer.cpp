#include "MB Sintax analyzer.h"

MINI_BASIC_Syntax_analyzer::MINI_BASIC_Syntax_analyzer()
{
   Create_Big_Table();

   ofstream ferr("Errors.txt");
   if (ferr.is_open()) {
       ferr.clear();
       ferr.close();
   }

   ofstream fa("Atoms.txt");
   if (fa.is_open()) {
       fa.clear();
       fa.close();
   }


   stk.push(18);
   stk.push(1);
   NTA = 0;
   in = 0;
   NTX = NTM = 1;
   num_str = 0;
   flagErr = false;

}

void MINI_BASIC_Syntax_analyzer::start_SA(string name_file)
{
   start_LA(name_file);
   //SPrint_table_tokens();

   //Предпологаем наличие мение 700-286 констант
   table_operands.resize(700);

   if (flag_error == true)
      return;

   ofstream fa("Atoms.txt");

   NTtemp = ptr_to_free;
   NTX = 700;
   NTM = 256;

   for (int i = 0; i < table_tokens.size(); i++)
   {
      switch (table_tokens[i].type)
      {
      case 0:
         table_tokens[i].type = 1;
         break;
      case 1:
         table_tokens[i].type = 2;
         break;
      case 2:
         table_tokens[i].type = 16 + table_tokens[i].value;
         break;
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
      case 16:
         //nothing
         break;
      case 17:
         table_tokens[i].type = 22;
         break;
      case 18:
         table_tokens[i].type = 23;
         break;
      }
   }

   int temp_par = -1;
   
   while (in < table_tokens.size())
   {
      
      //70
      temp_par = stk.top();

      
      fa << temp_par << " " << table_tokens[in].type << endl;
      

      PrintStk_in_file(fa);
      PrintTA_in_file(fa);

      fa << endl;
      

      if (test_flag)
      {
          cout << temp_par << " " << table_tokens[in].type << endl;

          PrintStk();
          PrintTA();

          cout << endl;
      }
      (this->*Control_Table[temp_par][table_tokens[in].type])();
   }

   if (flagErr)
   {
       cout << "Errors are present" << endl;
   }

   fa.close();
}

void MINI_BASIC_Syntax_analyzer::Create_Atom(int type, int a, int b, int c, int d)
{
   Atom A;
   A.type = type;
   A.attribute1 = a;
   A.attribute2 = b;
   A.attribute3 = c;
   A.attribute4 = d;
   table_atoms.push_back(A);
   NTA++;
}

void MINI_BASIC_Syntax_analyzer::PrintTA()
{
   cout << "TA" << endl << string(25, '-') << endl;
   for (int i = 0; i < table_atoms.size(); i++)
   {
      cout << AtomTypeString[table_atoms[i].type];
      if (table_atoms[i].attribute1 != -1)
         cout << " " << table_atoms[i].attribute1;
      if (table_atoms[i].attribute2 != -1)
         cout << " " << table_atoms[i].attribute2;
      if (table_atoms[i].attribute3 != -1)
         cout << " " << table_atoms[i].attribute3;
      if (table_atoms[i].attribute4 != -1)
         cout << " " << table_atoms[i].attribute4;
      cout<< endl << string(25, '-') << endl;
   }

   
}

void MINI_BASIC_Syntax_analyzer::PrintStk()
{
    cout << "Stk" << endl;
    stack<int> temp;
    for (int i = 0; i < stk.size();)
    {
        cout << stk.top() << " " << endl;
        temp.push(stk.top());
        stk.pop();
    }
    for (int i = 0; i < temp.size();)
    {
        stk.push(temp.top());
        temp.pop();
    }
    cout << endl;

}


void MINI_BASIC_Syntax_analyzer::PrintTA_in_file(ofstream& fa)
{
    fa << "TA" << endl << string(25, '-') << endl;
    for (int i = 0; i < table_atoms.size(); i++)
    {
        fa << AtomTypeString[table_atoms[i].type];
        if (table_atoms[i].attribute1 != -1)
            fa << " " << table_atoms[i].attribute1;
        if (table_atoms[i].attribute2 != -1)
            fa << " " << table_atoms[i].attribute2;
        if (table_atoms[i].attribute3 != -1)
            fa << " " << table_atoms[i].attribute3;
        if (table_atoms[i].attribute4 != -1)
            fa << " " << table_atoms[i].attribute4;
        fa << endl << string(25, '-') << endl;
    }

}

void MINI_BASIC_Syntax_analyzer::PrintStk_in_file(ofstream& fa)
{
   fa << "Stk" << endl;
   stack<int> temp;
   for (int i = 0; i < stk.size();)
   {
      fa << stk.top() << " " << endl;
      temp.push(stk.top());
      stk.pop();
   }
   for (int i = 0; i < temp.size();)
   {
      stk.push(temp.top());
      temp.pop();
   }
   fa << endl;

}

void MINI_BASIC_Syntax_analyzer::Error(string error)
{
   ofstream ferr("errors.txt");
   ferr << "Oшибка: Cтpoka " << num_str << ' ' << error;
   flagErr = true;

   if (table_tokens[in].type == 23)
   {
      in++;
   }
   else
   {
      while (in < table_tokens.size() && table_tokens[in].type != 1)
         in++;
   }

   if (stk.top() == 1 || stk.top() == 2 || stk.top() == 4) 
      return;
   else if (stk.top() == 16 || stk.top() == 18)
   {
      stk.pop(); stk.push(2);
   }
   else
   {
      while (stk.top() != 4)
         stk.pop();
   }

   ferr.close();
}


void MINI_BASIC_Syntax_analyzer::a()
{
   stk.pop();
   in++;
}
void MINI_BASIC_Syntax_analyzer::b()
{
   stk.pop();
   int i = stk.top() - 1;
   stk.pop();
   stack<int> tmp;
   while (i != 0)
   {
      tmp.push(stk.top());
      stk.pop();
      i--;
   }
   stk.pop();
   stk.push(table_tokens[in].value);
   while (!tmp.empty())
   {
      stk.push(tmp.top());
      tmp.pop();
   }
   in++;
}
void MINI_BASIC_Syntax_analyzer::c()
{
   Create_Atom(0);
   in++;
}
void MINI_BASIC_Syntax_analyzer::d()
{
   int k1, k2;
   stk.pop();
   k1 = stk.top();
   stk.pop();
   k2 = stk.top();
   stk.pop();
   Create_Atom(2, k1, k2);
}
void MINI_BASIC_Syntax_analyzer::e()
{
   int p, q, r, s;
   stk.pop();
   p = stk.top();
   stk.pop();
   q = stk.top();
   stk.pop();
   r = stk.top();
   stk.pop();
   s = stk.top();
   stk.pop();
   Create_Atom(6, p, q, r, s);

}
void MINI_BASIC_Syntax_analyzer::f()
{
   int p, q;
   stk.pop();
   p = stk.top();
   stk.pop();
   q = stk.top();
   stk.pop();
   Create_Atom(7, p, q);
}
void MINI_BASIC_Syntax_analyzer::g()
{
   int p;
   stk.pop();
   p = stk.top();
   stk.pop();
   Create_Atom(8, p);
}
void MINI_BASIC_Syntax_analyzer::h()
{
   int p, q, r, s;
   stk.pop();
   p = stk.top();
   stk.pop();
   q = stk.top();
   stk.pop();
   r = stk.top();
   stk.pop();
   s = stk.top();
   stk.pop();
   Create_Atom(9, p, q, r, s);
}
void MINI_BASIC_Syntax_analyzer::i()
{
   int k1, k2;
   stk.pop();
   k1 = stk.top();
   stk.pop();
   k2 = stk.top();
   stk.pop();
   if (k1 != k2)
   {
      Error("The variable in the 'next' statement is different from the variable in the 'for' statement");
   }
   stk.pop();
}
void MINI_BASIC_Syntax_analyzer::l()
{
   int p, q, r;
   stk.pop();
   p = stk.top();
   stk.pop();
   q = stk.top();
   stk.pop();
   r = stk.top();
   stk.pop();
   Create_Atom(11, p, q, r);
}
void MINI_BASIC_Syntax_analyzer::j()
{
   int p, q;
   stk.pop();
   p = stk.top();
   stk.pop();
   q = stk.top();
   stk.pop();
   Create_Atom(10, p, q);
}
void MINI_BASIC_Syntax_analyzer::k()
{
   int p;
   stk.pop();
   p = stk.top();
   stk.pop();
   Create_Atom(3, p);
}
void MINI_BASIC_Syntax_analyzer::n()
{
   int p, q, r;
   stk.pop();
   p = stk.top();
   stk.pop();
   q = stk.top();
   stk.pop();
   r = stk.top();
   stk.pop();
   Create_Atom(13, p, q, r);
}
void MINI_BASIC_Syntax_analyzer::m()
{
   int p, q, r;
   stk.pop();
   p = stk.top();
   stk.pop();
   q = stk.top();
   stk.pop();
   r = stk.top();
   stk.pop();
   Create_Atom(12, p, q, r);
}
void MINI_BASIC_Syntax_analyzer::o()
{
   int p, q, r;
   stk.pop();
   p = stk.top();
   stk.pop();
   q = stk.top();
   stk.pop();
   r = stk.top();
   stk.pop();
   Create_Atom(14, p, q, r);
}
void MINI_BASIC_Syntax_analyzer::p()
{
   int p, q, r;
   stk.pop();
   p = stk.top();
   stk.pop();
   q = stk.top();
   stk.pop();
   r = stk.top();
   stk.pop();
   Create_Atom(15, p, q, r);
}
void MINI_BASIC_Syntax_analyzer::q()
{
   int k1, k2;
   stk.pop();
   k1 = stk.top();
   stk.pop();
   k2 = stk.top();
   stk.pop();
   Create_Atom(16, k1, k2);
}
void MINI_BASIC_Syntax_analyzer::r()
{
   int k1, k2;
   stk.pop();
   k1 = stk.top();
   stk.pop();
   k2 = stk.top();
   stk.pop();
   Create_Atom(17, k1, k2);
}

void MINI_BASIC_Syntax_analyzer::F1()
{
   stk.pop();
   stk.push(16);
   stk.push(2);
   Create_Atom(1, table_tokens[in].value);

   num_str = table_number_string[table_tokens[in].value];
   in++;

}
void MINI_BASIC_Syntax_analyzer::F2()
{
   stk.pop();
   int k = stk.top();
}
void MINI_BASIC_Syntax_analyzer::F3()
{
   Create_Atom(1, table_tokens[in].value);
   num_str = table_number_string[table_tokens[in].value];
   in++;
}
void MINI_BASIC_Syntax_analyzer::F4()
{
   stk.pop();
   stk.push(4);//другие строки
   stk.push(0);
   stk.push(table_tokens[in].value);
   stk.push(19);//присв
   stk.push(3);
   stk.push(5);//выражение
   in++;
}
void MINI_BASIC_Syntax_analyzer::F5()
{
   stk.pop();
   stk.push(4);
   Create_Atom(3, table_tokens[in].value);
   in++;
}
void MINI_BASIC_Syntax_analyzer::F6()
{
   stk.pop();
   stk.push(4);
   stk.push(0);
   stk.push(0);
   stk.push(0);
   stk.push(0);
   stk.push(20);
   stk.push(5);
   stk.push(14);
   stk.push(5);
   stk.push(5);
   stk.push(8);
   stk.push(12);
   stk.push(8);
   stk.push(5);
   in++;
}
void MINI_BASIC_Syntax_analyzer::F7()
{
   stk.pop();
   stk.push(4);
   Create_Atom(4, table_tokens[in].value);
   in++;
}
void MINI_BASIC_Syntax_analyzer::F8()
{
   stk.pop();
   stk.push(4);
   Create_Atom(5);
   in++;
}
void MINI_BASIC_Syntax_analyzer::F9()
{
   table_operands.resize(table_operands.size() + 2);
   int p, s, t, u, v, y;
   p = table_tokens[in].value;// Значение входа
   s = NTX;// Значение поставляемому вызовом процедуры НОВТX
   NTX++;
   
   t = NTX;// Значение поставляемому другим вызовом процедуры НОВТХ
   NTX++;
   u = NTM;// значение поставляемому вызовом процедуры НОВТАМ
   NTM++;
   v = NTM;//значение поставляемому другим вызовом процедуры НОВТАМ
   NTM++;
   y = num_str;
   stk.pop();
   stk.push(4);
   stk.push(v);
   stk.push(22);
   stk.push(u);
   stk.push(26);
   stk.push(t);
   stk.push(p);
   stk.push(25);
   stk.push(y);
   stk.push(0);
   stk.push(p);
   stk.push(24);
   stk.push(3);
   stk.push(13);
   stk.push(4);
   stk.push(v);
   stk.push(t);
   stk.push(s);
   stk.push(p);
   stk.push(23);
   stk.push(u);
   stk.push(22);
   stk.push(t);
   stk.push(0);
   stk.push(21);
   stk.push(2);
   stk.push(3);
   stk.push(s);
   stk.push(0);
   stk.push(21);
   stk.push(2);
   stk.push(5);
   stk.push(17);
   stk.push(0);
   stk.push(p);
   stk.push(19);
   stk.push(3);
   stk.push(5);
   in++;
}
void MINI_BASIC_Syntax_analyzer::F10()
{
   stk.pop();
   stk.push(5);
   in++;
}
void MINI_BASIC_Syntax_analyzer::F11()
{
   table_operands[ptr_to_free] = 1;
   stk.pop();
   stk.pop();
   int p = stk.top();
   stk.pop();
   stk.pop();
   stk.push(ptr_to_free);
   stk.push(p);

   ptr_to_free++;
}
void MINI_BASIC_Syntax_analyzer::F12()
{
   stk.pop();
   stk.push(4);
   in++;
}

void MINI_BASIC_Syntax_analyzer::F13()
{
   stk.pop();
   stk.push(2);
   Create_Atom(1, table_tokens[in].value);
   num_str = table_number_string[table_tokens[in].value];
   in++;
}
void MINI_BASIC_Syntax_analyzer::F14()
{
   stk.pop();
   stk.push(0);
   stk.push(9);
   stk.push(2);
   stk.push(6);
}
void MINI_BASIC_Syntax_analyzer::F15()
{
   stk.pop();
   stk.push(NTtemp);
   stk.push(9);
   stk.push(NTtemp);
   stk.push(0);
   stk.push(32);
   stk.push(2);
   stk.push(6);
   NTtemp++;
   in++;
}

void MINI_BASIC_Syntax_analyzer::F16()
{
   stk.pop();
   stk.push(NTtemp);
   stk.push(9);
   stk.push(NTtemp);
   stk.push(0);
   stk.push(33);
   stk.push(2);
   stk.push(6);
   NTtemp++;
   in++;
}
void MINI_BASIC_Syntax_analyzer::F17()
{
   stk.pop();
   int p = stk.top();
   stk.pop();
   stk.push(NTtemp);
   stk.push(9);
   stk.push(NTtemp);
   stk.push(0);
   stk.push(p);
   stk.push(27);
   stk.push(3);
   stk.push(6);
   NTtemp++;
   in++;
}

void MINI_BASIC_Syntax_analyzer::F18()
{
   stk.pop();
   int p = stk.top();
   stk.pop();
   stk.push(NTtemp);
   stk.push(9);
   stk.push(NTtemp);
   stk.push(0);
   stk.push(p);
   stk.push(28);
   stk.push(3);
   stk.push(6);
   NTtemp++;
   in++;
}

void MINI_BASIC_Syntax_analyzer::F19()
{
   stk.pop();
   int p = stk.top();
   stk.pop();
   int i = stk.top() - 1;
   stk.pop();
   stack<int> tmp;
   while (i > 0)
   {
      tmp.push(stk.top());
      stk.pop();
      i--;
   }

   while (stk.top() != 0)
   {
      tmp.push(stk.top());
      stk.pop();
   }
   stk.pop();
   stk.push(p);
   while (!tmp.empty())
   {
      stk.push(tmp.top());
      tmp.pop();
   }
}


void MINI_BASIC_Syntax_analyzer::F20()
{
   stk.pop();
   stk.push(0);
   stk.push(10);
   stk.push(2);
   stk.push(7);
}

void MINI_BASIC_Syntax_analyzer::F21()
{
   stk.pop();
   int p = stk.top();
   stk.pop();
   stk.push(NTtemp);
   stk.push(10);
   stk.push(NTtemp);
   stk.push(0);
   stk.push(p);
   stk.push(29);
   stk.push(3);
   stk.push(7);
   NTtemp++;
   in++;
}


void MINI_BASIC_Syntax_analyzer::F22()
{
   stk.pop();
   int p = stk.top();
   stk.pop();
   stk.push(NTtemp);
   stk.push(10);
   stk.push(NTtemp);
   stk.push(0);
   stk.push(p);
   stk.push(30);
   stk.push(3);
   stk.push(7);
   NTtemp++;
   in++;
}

void MINI_BASIC_Syntax_analyzer::F23()
{
   stk.pop();
   int p = stk.top();
   stk.pop();
   int i = stk.top() - 1;
   stk.pop();
   stack<int> tmp;
   while (i != 0)
   {
      tmp.push(stk.top());
      stk.pop();
      i--;
   }
   while (stk.top() != 0)
   {
      tmp.push(stk.top());
      stk.pop();
   }
   stk.pop();
   stk.push(p);
   while (!tmp.empty())
   {
      stk.push(tmp.top());
      tmp.pop();
   }
}

void MINI_BASIC_Syntax_analyzer::F24()
{
   stk.pop();
   stk.push(0);
   stk.push(11);
   stk.push(2);
   stk.push(8);
}

void MINI_BASIC_Syntax_analyzer::F25()
{
   stk.pop();
   int p = stk.top();
   stk.pop();
   int t = stk.top();
   stk.push(NTtemp);
   stk.push(11);
   stk.push(NTtemp);
   stk.push(0);
   stk.push(p);
   stk.push(31);
   stk.push(3);
   stk.push(8);
   NTtemp++;
   in++;
}

void MINI_BASIC_Syntax_analyzer::F26()
{
   stk.pop();
   int p = stk.top();
   stk.pop();
   int i = stk.top() - 1;
   stk.pop();
   stack<int> tmp;
   while (i > 0)
   {
      tmp.push(stk.top());
      stk.pop();
      i--;
   }

   while (stk.top() != 0)
   {
      tmp.push(stk.top());
      stk.pop();
   }
   stk.pop();
   stk.push(p);
   while (!tmp.empty())
   {
      stk.push(tmp.top());
      tmp.pop();
   }
}

void MINI_BASIC_Syntax_analyzer::F27()
{
   stk.pop();
   int p = stk.top();
   stk.pop();
   stk.push(15);
   stk.push(p);
   stk.push(5);
   in++;
}

void MINI_BASIC_Syntax_analyzer::F28()
{
   stk.pop();
   int i = stk.top() - 1;
   stk.pop();
   stack<int> tmp;
   while (i > 0)
   {
      tmp.push(stk.top());
      stk.pop();
      i--;
   }
   while (stk.top() != 0)
   {
      tmp.push(stk.top());
      stk.pop();
   }
   stk.pop();
   stk.push(table_tokens[in].value);
   while (!tmp.empty())
   {
      stk.push(tmp.top());
      tmp.pop();
   }
   in++;
}

// Процедуры перехода на обработку ошибки
void MINI_BASIC_Syntax_analyzer::A()
{
   Error("Программа начинается неверно.");
}
void MINI_BASIC_Syntax_analyzer::B() {
   Error("Оператор начинается неверно.");
}
void MINI_BASIC_Syntax_analyzer::G1() {
   Error("Неожиданный вход после for-оператора.");
}
void MINI_BASIC_Syntax_analyzer::G2() {
   Error("Лишняя правая скобка в выражении после table_operands.");
}
void MINI_BASIC_Syntax_analyzer::C() {
   Error(" ");
}
void MINI_BASIC_Syntax_analyzer::D() {
   Error("Неожиданный вход после оператора.");
}
void MINI_BASIC_Syntax_analyzer::K1() {
   Error("Выражение незаконно - нет операнда.");
}
void MINI_BASIC_Syntax_analyzer::K2() {
   Error("Оператор незакончен.");
}
void MINI_BASIC_Syntax_analyzer::K3() {
   Error("В выражении пропущен операнд.");
}
void MINI_BASIC_Syntax_analyzer::K4() {
   Error("Неожиданный вход после выражения.");
}
void MINI_BASIC_Syntax_analyzer::K5() {
   Error("Выражение начинается с недопустимого символа.");
}
void MINI_BASIC_Syntax_analyzer::K6()
{
   Error("Два знака операции в выражении.");
}

void MINI_BASIC_Syntax_analyzer::K7() {
   Error("В выражении пропущен знак операции.");
}

void MINI_BASIC_Syntax_analyzer::E1() {
   Error("Неожиданный вход в if-операторе.");
}

void MINI_BASIC_Syntax_analyzer::E2() {
   Error("If-оператор незакончен.");
}

void MINI_BASIC_Syntax_analyzer::E3() {
   Error("Лишняя правая скобка в выражении после И.");
}

void MINI_BASIC_Syntax_analyzer::L() {
   Error("for-операторы вложены неверно. Пропущено next");
}

void MINI_BASIC_Syntax_analyzer::M1() {
   Error("Неожиданный вход в if-операторе.");
}

void MINI_BASIC_Syntax_analyzer::M2() {
   Error("If-оператор незакончен.");
}

void MINI_BASIC_Syntax_analyzer::M3() {
   Error("Два знака отношения в if-операторе.");
}

void MINI_BASIC_Syntax_analyzer::M4() {
   Error("Лишняя правая скобка в выражении после знака отношения.");
}

void MINI_BASIC_Syntax_analyzer::N1() {
   Error("Пропущена правая скобка перед вход.");
}

void MINI_BASIC_Syntax_analyzer::N2() {
   Error("Пропущена правая скобка в конце строки.");
}

void MINI_BASIC_Syntax_analyzer::K() {
   Error("for-операторы вложены неверно - лишнее next.");
}

void MINI_BASIC_Syntax_analyzer::P1() {
   Error("Неожиданный вход в for-операторе.");
}

void MINI_BASIC_Syntax_analyzer::P2() {
   Error("for-оператор незакончен.");
}

void MINI_BASIC_Syntax_analyzer::P3() {
   Error("Лишняя правая скобка в выражении после to.");
}

void MINI_BASIC_Syntax_analyzer::P4() {
   Error("to пропущено или не на своём месте в for-операторе.");
}

void MINI_BASIC_Syntax_analyzer::P() {
   Error("Программа продолжается после end-оператора.");
}
void MINI_BASIC_Syntax_analyzer::T1() {
   Error("Нет программы.");
}

void MINI_BASIC_Syntax_analyzer::T2() {
   Error("Пропущен end-оператор.");
}

void MINI_BASIC_Syntax_analyzer::T3() {
   Error("Программа кончается посреди оператора.");
}

void MINI_BASIC_Syntax_analyzer::O() {
   Error("Ошибка компилятора.");
}


int MINI_BASIC_Syntax_analyzer::Find_label(int a)
{
   for (int i = 0; i < table_tokens.size(); i++)
   {
      if (table_tokens[i].type == 1 && table_tokens[i].value == a)//Уже передаланное под таблицу
         return i;

   }
   cout << "Error Error'a" << endl;
}

void MINI_BASIC_Syntax_analyzer::Create_Big_Table()
{
   //<Программа>
   Control_Table[1][1] = &MINI_BASIC_Syntax_analyzer::F1;
   Control_Table[1][2] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][3] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][4] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][5] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][6] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][7] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][8] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][9] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][10] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][11] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][12] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][13] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][14] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][15] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][16] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][17] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][18] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][19] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][20] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][21] = &MINI_BASIC_Syntax_analyzer::A;
   Control_Table[1][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[1][23] = &MINI_BASIC_Syntax_analyzer::T1;

   //<Тело программы>
   Control_Table[2][1] = &MINI_BASIC_Syntax_analyzer::F3;
   Control_Table[2][2] = &MINI_BASIC_Syntax_analyzer::B;
   Control_Table[2][3] = &MINI_BASIC_Syntax_analyzer::B;
   Control_Table[2][4] = &MINI_BASIC_Syntax_analyzer::F2;
   Control_Table[2][5] = &MINI_BASIC_Syntax_analyzer::F4;
   Control_Table[2][6] = &MINI_BASIC_Syntax_analyzer::F9;
   Control_Table[2][7] = &MINI_BASIC_Syntax_analyzer::F5;
   Control_Table[2][8] = &MINI_BASIC_Syntax_analyzer::F7;
   Control_Table[2][9] = &MINI_BASIC_Syntax_analyzer::B;
   Control_Table[2][10] = &MINI_BASIC_Syntax_analyzer::B;
   Control_Table[2][11] = &MINI_BASIC_Syntax_analyzer::F6;
   Control_Table[2][12] = &MINI_BASIC_Syntax_analyzer::F8;
   Control_Table[2][13] = &MINI_BASIC_Syntax_analyzer::F2;
   Control_Table[2][14] = &MINI_BASIC_Syntax_analyzer::B;
   Control_Table[2][15] = &MINI_BASIC_Syntax_analyzer::B;
   Control_Table[2][16] = &MINI_BASIC_Syntax_analyzer::F12;
   Control_Table[2][17] = &MINI_BASIC_Syntax_analyzer::B;
   Control_Table[2][18] = &MINI_BASIC_Syntax_analyzer::B;
   Control_Table[2][19] = &MINI_BASIC_Syntax_analyzer::B;
   Control_Table[2][20] = &MINI_BASIC_Syntax_analyzer::B;
   Control_Table[2][21] = &MINI_BASIC_Syntax_analyzer::B;
   Control_Table[2][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[2][23] = &MINI_BASIC_Syntax_analyzer::T2;

   //<Шаг>
   Control_Table[3][1] = &MINI_BASIC_Syntax_analyzer::F11;
   Control_Table[3][2] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][3] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][4] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][5] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][6] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][7] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][8] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][9] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][10] = &MINI_BASIC_Syntax_analyzer::G2;
   Control_Table[3][11] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][12] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][13] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][14] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][15] = &MINI_BASIC_Syntax_analyzer::F10;
   Control_Table[3][16] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][17] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][18] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][19] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][20] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][21] = &MINI_BASIC_Syntax_analyzer::G1;
   Control_Table[3][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[3][23] = &MINI_BASIC_Syntax_analyzer::T2;

   //<Другие строки>
   Control_Table[4][1] = &MINI_BASIC_Syntax_analyzer::F13;
   Control_Table[4][2] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][3] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][4] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][5] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][6] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][7] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][8] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][9] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][10] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][11] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][12] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][13] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][14] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][15] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][16] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][17] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][18] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][19] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][20] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][21] = &MINI_BASIC_Syntax_analyzer::D;
   Control_Table[4][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[4][23] = &MINI_BASIC_Syntax_analyzer::T2;

   //<Выражение>
   Control_Table[5][1] = &MINI_BASIC_Syntax_analyzer::K2;
   Control_Table[5][2] = &MINI_BASIC_Syntax_analyzer::F14;
   Control_Table[5][3] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[5][4] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[5][5] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[5][6] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[5][7] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[5][8] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[5][9] = &MINI_BASIC_Syntax_analyzer::F14;
   Control_Table[5][10] = &MINI_BASIC_Syntax_analyzer::K3;
   Control_Table[5][11] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[5][12] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[5][13] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[5][14] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[5][15] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[5][16] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[5][17] = &MINI_BASIC_Syntax_analyzer::F15;
   Control_Table[5][18] = &MINI_BASIC_Syntax_analyzer::F16;
   Control_Table[5][19] = &MINI_BASIC_Syntax_analyzer::K5;
   Control_Table[5][20] = &MINI_BASIC_Syntax_analyzer::K5;
   Control_Table[5][21] = &MINI_BASIC_Syntax_analyzer::K5;
   Control_Table[5][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[5][23] = &MINI_BASIC_Syntax_analyzer::T3;

   //<Терм>
   Control_Table[6][1] = &MINI_BASIC_Syntax_analyzer::K2;
   Control_Table[6][2] = &MINI_BASIC_Syntax_analyzer::F20;
   Control_Table[6][3] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[6][4] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[6][5] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[6][6] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[6][7] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[6][8] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[6][9] = &MINI_BASIC_Syntax_analyzer::F20;
   Control_Table[6][10] = &MINI_BASIC_Syntax_analyzer::K3;
   Control_Table[6][11] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[6][12] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[6][13] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[6][14] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[6][15] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[6][16] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[6][17] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[6][18] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[6][19] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[6][20] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[6][21] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[6][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[6][23] = &MINI_BASIC_Syntax_analyzer::T3;

   //<Множитель>
   Control_Table[7][1] = &MINI_BASIC_Syntax_analyzer::K2;
   Control_Table[7][2] = &MINI_BASIC_Syntax_analyzer::F24;
   Control_Table[7][3] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[7][4] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[7][5] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[7][6] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[7][7] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[7][8] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[7][9] = &MINI_BASIC_Syntax_analyzer::F24;
   Control_Table[7][10] = &MINI_BASIC_Syntax_analyzer::K3;
   Control_Table[7][11] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[7][12] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[7][13] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[7][14] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[7][15] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[7][16] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[7][17] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[7][18] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[7][19] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[7][20] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[7][21] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[7][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[7][23] = &MINI_BASIC_Syntax_analyzer::T3;

   //<первичное>
   Control_Table[8][1] = &MINI_BASIC_Syntax_analyzer::K2;
   Control_Table[8][2] = &MINI_BASIC_Syntax_analyzer::F28;
   Control_Table[8][3] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[8][4] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[8][5] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[8][6] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[8][7] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[8][8] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[8][9] = &MINI_BASIC_Syntax_analyzer::F27;
   Control_Table[8][10] = &MINI_BASIC_Syntax_analyzer::K3;
   Control_Table[8][11] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[8][12] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[8][13] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[8][14] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[8][15] = &MINI_BASIC_Syntax_analyzer::K1;
   Control_Table[8][16] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[8][17] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[8][18] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[8][19] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[8][20] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[8][21] = &MINI_BASIC_Syntax_analyzer::K6;
   Control_Table[8][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[8][23] = &MINI_BASIC_Syntax_analyzer::T3;

   //<E-список>
   Control_Table[9][1] = &MINI_BASIC_Syntax_analyzer::F19;
   Control_Table[9][2] = &MINI_BASIC_Syntax_analyzer::K7;
   Control_Table[9][3] = &MINI_BASIC_Syntax_analyzer::F19;
   Control_Table[9][4] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][5] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][6] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][7] = &MINI_BASIC_Syntax_analyzer::F19;
   Control_Table[9][8] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][9] = &MINI_BASIC_Syntax_analyzer::K7;
   Control_Table[9][10] = &MINI_BASIC_Syntax_analyzer::F19;
   Control_Table[9][11] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][12] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][13] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][14] = &MINI_BASIC_Syntax_analyzer::F19;
   Control_Table[9][15] = &MINI_BASIC_Syntax_analyzer::F19;
   Control_Table[9][16] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][17] = &MINI_BASIC_Syntax_analyzer::F17;
   Control_Table[9][18] = &MINI_BASIC_Syntax_analyzer::F18;
   Control_Table[9][19] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][20] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][21] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][22] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[9][23] = &MINI_BASIC_Syntax_analyzer::O;

   //<T-список>
   Control_Table[10][1] = &MINI_BASIC_Syntax_analyzer::F23;
   Control_Table[10][2] = &MINI_BASIC_Syntax_analyzer::K7;
   Control_Table[10][3] = &MINI_BASIC_Syntax_analyzer::F23;
   Control_Table[10][4] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[10][5] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[10][6] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[10][7] = &MINI_BASIC_Syntax_analyzer::F23;
   Control_Table[10][8] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[10][9] = &MINI_BASIC_Syntax_analyzer::K7;
   Control_Table[10][10] = &MINI_BASIC_Syntax_analyzer::F23;
   Control_Table[10][11] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[10][12] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[10][13] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[10][14] = &MINI_BASIC_Syntax_analyzer::F23;
   Control_Table[10][15] = &MINI_BASIC_Syntax_analyzer::F23;
   Control_Table[10][16] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[10][17] = &MINI_BASIC_Syntax_analyzer::F23;
   Control_Table[10][18] = &MINI_BASIC_Syntax_analyzer::F23;
   Control_Table[10][19] = &MINI_BASIC_Syntax_analyzer::F21;
   Control_Table[10][20] = &MINI_BASIC_Syntax_analyzer::F22;
   Control_Table[10][21] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[10][22] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[10][23] = &MINI_BASIC_Syntax_analyzer::O;

   //<F-список>
   Control_Table[11][1] = &MINI_BASIC_Syntax_analyzer::F26;
   Control_Table[11][2] = &MINI_BASIC_Syntax_analyzer::K7;
   Control_Table[11][3] = &MINI_BASIC_Syntax_analyzer::F26;
   Control_Table[11][4] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[11][5] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[11][6] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[11][7] = &MINI_BASIC_Syntax_analyzer::F26;
   Control_Table[11][8] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[11][9] = &MINI_BASIC_Syntax_analyzer::K7;
   Control_Table[11][10] = &MINI_BASIC_Syntax_analyzer::F26;
   Control_Table[11][11] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[11][12] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[11][13] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[11][14] = &MINI_BASIC_Syntax_analyzer::F26;
   Control_Table[11][15] = &MINI_BASIC_Syntax_analyzer::F26;
   Control_Table[11][16] = &MINI_BASIC_Syntax_analyzer::K4;
   Control_Table[11][17] = &MINI_BASIC_Syntax_analyzer::F26;
   Control_Table[11][18] = &MINI_BASIC_Syntax_analyzer::F26;
   Control_Table[11][19] = &MINI_BASIC_Syntax_analyzer::F26;
   Control_Table[11][20] = &MINI_BASIC_Syntax_analyzer::F26;
   Control_Table[11][21] = &MINI_BASIC_Syntax_analyzer::F25;
   Control_Table[11][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[11][23] = &MINI_BASIC_Syntax_analyzer::T2;

   //<Отношение>
   Control_Table[12][1] = &MINI_BASIC_Syntax_analyzer::E2;
   Control_Table[12][2] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][3] = &MINI_BASIC_Syntax_analyzer::b;
   Control_Table[12][4] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][5] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][6] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][7] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][8] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][9] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][10] = &MINI_BASIC_Syntax_analyzer::E3;
   Control_Table[12][11] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][12] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][13] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][14] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][15] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][16] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][17] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][18] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][19] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][20] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][21] = &MINI_BASIC_Syntax_analyzer::E1;
   Control_Table[12][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[12][23] = &MINI_BASIC_Syntax_analyzer::T3;

   //<Конец цикла>
   Control_Table[13][1] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][2] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][3] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][4] = &MINI_BASIC_Syntax_analyzer::b;
   Control_Table[13][5] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][6] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][7] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][8] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][9] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][10] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][11] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][12] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][13] = &MINI_BASIC_Syntax_analyzer::L;
   Control_Table[13][14] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][15] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][16] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][17] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][18] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][19] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][20] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][21] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][22] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[13][23] = &MINI_BASIC_Syntax_analyzer::O;

   //<Переход>
   Control_Table[14][1] = &MINI_BASIC_Syntax_analyzer::M2;
   Control_Table[14][2] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][3] = &MINI_BASIC_Syntax_analyzer::M3;
   Control_Table[14][4] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][5] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][6] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][7] = &MINI_BASIC_Syntax_analyzer::b;
   Control_Table[14][8] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][9] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][10] = &MINI_BASIC_Syntax_analyzer::M4;
   Control_Table[14][11] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][12] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][13] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][14] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][15] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][16] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][17] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][18] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][19] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][20] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][21] = &MINI_BASIC_Syntax_analyzer::M1;
   Control_Table[14][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[14][23] = &MINI_BASIC_Syntax_analyzer::T3;

   //<Правая скобка>
   Control_Table[15][1] = &MINI_BASIC_Syntax_analyzer::N2;
   Control_Table[15][2] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][3] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][4] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][5] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][6] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][7] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][8] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][9] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][10] = &MINI_BASIC_Syntax_analyzer::a;
   Control_Table[15][11] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][12] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][13] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][14] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][15] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][16] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][17] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][18] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][19] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][20] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][21] = &MINI_BASIC_Syntax_analyzer::N1;
   Control_Table[15][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[15][23] = &MINI_BASIC_Syntax_analyzer::T3;

   //<Конец>
   Control_Table[16][1] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][2] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][3] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][4] = &MINI_BASIC_Syntax_analyzer::K;
   Control_Table[16][5] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][6] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][7] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][8] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][9] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][10] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][11] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][12] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][13] = &MINI_BASIC_Syntax_analyzer::a;
   Control_Table[16][14] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][15] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][16] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][17] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][18] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][19] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][20] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][21] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][22] = &MINI_BASIC_Syntax_analyzer::O;
   Control_Table[16][23] = &MINI_BASIC_Syntax_analyzer::O;

   //<До>
   Control_Table[17][1] = &MINI_BASIC_Syntax_analyzer::P2;
   Control_Table[17][2] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][3] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][4] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][5] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][6] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][7] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][8] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][9] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][10] = &MINI_BASIC_Syntax_analyzer::P3;
   Control_Table[17][11] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][12] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][13] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][14] = &MINI_BASIC_Syntax_analyzer::a;
   Control_Table[17][15] = &MINI_BASIC_Syntax_analyzer::P4;
   Control_Table[17][16] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][17] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][18] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][19] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][20] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][21] = &MINI_BASIC_Syntax_analyzer::P1;
   Control_Table[17][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[17][23] = &MINI_BASIC_Syntax_analyzer::T3;

   //<@>
   Control_Table[18][1] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][2] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][3] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][4] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][5] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][6] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][7] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][8] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][9] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][10] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][11] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][12] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][13] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][14] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][15] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][16] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][17] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][18] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][19] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][20] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][21] = &MINI_BASIC_Syntax_analyzer::P;
   Control_Table[18][22] = &MINI_BASIC_Syntax_analyzer::C;
   Control_Table[18][23] = &MINI_BASIC_Syntax_analyzer::c;

   for (int i = 1; i < 24; i++)
      Control_Table[19][i] = &MINI_BASIC_Syntax_analyzer::d;

   for (int i = 1; i < 24; i++)
      Control_Table[20][i] = &MINI_BASIC_Syntax_analyzer::e;

   for (int i = 1; i < 24; i++)
      Control_Table[21][i] = &MINI_BASIC_Syntax_analyzer::f;

   for (int i = 1; i < 24; i++)
      Control_Table[22][i] = &MINI_BASIC_Syntax_analyzer::g;

   for (int i = 1; i < 24; i++)
      Control_Table[23][i] = &MINI_BASIC_Syntax_analyzer::h;

   for (int i = 1; i < 24; i++)
      Control_Table[24][i] = &MINI_BASIC_Syntax_analyzer::i;

   for (int i = 1; i < 24; i++)
      Control_Table[25][i] = &MINI_BASIC_Syntax_analyzer::j;

   for (int i = 1; i < 24; i++)
      Control_Table[26][i] = &MINI_BASIC_Syntax_analyzer::k;

   for (int i = 1; i < 24; i++)
      Control_Table[27][i] = &MINI_BASIC_Syntax_analyzer::l;

   for (int i = 1; i < 24; i++)
      Control_Table[28][i] = &MINI_BASIC_Syntax_analyzer::m;

   for (int i = 1; i < 24; i++)
      Control_Table[29][i] = &MINI_BASIC_Syntax_analyzer::n;

   for (int i = 1; i < 24; i++)
      Control_Table[30][i] = &MINI_BASIC_Syntax_analyzer::o;

   for (int i = 1; i < 24; i++)
      Control_Table[31][i] = &MINI_BASIC_Syntax_analyzer::p;

   for (int i = 1; i < 24; i++)
      Control_Table[32][i] = &MINI_BASIC_Syntax_analyzer::q;

   for (int i = 1; i < 24; i++)
      Control_Table[33][i] = &MINI_BASIC_Syntax_analyzer::r;
};
