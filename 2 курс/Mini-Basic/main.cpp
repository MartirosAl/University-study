
#include "Translator_to_assembler.h"
using namespace std;
int main()
{ 
   //string name_file = "Test3.txt";
   //MINI_BASIC_Lexical_analyzer A;
   //A.start_LA(name_file);
   //A.Print_table_tokens();
   //A.Print_table_operands();
   //A.Print_table_labels();
   
   //MINI_BASIC_Syntax_analyzer B;
   //B.test_flag = 1;
   //B.start_SA(name_file);
   //B.PrintTA();
   //B.PrintStk();

   Translator_to_assembler C("Programm.txt");

   C.Generate_assembler_code("Code.asm");



   return 0;
}
