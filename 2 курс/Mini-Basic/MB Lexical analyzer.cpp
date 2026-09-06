#pragma once
#include "MB Lexical analyzer.h"


SymbolicToken MINI_BASIC_Lexical_analyzer::Transliterator(int character)
{
	SymbolicToken result;
	result.value = 0;
	if (character >= 'A' && character <= 'Z')
	{
		result.token_class = SymbolicTokenType::LETTER_S;
		result.value = character - 'A' + 1;
	}
	else if (character >= 'a' && character <= 'z')
	{
	   result.token_class = SymbolicTokenType::LETTER_S;
	   result.value = character - 'a' + 1;
	}
	else if (character >= '0' && character <= '9')
	{
		result.token_class = SymbolicTokenType::DIGIT_S;
		result.value = character - '0';
	}
	else if (character == '+')
	{
		result.token_class = SymbolicTokenType::ARITHMETIC_OPERATION_S;
		result.value = 1;
	}    
	else if (character == '-')
	{
		result.token_class = SymbolicTokenType::ARITHMETIC_OPERATION_S;
		result.value = 2;
	}    
	else if (character == '*')
	{
		result.token_class = SymbolicTokenType::ARITHMETIC_OPERATION_S;
		result.value = 3;
	}    
	else if (character == '/')
	{
		result.token_class = SymbolicTokenType::ARITHMETIC_OPERATION_S;
		result.value = 4;
	}    
	else if (character == '^')
	{
		result.token_class = SymbolicTokenType::ARITHMETIC_OPERATION_S;
		result.value = 5;
	}
	else if (character == '=')
	{
		result.token_class = SymbolicTokenType::RELATION_S;
		result.value = 1;
	}
	else if (character == '<')
	{
	   result.token_class = SymbolicTokenType::RELATION_S;
	   result.value = 2;
	}
	else if (character == '>')
	{
	   result.token_class = SymbolicTokenType::RELATION_S;
	   result.value = 3;
	}
	else if (character == '(')
	{
		result.token_class = SymbolicTokenType::O_BRACE_S;
		result.value = (int)character;
	}
	else if (character == ')')
	{
		result.token_class = SymbolicTokenType::C_BRACE_S;
		result.value = (int)character;
	}
	else if (character == '.')
	{
	   result.token_class = SymbolicTokenType::DOT_S;
	   result.value = (int)character;
	}
	else if (character == ' ' || character == '\t')
	{
		result.token_class = SymbolicTokenType::SPACE_S;
		result.value = (int)character;
	}
	else if (character == '\n')
	{
		result.token_class = SymbolicTokenType::LF_S;
		result.value = (int)character;
	}
	else if (character == EOF)
	{
		result.token_class = SymbolicTokenType::END_OF_FILE_S;
		result.value = (int)character;
	}
	else
	{
		result.token_class = SymbolicTokenType::ERROR_S;
		result.value = (int)character;
	}
	return result;
}

void MINI_BASIC_Lexical_analyzer::next()
{
   character = Transliterator(stream.get());
}

MINI_BASIC_Lexical_analyzer::MINI_BASIC_Lexical_analyzer()
{
	;
}

void MINI_BASIC_Lexical_analyzer::start_LA(string name_file)
{
   stream.open(name_file);
   if (!stream)
   {
	  cout << "Couldn't open the file " << name_file << endl;
	  return;
   }

   //Tests flags
   bool flag_work_state = false;

   //Initial state
   q = &MINI_BASIC_Lexical_analyzer::A1;
   next();

   //Initial table operands
   table_operands.assign(287, 0);

   func prev_func = q;

   while (true)
   {
	  if (flag_work_state)
		 cout << character.value << endl;
	  (this->*q)();
	  if (q == &MINI_BASIC_Lexical_analyzer::Error)
		 break;


	  if (q == &MINI_BASIC_Lexical_analyzer::EXIT1 || q == &MINI_BASIC_Lexical_analyzer::EXIT2 || q == &MINI_BASIC_Lexical_analyzer::EXIT3 || q == &MINI_BASIC_Lexical_analyzer::EXIT4 || q == &MINI_BASIC_Lexical_analyzer::EXIT5 || q == &MINI_BASIC_Lexical_analyzer::EXIT6)
	  {
		 if (table_number_string.error_finder())
		 {
			flag_error = 1;
			cout << "Error in labels" << endl;
		 }
		 break;
	  }

   }

   Write_table_tokens();
   Write_table_operands();
   Write_table_labels();
   stream.close();
}

