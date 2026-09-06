#pragma once
#include "MB Sintax analyzer.h"

class Translator_to_assembler : 
	protected MINI_BASIC_Syntax_analyzer
{
public:
	Translator_to_assembler(string file_name);

	void Generate_assembler_code(string file_name);

	string N_to_S(int i) const;

protected:

	
};

