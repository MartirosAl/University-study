#pragma once
#include <iomanip>
#include "Function.h"

class Action
{
public:
	virtual ~Action() {}

	virtual const string& Get_Name() = 0;

	virtual void Operate(Function* func_) = 0;
};