void MINI_BASIC_Lexical_analyzer::Print_table_tokens()
{
   for (int i = 0; i < table_tokens.size(); i++)
   {
	  cout << "---------------------------------------" << endl;
	  cout << TokenTypeString[table_tokens[i].type] << " ";
	  switch (table_tokens[i].type)
	  {

	  case LABLE_T:
		 cout << table_number_string[table_tokens[i].value];
		 break;

	  case OPERAND_T:
	  case LET_T:
	  case FOR_T:
	  case NEXT_T:
		 if (table_tokens[i].value <= 286)
			cout << (char)((table_tokens[i].value % 26) + 'A' - 1) << (((table_tokens[i].value / 26) == 0) ? ' ' : (char)(table_tokens[i].value / 26 + '0' - 1));
		 else
			cout << table_operands[table_tokens[i].value];
		 break;

	  case GOTO_T:
	  case GOSUB_T:
		 cout << table_number_string[table_tokens[i].value];
		 break;

	  case RELATIONSHIP_OPERATIONS_T:
		 switch (table_tokens[i].value)
		 {
		 case(1):
			cout << '=';
			break;
		 case(2):
			cout << '<';
			break;
		 case(3):
			cout << '>';
			break;
		 case(4):
			cout << "<=";
			break;
		 case(5):
			cout << ">=";
			break;
		 case(6):
			cout << "<>";
			break;
		 }
		 break;
	  case ARITHMETIC_OPERATIONS_T:
		 switch (table_tokens[i].value)
		 {
		 case(1):
			 cout << '+';
			 break;
		 case(2):
			 cout << '-';
			 break;
		 case(3):
			 cout << '*';
			 break;
		 case(4):
			 cout << '/';
			 break;
		 case(5):
			 cout << '^';
			 break;
		 }
		 break;
	  case L_BRACKET_T:
		 cout << '(';
		 break;
	  case R_BRACKET_T:
		 cout << ')';
		 break;
	  case IF_T:
	  case RETURN_T:
	  case END_T:
	  case TO_T:
	  case STEP_T:
	  case REM_T:
	  case ERROR_T:
	  case END_OF_FILE_T:
		 ;
		 break;
	  }
	  cout << endl;
   }
   cout << "---------------------------------------" << endl;
}

void MINI_BASIC_Lexical_analyzer::Write_table_tokens()
{
	ofstream file("Tokens.txt");	
	if (!file.is_open())
	{
		cout << "Error opening file Labels.txt" << endl;
		return;
	}
	file.clear();
	for (int i = 0; i < table_tokens.size(); i++)
	{
		file << "---------------------------------------" << endl;
		file << TokenTypeString[table_tokens[i].type] << " ";
		switch (table_tokens[i].type)
		{

		case LABLE_T:
			file << table_number_string[table_tokens[i].value];
			break;

		case OPERAND_T:
		case LET_T:
		case FOR_T:
		case NEXT_T:
			if (table_tokens[i].value <= 286)
				file << (char)((table_tokens[i].value % 26) + 'A' - 1) << (((table_tokens[i].value / 26) == 0) ? ' ' : (char)(table_tokens[i].value / 26 + '0' - 1));
			else
				file << table_operands[table_tokens[i].value];
			break;

		case GOTO_T:
		case GOSUB_T:
			file << table_number_string[table_tokens[i].value];
			break;

		case RELATIONSHIP_OPERATIONS_T:
			switch (table_tokens[i].value)
			{
			case(1):
				file << '=';
				break;
			case(2):
				file << '<';
				break;
			case(3):
				file << '>';
				break;
			case(4):
				file << "<=";
				break;
			case(5):
				file << ">=";
				break;
			case(6):
				file << "<>";
				break;
			}
			break;
		case ARITHMETIC_OPERATIONS_T:
			switch (table_tokens[i].value)
			{
			case(1):
				file << '+';
				break;
			case(2):
				file << '-';
				break;
			case(3):
				file << '*';
				break;
			case(4):
				file << '/';
				break;
			case(5):
				file << '^';
				break;
			}
			break;
		case L_BRACKET_T:
			file << '(';
			break;
		case R_BRACKET_T:
			file << ')';
			break;
		case IF_T:
		case RETURN_T:
		case END_T:
		case TO_T:
		case STEP_T:
		case REM_T:
		case ERROR_T:
		case END_OF_FILE_T:
			;
			break;
		}
		file << endl;
	}
	file << "---------------------------------------" << endl;
	file.close();
}

