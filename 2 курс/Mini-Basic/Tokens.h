#pragma once
#include <map>
#include <string>

using namespace std;

enum TokenType
{
   start_T = -1, LABLE_T, OPERAND_T, ARITHMETIC_OPERATIONS_T, RELATIONSHIP_OPERATIONS_T, 
   NEXT_T, LET_T, FOR_T, GOTO_T, GOSUB_T, L_BRACKET_T, R_BRACKET_T, IF_T, RETURN_T, END_T, TO_T, STEP_T, REM_T, ERROR_T, END_OF_FILE_T
};

const vector<string> TokenTypeString
{
    "LABLE", "OPERAND", "ARITHMETIC_OPERATIONS", "RELATIONSHIP_OPERATIONS", "NEXT", "LET", "FOR", "GOTO", "GOSUB", "L_BRACKET", "R_BRACKET", "IF", "RETURN", "END", "TO", "STEP", "REM", "ERROR", "END_OF_FILE"
};

enum Arithmetic_Operations
{
   PLUS, MINUS, MULT, DIV, XOR
};

enum Relationship_operations
{
   EQUAL, NOT, LESS_THEN, MORE_THEN, NOT_EQUAL, LESS_OR_EQUAL_THEN, MORE_OR_EQUAL_THEN
};

const map<string, TokenType> table_detection
{
   {"NEXT", NEXT_T}, {"LET", LET_T}, {"FOR", FOR_T}, {"GOTO", GOTO_T}, {"GOSUB", GOSUB_T}, 
   {"IF", IF_T}, {"RETURN", RETURN_T}, {"END", END_T}, {"TO", TO_T}, {"STEP", STEP_T}, {"REM", REM_T}
};

struct Token
{
   int type = start_T;
   int value;
};

enum SymbolicTokenType
{
   RUS_LETTER_S = -2,
   start_S,
   LETTER_S,
   DIGIT_S,
   ARITHMETIC_OPERATION_S,
   RELATION_S,
   SPACE_S,
   LF_S,
   ERROR_S,
   O_BRACE_S,
   C_BRACE_S,
   DOT_S,
   END_OF_FILE_S
};

struct SymbolicToken
{
   SymbolicTokenType token_class = start_S;
   int value = 0;
};




