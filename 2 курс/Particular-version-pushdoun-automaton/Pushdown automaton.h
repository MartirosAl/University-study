#pragma once
#include <iostream>
#include <string>
#include <stack>

using namespace std;

class PDA
{
   void(PDA::* q)(char a);

   stack<char> pd;
   int number_character;
   int flag;
   int state;

   void move()
   {
      number_character++;
   }

   void push(char c)
   {
      pd.push(c);
   }

   void pop()
   {
      pd.pop();
   }

   void pop(int n)
   {
      for (int i = 0; i < n; i++)
         pd.pop();
   }

   void hold()
   {
      ;
   }

   void reject()
   {
      flag = -1;
   }

   void accept()
   {
      flag = 1;
   }

   void move_state(int a)
   {
      state = a;
   }

public:
   PDA()
   {
      pd.push('Z');
      number_character = 0;
      flag = 0;
      state = 0;
   }

   void start(string a_)
   {
      
      while (!flag)
      {
         char c = a_[number_character];
         switch (state)
         {
         case (0):
            switch (c)
            {
            case('0'):
               switch (pd.top())
               {
               case('1'):
                  pop(2);
                  move_state(1);
                  move();
                  break;
               case('Z'):
               default:
                  reject();
               }
               break;
            case('1'):
               switch (pd.top())
               {
               case('1'):
                  push('1');
                  move();
                  break;
               case('Z'):
                  push('1');
                  move();
                  break;
               default:
                  reject();
               }
               break;
            case('2'):
               switch (pd.top())
               {
               case('1'):
                  pop();
                  move_state(2);
                  move();
                  break;
               case('Z'):
               default:
                  reject();
               }
               break;
            case('E'):
               switch (pd.top())
               {
               case('1'):
               case('Z'):
               default:
                  reject();
               }
               break;
            default:
               reject();
            }
            break;
         case (1):
            switch (c)
            {
            case('0'):
               switch (pd.top())
               {
               case('1'):
                  pop(2);
                  move();
                  break;
               case('Z'):
               default:
                  reject();
               }
               break;
            case('1'):
               switch (pd.top())
               {
               case('1'):
               case('Z'):
               default:
                  reject();
               }
               break;
            case('2'):
               switch (pd.top())
               {
               case('1'):
               case('Z'):
               default:
                  reject();
               }
               break;
            case('E'):
               switch (pd.top())
               {
               case('1'):
                  reject();
                  break;
               case('Z'):
                  accept();
                  break;
               default:
                  reject();
               }
               break;
            default:
               reject();
            }
            break;
         case (2):
            switch (c)
            {
            case('0'):
               switch (pd.top())
               {
               case('1'):
               case('Z'):
               default:
                  reject();
               }
               break;
            case('1'):
               switch (pd.top())
               {
               case('1'):
               case('Z'):
               default:
                  reject();
               }
               break;
            case('2'):
               switch (pd.top())
               {
               case('1'):
                  pop();
                  move();
                  break;
               case('Z'):
               default:
                  reject();
               }
               break;
            case('E'):
               switch (pd.top())
               {
               case('1'):
                  reject();
                  break;
               case('Z'):
                  accept();
                  break;
               default:
                  reject();
               }
               break;
            default:
               reject();
            }
            break;
         default:
            reject();
            break;
         }
      }
         

      cout << ((flag==1)? "Accept" : "Reject") << endl;
      return;
   }
};