void MINI_BASIC_Lexical_analyzer::Print_table_operands()
{
   cout << "--------------------------" << endl;
   for (int i = 0; i < table_operands.size(); i++)
   {
	   int j = i;
	   if (j <= 26 && table_operands[j] == 1)
		   cout << j << "\t | " << (char)((j % 27) + 'A' - 1) << "\t\t | " << endl;
	   else if (j <= 286 && table_operands[j] == 1)
	   {
		   cout << j << "\t | ";
		   if (j % 26 == 0)
		   {
			   cout << "Z";
			   j /= 26;
			   cout << j % 26 - 2 << "\t\t | " << endl;
		   }
		   else
		   {
			   cout << (char)((j % 26) + 'A' - 1);

			   j /= 26;
			   cout << j % 26 - 1 << "\t\t | " << endl;
		   }
	   }
	   else if (j > 286)
		   cout << j << "\t | " << j << "\t\t | " << endl;
   }
   cout << "--------------------------" << endl;
}

void MINI_BASIC_Lexical_analyzer::Write_table_operands()
{
	ofstream file("Operands.txt");
	if (!file.is_open())
	{
		cout << "Error opening file Labels.txt" << endl;
		return;
	}
	file.clear();
	file << "--------------------------" << endl;
	for (int i = 0; i < table_operands.size(); i++)
	{
		int j = i;
		if (j <= 26 && table_operands[j] == 1)
			file << j << "\t | " << (char)((j % 27) + 'A' - 1) << "\t\t | " << endl;
		else if (j <= 286 && table_operands[j] == 1)
		{
			file << j << "\t | ";
			if (j % 26 == 0)
			{
				file << "Z";
				j /= 26;
				file << j % 26 - 2 << "\t\t | " << endl;
			}
			else
			{
				file << (char)((j % 26) + 'A' - 1);

				j /= 26;
				file << j % 26 - 1 << "\t\t | " << endl;
			}
		}
		else if (j > 286)
			file << j << "\t | " << table_operands[j] << "\t\t | " << endl;
	}
	file << "--------------------------" << endl;
	file.close();
}

void MINI_BASIC_Lexical_analyzer::Print_table_labels()
{
   table_number_string.Print();
}

void MINI_BASIC_Lexical_analyzer::Write_table_labels()
{
	ofstream file ("Labels.txt");
	if (!file.is_open())
	{
		cout << "Error opening file Labels.txt" << endl;
		return;
	}
	file.clear();
	table_number_string.Write(file);
	file.close();
}

//начало строки
void MINI_BASIC_Lexical_analyzer::A1()
{
   switch (character.token_class)
   {
   case DIGIT_S:
	  E2a();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::A1;
	  break;
   case LF_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::A1;
	  break;
   case END_OF_FILE_S:
	  EXIT1();
	  break;
   default:
	  Error();
	  break;
   }
}

//искать перем., конст., опер., СR, (, ), отнош.
void MINI_BASIC_Lexical_analyzer::A2()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  C2a();
	  break;
   case DIGIT_S:
	  D1a();
	  break;
   case ARITHMETIC_OPERATION_S:
	  A2a();
	  break;
   case RELATION_S:
	  H1a();
	  break;
   case O_BRACE_S:
	  A2h();
	  break;
   case C_BRACE_S:
	  A3b();
	  break;
   case DOT_S:
	  q = &MINI_BASIC_Lexical_analyzer::D6;
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::A2;
	  break;
   case LF_S:
	  q = &MINI_BASIC_Lexical_analyzer::A1;
	  break;
   case END_OF_FILE_S:
	  EXIT1();
	  break;
   default:
	  Error();
	  break;
   }
}

//искать зарезерв. слово, опер., СR, (, ), отнош
void MINI_BASIC_Lexical_analyzer::A3()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  B1a();
	  break;
   case DIGIT_S:
	  D1a();
	  break;
   case ARITHMETIC_OPERATION_S:
	  A2a();
	  break;
   case RELATION_S:
	  H1a();
	  break;
   case O_BRACE_S:
	  A2h();
	  break;
   case C_BRACE_S:
	  A3b();
	  break;
   case DOT_S:
	  q = &MINI_BASIC_Lexical_analyzer::D6;
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::A3;
	  break;
   case LF_S:
	  q = &MINI_BASIC_Lexical_analyzer::A1;
	  break;
   case END_OF_FILE_S:
	  EXIT1();
	  break;
   default:
	  Error();
	  break;
   }
}

//Обнаружить зарезерв.слово
void MINI_BASIC_Lexical_analyzer::B1()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  M1();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::B1;
	  break;
   default:
	  Error();
	  break;
   }
}

//искать переменную
void MINI_BASIC_Lexical_analyzer::C1()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  C2d();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::C1;
	  break;
   case END_OF_FILE_S:
	  EXIT3();
	  break;
   default:
	  Error();
	  break;
   }
}

