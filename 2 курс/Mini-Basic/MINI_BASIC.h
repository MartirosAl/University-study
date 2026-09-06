#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Tokens.h"
#include "hash_tables.h"
#include "Decimal_fractions.h"



using namespace std; 
class MINI_BASIC
{
   //Файл с ошибками
   std::ofstream error_list;   
   //RSTR
   int number_string_reg = 0;
   //RCH
   long long number_reg = 0; 
   //RZ
   int order_sign_reg = 0;       
   //RP
   int order_reg = 0;        
   //RS
   int counter_reg = 0;
   //RKL
   TokenType lex_class_reg = start;
   //ROT
   int relation_value_reg = 0;
   //RSOS
   int state_reg = 0;
   //ROB
   int detection_reg = 0;
   //RK
   int char_class_value_reg = 0;
   //RI
   int index_reg = 0;

   typedef void(MINI_BASIC::*func) ();
   func q;

   //RZN Текущий символ 
   SymbolicToken character;
   //Текцщее слово
   string word;

   //Поток
   ifstream stream;

   //TS
   Hash_table_internal table_number_string;

   //TO
   vector<long double> table_operands;

   //NTO
   int ptr_to_free = 287;

   //Temp for TO
   Decimal_fractions Dec_number;

   //TL
   vector<Token> table_tokens;

   //Счетчик лексем
   int counter_tokens = 0;

   //Переменная для хэш-таблицы
   int index_cur_number = 0;

   //Флаг для операнда (переменная / константа)
   bool flag_operand = 0;


   SymbolicToken Transliterator(int character);

   void next();

   


   //states

   //начало строки
   void A1();
   //искать перем., конст., опер., СR, (, ), отнош.
   void A2();
   //искать зарезерв. слово, опер., СR, (, ), отнош
   void A3();
   //Обнаружить зарезерв.слово
   void B1();
   //искать переменную
   void C1();
   //завершить обработку переменной
   void C2();
   //завершить обработку целой части
   void D1();
   //завершить обработку дробной части
   void D2();
   //после буквы Е
   void D3();
   //после буквы Е и знака
   void D4();
   //завершить обработку порядка
   void D5();
   //после первой десятичной точки
   void D6();
   //искать номер строки
   void E1();
   //оставшаяся часть номера строки
   void E2();
   //искать переменную и =
   void F1();
   //оставшаяся часть переменной
   void F2();
   //искать =
   void F3();
   //найти СR (комментарий)
   void G1();
   //завершить обработку отношения
   void H1();

   void Error();

   //Процедуры

   void DA1D();
   void DA2D();
   void DA3D();
   void DA1E();


   void A1a();
   void A1b();
   void A1c();
   void A1d();
   void A1e();

   void A2a(); 
   void A2b(); 
   void A2c(); 
   void A2d(); 
   void A2e(); 
   void A2f(); 
   void A2g(); 
   void A2h(); 
   void A2j(); 
   void A2k(); 
   void A2l(); 
   void A2m(); 
   void A2n(); 
   void A2o(); 
   void A2p(); 
   void A2q(); 
   void A2r(); 
   void A2s(); 
   void A2t(); 
   void A2u(); 
   
   void A3a();
   void A3b();
   void A3c();
   void A3d();
   void A3e();
   void A3f();
   void A3g();

   void B1a();
   void B1b();
   void B1c();
   void B1d();
   void B1e();

   void C1a();

   void C2a();
   void C2b();
   void C2d();

   void D1a();
   void D1b();
   void D1c();
   
   void D2a();
   void D2b();
   void D2c();

   void D3a();

   void D4a();
   
   void D5a();
   void D5b();
   void D5c();

   void D6a();

   void E1a();
   void E1b();

   void E2a();
   void E2b();
   void E2c();

   void F1a();
   void F1b();

   void F2a();

   void F3a();

   void G1a();

   void H1a();
   void H1b();
   void H1c();
   void H1d();
   void H1e();
   void H1f();

   void M1();
   void M2();
   void M3();

   void EXIT1();
   void EXIT2();
   void EXIT3();
   void EXIT4();
   void EXIT5();
   void EXIT6();

   void Create_Token();

   void Error_Handler();


   struct Keyword{
      int letter;
      func f;
      int alt;
   };

   vector<int> table_first_vector
   {
      /*0*/-1,
      /*A*/0,
      /*B*/0,
      /*C*/0,
      /*D*/0,
      /*E*/1,
      /*F*/3,
      /*G*/5,
      /*H*/0,
      /*I*/11,
      /*J*/0,
      /*K*/0,
      /*L*/12,
      /*M*/0,
      /*N*/14,
      /*O*/0,
      /*P*/0,
      /*Q*/0,
      /*R*/17,
      /*S*/23,
      /*T*/26,
      /*U*/0,
      /*V*/0,
      /*W*/0,
      /*X*/0,
      /*Y*/0,
      /*Z*/0
   };

   vector<Keyword> table_detection
   {
      /**0*/{-1, &MINI_BASIC::A1a, -2},
      /**1*/{14, &MINI_BASIC::B1d, -1},//END
      /**2*/{4,  &MINI_BASIC::A2q, -1},//END
      /**3*/{15, &MINI_BASIC::B1d, -1},//FOR
      /**4*/{18, &MINI_BASIC::F1b, -1},//FOR
      /**5*/{15, &MINI_BASIC::B1d, -1},//GOTO, GOSUB
      /**6*/{20, &MINI_BASIC::B1d,  8},//GOTO 
      /**7*/{15, &MINI_BASIC::E1a, -1},//GOSUB
      /**8*/{19, &MINI_BASIC::B1d, -1},//GOSUB
      /**9*/{21, &MINI_BASIC::B1d, -1},//GOSUB
      /*10*/{2,  &MINI_BASIC::E1b, -1},//GOSUB
      /*11*/{6,  &MINI_BASIC::A2r, -1},//IF
      /*12*/{5,  &MINI_BASIC::B1d, -1},//LET
      /*13*/{20, &MINI_BASIC::F1a, -1},//LET
      /*14*/{5,  &MINI_BASIC::B1d, -1},//NEXT
      /*15*/{24, &MINI_BASIC::B1d, -1},//NEXT
      /*16*/{20, &MINI_BASIC::C1a, -1},//NEXT
      /*17*/{5,  &MINI_BASIC::B1d, -1},//RETURN, REM
      /*18*/{20, &MINI_BASIC::B1d, 22},//RETURN
      /*19*/{21, &MINI_BASIC::B1d, -1},//RETURN
      /*20*/{18, &MINI_BASIC::B1d, -1},//RETURN
      /*21*/{14, &MINI_BASIC::A2s, -1},//RETURN
      /*22*/{13, &MINI_BASIC::G1a, -1},//REM
      /*23*/{20, &MINI_BASIC::B1d, -1},//STEP
      /*24*/{5,  &MINI_BASIC::B1d, -1},//STEP
      /*25*/{16, &MINI_BASIC::A2t, -1},//STEP
      /*26*/{15, &MINI_BASIC::A2u, -1},//TO
   };


public:

   MINI_BASIC(string name_file);

   void Print_table_tokens();

   void Print_table_operands();

   void Print_table_labels();

};

