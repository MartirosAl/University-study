#pragma once
#include <vector>
#include <string>
using namespace std;

enum AtomType
{
   start_A = -1, END_A, NUMBER_LINE_A, ASSIGNMENT_A, TRANSITION_A, STORAGE_TRANSITION_A, RETURN_TRANSITION_A, CONDITIONAL_TRANSITION_A, STORAGE_A, LABLE_A, CHECK, INCREASE_A, ADDITION_A, SUBSTRACTION_A, MULTIPLICATION_A, DIVISION_A, POWER_A, PLUS_A, MINUS_A
};

const vector<string> AtomTypeString
{
    "END", "NUMBER_LINE", "ASSIGNMENT", "TRANSITION", "STORAGE_TRANSITION", "RETURN_TRANSITION", "CONDITIONAL_TRANSITION", "STORAGE", "LABLE", "CHECK", "INCREASE", "ADDITION", "SUBSTRACTION", "MULTIPLICATION", "DIVISION", "POWER", "PLUS", "MINUS"
};

struct Atom
{
   int type = start_A;
   int attribute1 = -1;
   int attribute2 = -1;
   int attribute3 = -1;
   int attribute4 = -1;
};

const vector<string> TableType1
{
   "<Programm>", "<Programm's body>", "<Step>", "<Other rows>", "<Expression>", "<Term>", "<Multiplier>", "<E-list>", "<T-list>", "<F-list>", "Relation", "End cycle", "Transition", "Right bracket", "End", "To", "@", "{Assign}", "{Conditional transition}", "{Store}", "{Label}", "{Check}", "{Control}", "{Increase}", "{Transition}", "{Addition}", "{Substract}", "{Multiplication}", "{Division}", "{Power}", "{Plus}", "{Minus}"
};

const vector<string> TableType2
{
   "LABEL", "Operand", "Relation", "NEXT", "LET", "FOR", "GOTO", "GOSUB", "Left bracket", "Right bracket", "IF", "RETURN", "END", "TO", "STEP", "COMMENT", "+", "-", "*", "/", "^", "ERROR", "END_MARK"
};