//завершить обработку переменной
void MINI_BASIC_Lexical_analyzer::C2()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  B1b();
	  break;
   case DIGIT_S:
	  A3a();
	  break;
   case ARITHMETIC_OPERATION_S:
	  A2g();
	  break;
   case RELATION_S:
	  H1b();
	  break;
   case O_BRACE_S:
	  A2k();
	  break;
   case C_BRACE_S:
	  A3c();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::C2;
	  break;
   case LF_S:
	  A1a();
	  break;
   case END_OF_FILE_S:
	  EXIT4();
	  break;
   default:
	  Error();
	  break;
   }
}

//завершить обработку целой части
void MINI_BASIC_Lexical_analyzer::D1()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  M2();
	  break;
   case DIGIT_S:
	  D1b();
	  break;
   case ARITHMETIC_OPERATION_S:
	  A2c();
	  break;
   case RELATION_S:
	  H1c();
	  break;
   case O_BRACE_S:
	  A2l();
	  break;
   case C_BRACE_S:
	  A3d();
	  break;
   case DOT_S:
	  D2c();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::D1;
	  break;
   case LF_S:
	  A1b();
	  break;
   case END_OF_FILE_S:
	  EXIT3();
	  break;
   default:
	  Error();
	  break;
   }
}

//завершить обработку дробной части
void MINI_BASIC_Lexical_analyzer::D2()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  M3();
	  break;
   case DIGIT_S:
	  D2a();
	  break;
   case ARITHMETIC_OPERATION_S:
	  A2d();
	  break;
   case RELATION_S:
	  H1d();
	  break;
   case O_BRACE_S:
	  A2m();
	  break;
   case C_BRACE_S:
	  A3e();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::D2;
	  break;
   case LF_S:
	  A1c();
	  break;
   case END_OF_FILE_S:
	  EXIT4();
	  break;
   default:
	  Error();
	  break;
   }
}

//после буквы Е
void MINI_BASIC_Lexical_analyzer::D3()
{
   switch (character.token_class)
   {
   case DIGIT_S:
	  D5a();
	  break;
   case ARITHMETIC_OPERATION_S:
	  D4a();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::D3;
	  break;
   default:
	  Error();
	  break;
   }
}

//после буквы Е и знака
void MINI_BASIC_Lexical_analyzer::D4()
{
   switch (character.token_class)
   {
   case DIGIT_S:
	  D2b();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::D4;
	  break;
   default:
	  Error();
	  break;
   }
}

//завершить обработку порядка
void MINI_BASIC_Lexical_analyzer::D5()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  B1c();
	  break;
   case DIGIT_S:
	  D5c();
	  break;
   case ARITHMETIC_OPERATION_S:
	  A2e();
	  break;
   case RELATION_S:
	  H1c();
	  break;
   case O_BRACE_S:
	  A2n();
	  break;
   case C_BRACE_S:
	  A3f();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::D5;
	  break;
   case LF_S:
	  A1d();
	  break;
   case END_OF_FILE_S:
	  EXIT5();
	  break;
   default:
	  Error();
	  break;
   }
}

//после первой десятичной точки
void MINI_BASIC_Lexical_analyzer::D6()
{
   switch (character.token_class)
   {
   case DIGIT_S:
	  D2b();
	  break;
   case SPACE_S:
	  lex_class_reg = OPERAND_T;
	  flag_operand = 1;
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::D6;
	  break;
   default:
	  Error();
	  break;
   }
}

//искать номер строки
void MINI_BASIC_Lexical_analyzer::E1()
{
   switch (character.token_class)
   {
   case DIGIT_S:
	  E2b();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::E1;
	  break;
   default:
	  Error();
	  break;
   }
}

//оставшаяся часть номера строки
void MINI_BASIC_Lexical_analyzer::E2()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  B1e();
	  break;
   case DIGIT_S:
	  E2c();
	  break;
   case ARITHMETIC_OPERATION_S:
	  A2f();
	  break;
   case RELATION_S:
	  H1f();
	  break;
   case O_BRACE_S:
	  A2j();
	  break;
   case C_BRACE_S:
	  A3g();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::E2;
	  break;
   case LF_S:
	  A1e();
	  break;
   case END_OF_FILE_S:
	  EXIT6();
	  break;
   default:
	  Error();
	  break;
   }
}

//искать переменную и =
void MINI_BASIC_Lexical_analyzer::F1()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  F2a();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::F1;
	  break;
   default:
	  Error();
	  break;
   }
}

//оставшаяся часть переменной
void MINI_BASIC_Lexical_analyzer::F2()
{
   switch (character.token_class)
   {
   case DIGIT_S:
	  F3a();
	  break;
   case RELATION_S:
	  A2o();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::F2;
	  break;
   default:
	  Error();
	  break;
   }
}

//искать =
void MINI_BASIC_Lexical_analyzer::F3()
{
   switch (character.token_class)
   {
   case RELATION_S:
	  A2o();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::F3;
	  break;
   default:
	  Error();
	  break;
   }
}

//найти СR (комментарий)
void MINI_BASIC_Lexical_analyzer::G1()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::G1;
	  break;
   case DIGIT_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::G1;
	  break;
   case ARITHMETIC_OPERATION_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::G1;
	  break;
   case RELATION_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::G1;
	  break;
   case O_BRACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::G1;
	  break;
   case C_BRACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::G1;
	  break;
   case DOT_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::G1;
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::G1;
	  break;
   case LF_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::A1;
	  break;
   case END_OF_FILE_S:
	  EXIT1();
	  break;
   default:
	  next();
	  break;
   }
}

//завершить обработку отношения
void MINI_BASIC_Lexical_analyzer::H1()
{
   switch (character.token_class)
   {
   case LETTER_S:
	  C2b();
	  break;
   case DIGIT_S:
	  D1c();
	  break;
   case ARITHMETIC_OPERATION_S:
	  A2g();
	  break;
   case RELATION_S:
	  A2p();
	  break;
   case O_BRACE_S:
	  A2k();
	  break;
   case C_BRACE_S:
	  A3c();
	  break;
   case DOT_S:
	  D6a();
	  break;
   case SPACE_S:
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::H1;
	  break;
   case LF_S:
	  A1a();
	  break;
   case END_OF_FILE_S:
	  EXIT1();
	  break;
   default:
	  Error();
	  break;
   }
}

void MINI_BASIC_Lexical_analyzer::DA1D()
{
   order_reg = 0;

   table_operands.push_back(number_reg);
   ptr_to_free++;
   
}

void MINI_BASIC_Lexical_analyzer::DA2D()
{

	string temp;
	if (to_string(number_reg).length() - counter_reg <= 0)
	{
	   temp = "0.";

	   for (int i = 0; i < abs((int)to_string(number_reg).length() - counter_reg) - 1; i++)
		  temp += '0';
	   table_operands.push_back(stold(temp + to_string(number_reg)));

	}
	else
	{
	   temp = to_string(number_reg);
	   reverse(temp.begin(), temp.end());


	   number_reg /= pow(10, counter_reg);

	   temp.resize(counter_reg);
	   reverse(temp.begin(), temp.end());

	   table_operands.push_back(stold(to_string(number_reg) + '.' + temp));
	}
	ptr_to_free++;

}

void MINI_BASIC_Lexical_analyzer::DA3D()
{
	if (order_reg == -1)
	{
		order_reg = -order_reg;
	}

	counter_reg -= order_reg;
	string temp = "\0";
	if (counter_reg > 0)
	{
	   DA2D();
	}
	else
	{

	   for (int i = 0; i < abs(counter_reg); i++)
		  temp += '0';
	   table_operands.push_back(stold(to_string(number_reg) + temp));
	   ptr_to_free++;
	}

}

void MINI_BASIC_Lexical_analyzer::DA1E()
{
   if (table_number_string.find_and_return_index(number_string_reg) != -1 && lex_class_reg == LABLE_T)
	  Error_Handler("There is already such a label.");
   else
	  index_cur_number = table_number_string.insert(number_string_reg);
}


void MINI_BASIC_Lexical_analyzer::A1a()
{
	Create_Token();
	next();
	q = &MINI_BASIC_Lexical_analyzer::A1;
}

void MINI_BASIC_Lexical_analyzer::A1b()
{
	DA1D();
	A1a();
	q = &MINI_BASIC_Lexical_analyzer::A1;
}

void MINI_BASIC_Lexical_analyzer::A1c()
{
	DA2D();
	A1a();
	q = &MINI_BASIC_Lexical_analyzer::A1;
}

void MINI_BASIC_Lexical_analyzer::A1d()
{
	DA3D();
	A1a();
	q = &MINI_BASIC_Lexical_analyzer::A1;
}

void MINI_BASIC_Lexical_analyzer::A1e()
{
	DA1E();
	A1a();
	q = &MINI_BASIC_Lexical_analyzer::A1;
}

void MINI_BASIC_Lexical_analyzer::A2a()
{
	lex_class_reg = ARITHMETIC_OPERATIONS_T;
	A2b();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2b()
{
	Create_Token();
	next();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2c()
{
	DA1D();
	A2g();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2d()
{
	DA2D();
	A2g();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2e()
{
	DA3D();
	A2g();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2f()
{
	DA1E();
	A2g();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2g()
{
	Create_Token();
	A2a();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2h()
{
	lex_class_reg = L_BRACKET_T;
	Create_Token();
	next();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2j()
{
	DA1E();
	A2k();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2k()
{
	Create_Token();
	A2h();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2l()
{
	DA1D();
	A2k();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2m()
{
	DA2D();
	A2k();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2n()
{
	DA3D();
	A2k();
	q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2o()
{
   if (character.value == 1)
	  A2b();
   else
   {
	  Error_Handler();
	  return;
   }
   q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2p()
{
   switch (relation_value_reg)
   {
   case 1:
	  Error_Handler();
	  break;
   case 2:
	  if (character.value == 1/* = */)
		 relation_value_reg = 4;
	  else if (character.value == 3/* > */)
		 relation_value_reg = 6;
	  else
		 Error_Handler();
	  break;
   case 3:
	  if (character.value == 1/* = */)
		 relation_value_reg = 5;
	  else
		 Error_Handler();
	  break;
   default:
	   Error_Handler();
   }
   A2b();
   q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2q()
{
   lex_class_reg = END_T;
   A2b();
   q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2r()
{
   lex_class_reg = IF_T;
   A2b();
   q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2s()
{
   lex_class_reg = RETURN_T;
   A2b();
   q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2t()
{
   lex_class_reg = STEP_T;
   A2b();
   q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A2u()
{
   lex_class_reg = TO_T;
   A2b();
   q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A3a()
{
   //имя переменой
   index_reg += (character.value + 1) * 26;
   Create_Token();
   next();
   q = &MINI_BASIC_Lexical_analyzer::A2;
}

void MINI_BASIC_Lexical_analyzer::A3b()
{
   lex_class_reg = R_BRACKET_T;
   Create_Token();
   next();
   q = &MINI_BASIC_Lexical_analyzer::A3;
}

void MINI_BASIC_Lexical_analyzer::A3c()
{
   Create_Token();
   A3b();
   q = &MINI_BASIC_Lexical_analyzer::A3;
}

void MINI_BASIC_Lexical_analyzer::A3d()
{
   DA1D();
   A3c();
   q = &MINI_BASIC_Lexical_analyzer::A3;
}

void MINI_BASIC_Lexical_analyzer::A3e()
{
   DA2D();
   A3c();
   q = &MINI_BASIC_Lexical_analyzer::A3;
}

void MINI_BASIC_Lexical_analyzer::A3f()
{
   DA3D();
   A3c();
   q = &MINI_BASIC_Lexical_analyzer::A3;
}

void MINI_BASIC_Lexical_analyzer::A3g()
{
   DA1E();
   A3c();
   q = &MINI_BASIC_Lexical_analyzer::A3;
}

void MINI_BASIC_Lexical_analyzer::B1a()
{
   detection_reg = table_first_vector[character.value];
   next();
   q = &MINI_BASIC_Lexical_analyzer::B1;
}

void MINI_BASIC_Lexical_analyzer::B1b()
{
   Create_Token();
   B1a();
   q = &MINI_BASIC_Lexical_analyzer::B1;
}

void MINI_BASIC_Lexical_analyzer::B1c()
{
   DA3D();
   B1b();
   q = &MINI_BASIC_Lexical_analyzer::B1;
}

void MINI_BASIC_Lexical_analyzer::B1d()
{
   detection_reg++;
   next();
   q = &MINI_BASIC_Lexical_analyzer::B1;
}

void MINI_BASIC_Lexical_analyzer::B1e()
{
   DA1E();
   B1b();
   q = &MINI_BASIC_Lexical_analyzer::B1;
}

void MINI_BASIC_Lexical_analyzer::C1a()
{
   lex_class_reg = NEXT_T;
   next();
   q = &MINI_BASIC_Lexical_analyzer::C1;
}

void MINI_BASIC_Lexical_analyzer::C2a()
{
   lex_class_reg = OPERAND_T;
   flag_operand = 0;
   C2d();
   q = &MINI_BASIC_Lexical_analyzer::C2;
}

void MINI_BASIC_Lexical_analyzer::C2b()
{
   Create_Token();
   C2a();
   q = &MINI_BASIC_Lexical_analyzer::C2;
}

void MINI_BASIC_Lexical_analyzer::C2d()
{
   index_reg = character.value;
   next();
   q = &MINI_BASIC_Lexical_analyzer::C2;
}

void MINI_BASIC_Lexical_analyzer::D1a()
{
   lex_class_reg = OPERAND_T;
   number_reg = character.value;
   flag_operand = 1;
   next();
   q = &MINI_BASIC_Lexical_analyzer::D1;
}

void MINI_BASIC_Lexical_analyzer::D1b()
{
   number_reg *= 10;
   number_reg += character.value;
   next();
   q = &MINI_BASIC_Lexical_analyzer::D1;
}

void MINI_BASIC_Lexical_analyzer::D1c()
{
   Create_Token();
   D1a();
   q = &MINI_BASIC_Lexical_analyzer::D1;
}

void MINI_BASIC_Lexical_analyzer::D2a()
{
   counter_reg += 1;
   number_reg *= 10;
   number_reg += character.value;
   next();
   q = &MINI_BASIC_Lexical_analyzer::D2;
}

//🔥🔥🔥🔥🔥🔥🧯
void MINI_BASIC_Lexical_analyzer::D2b()
{
   counter_reg = 1;
   number_reg = character.value;
   next();
   q = &MINI_BASIC_Lexical_analyzer::D2;
}

void MINI_BASIC_Lexical_analyzer::D2c()
{
   counter_reg = 0;
   next();
   q = &MINI_BASIC_Lexical_analyzer::D2;
}

void MINI_BASIC_Lexical_analyzer::D3a()
{
   counter_reg = 0;
   next();
   q = &MINI_BASIC_Lexical_analyzer::D3;
}

void MINI_BASIC_Lexical_analyzer::D4a()
{
   if (character.value == 1)
	  order_sign_reg = 1;
   else if (character.value == 2)
	  order_sign_reg = -1;
   else
	  Error_Handler();
   next();
   q = &MINI_BASIC_Lexical_analyzer::D4;
}

void MINI_BASIC_Lexical_analyzer::D5a()
{
   char_class_value_reg = +1;
   D5b();
   q = &MINI_BASIC_Lexical_analyzer::D5;
}

void MINI_BASIC_Lexical_analyzer::D5b()
{
   order_reg = character.value;
   next();
   q = &MINI_BASIC_Lexical_analyzer::D5;
}

void MINI_BASIC_Lexical_analyzer::D5c()
{
   order_reg *= 10;
   order_reg = character.value;
   next();
   q = &MINI_BASIC_Lexical_analyzer::D5;
}

void MINI_BASIC_Lexical_analyzer::D6a()
{
   Create_Token();
   lex_class_reg = OPERAND_T;
   flag_operand = 1;
   next();
   q = &MINI_BASIC_Lexical_analyzer::D6;
}

void MINI_BASIC_Lexical_analyzer::E1a()
{
   lex_class_reg = GOTO_T;
   next();
   q = &MINI_BASIC_Lexical_analyzer::E1;
}

void MINI_BASIC_Lexical_analyzer::E1b()
{
   lex_class_reg = GOSUB_T;
   next();
   q = &MINI_BASIC_Lexical_analyzer::E1;
}

void MINI_BASIC_Lexical_analyzer::E2a()
{
   lex_class_reg = LABLE_T;
   E2b();
   q = &MINI_BASIC_Lexical_analyzer::E2;
}

void MINI_BASIC_Lexical_analyzer::E2b()
{
   number_string_reg = character.value;
   next();
   q = &MINI_BASIC_Lexical_analyzer::E2;
}

void MINI_BASIC_Lexical_analyzer::E2c()
{
   number_string_reg *= 10;
   number_string_reg += character.value;
   next();
   q = &MINI_BASIC_Lexical_analyzer::E2;
}

void MINI_BASIC_Lexical_analyzer::F1a()
{
   lex_class_reg = LET_T;
   next();
   q = &MINI_BASIC_Lexical_analyzer::F1;
}

void MINI_BASIC_Lexical_analyzer::F1b()
{
   lex_class_reg = FOR_T;
   next();
   q = &MINI_BASIC_Lexical_analyzer::F1;
}

void MINI_BASIC_Lexical_analyzer::F2a()
{
   index_reg = character.value;
   next();
   q = &MINI_BASIC_Lexical_analyzer::F2;
}

void MINI_BASIC_Lexical_analyzer::F3a()
{
   index_reg += (character.value + 1) * 26;
   next();
   q = &MINI_BASIC_Lexical_analyzer::F3;
}

void MINI_BASIC_Lexical_analyzer::G1a()
{
   lex_class_reg = REM_T;
   Create_Token();
   next();
   q = &MINI_BASIC_Lexical_analyzer::G1;
}

void MINI_BASIC_Lexical_analyzer::H1a()
{
   relation_value_reg = character.value;
   lex_class_reg = RELATIONSHIP_OPERATIONS_T;
   next();
   q = &MINI_BASIC_Lexical_analyzer::H1;
}

void MINI_BASIC_Lexical_analyzer::H1b()
{
   Create_Token();
   H1a();
   q = &MINI_BASIC_Lexical_analyzer::H1;
}

void MINI_BASIC_Lexical_analyzer::H1c()
{
   DA1D();
   H1b();
   q = &MINI_BASIC_Lexical_analyzer::H1;
}

void MINI_BASIC_Lexical_analyzer::H1d()
{
   DA2D();
   H1b();
   q = &MINI_BASIC_Lexical_analyzer::H1;
}

void MINI_BASIC_Lexical_analyzer::H1e()
{
   DA3D();
   H1b();
   q = &MINI_BASIC_Lexical_analyzer::H1;
}

void MINI_BASIC_Lexical_analyzer::H1f()
{
   DA1E();
   H1b();
   q = &MINI_BASIC_Lexical_analyzer::H1;
}

void MINI_BASIC_Lexical_analyzer::M1()
{
   if (detection_reg == 0)
   {
	  if (table_first_vector[character.value] != 0)
		 detection_reg = table_first_vector[character.value];
	  else
		 Error_Handler();
   }


   if (character.value == table_detection[detection_reg].letter)
   {
	  (this->*(table_detection[detection_reg].f))();
   }
   else if (table_detection[detection_reg].alt != -1)
   {
	  detection_reg = table_detection[detection_reg].alt;
   }
   else    
	  Error_Handler();
}

void MINI_BASIC_Lexical_analyzer::M2()
{
   if (character.value != 5)
   {
	  DA1D();
	  B1b();
   }
   else
	  D3a();
}

void MINI_BASIC_Lexical_analyzer::M3()
{
   if (character.value != 5)
   {
	  DA2D();
	  B1b();
   }
   else
   {
	  next();
	  q = &MINI_BASIC_Lexical_analyzer::D3;
   }
}

void MINI_BASIC_Lexical_analyzer::EXIT1()
{
   lex_class_reg = END_OF_FILE_T;
   Create_Token();
   q = &MINI_BASIC_Lexical_analyzer::EXIT1;
}

void MINI_BASIC_Lexical_analyzer::EXIT2()
{
   Create_Token();
   EXIT1();
   q = &MINI_BASIC_Lexical_analyzer::EXIT2;
}

void MINI_BASIC_Lexical_analyzer::EXIT3()
{
   DA1D();
   EXIT2();
   q = &MINI_BASIC_Lexical_analyzer::EXIT3;
}

void MINI_BASIC_Lexical_analyzer::EXIT4()
{
   DA2D();
   EXIT2();
   q = &MINI_BASIC_Lexical_analyzer::EXIT4;
}

void MINI_BASIC_Lexical_analyzer::EXIT5()
{
   DA3D();
   EXIT2();
   q = &MINI_BASIC_Lexical_analyzer::EXIT5;
}

void MINI_BASIC_Lexical_analyzer::EXIT6()
{
   DA1E();
   EXIT2();
   q = &MINI_BASIC_Lexical_analyzer::EXIT6;
}

void MINI_BASIC_Lexical_analyzer::Create_Token()
{
   Token T;
   T.type = lex_class_reg;
   counter_tokens++;

   switch (lex_class_reg)
   {
   case LABLE_T:
	  table_number_string.insert_index(index_cur_number, counter_tokens);
	  T.value = index_cur_number;
	  break;

   case OPERAND_T:
	  
	  if (flag_operand == 0)  //Переменная
	  {
		 table_operands[index_reg] = 1;
		 T.value = index_reg;
	  }
	  else if (flag_operand == 1) //Константа
		 T.value = ptr_to_free - 1;
	  break;

   case GOTO_T:
   case GOSUB_T:
	  T.value = table_number_string.find(number_string_reg);
	  break;

   case LET_T:
   case FOR_T:
   case NEXT_T:
	  table_operands[index_reg] = 1;
	  T.value = index_reg;
	  break;

   case RELATIONSHIP_OPERATIONS_T:
	  T.value = relation_value_reg;
	  break;

   case ARITHMETIC_OPERATIONS_T:
   case L_BRACKET_T:
   case R_BRACKET_T:
   case IF_T:
   case RETURN_T:
   case END_T:
   case TO_T:
   case STEP_T:
   case REM_T:
   case ERROR_T:
   case END_OF_FILE_T:
	  T.value = character.value;
	  break;
   }

   table_tokens.push_back(T);
}

void MINI_BASIC_Lexical_analyzer::Error_Handler(string error)
{
   flag_error = 1;
   cout << error << " ";
   cout << "An error in the lexical analyzer." << endl;
   q = &MINI_BASIC_Lexical_analyzer::Error;
}

void MINI_BASIC_Lexical_analyzer::Error()
{
   cout << "An error in the lexical analyzer. \n Input error." << endl;
   q = &MINI_BASIC_Lexical_analyzer::Error;
}




