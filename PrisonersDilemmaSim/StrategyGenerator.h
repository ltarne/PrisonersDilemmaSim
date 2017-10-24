#pragma once
#include <fstream>
#include "UserInterface.h"
#include "Interpreter.h"

class StrategyGenerator
{
public:
	StrategyGenerator(UserInterface* ui, Interpreter* interpreter);
	~StrategyGenerator();

	void writeManualStrategy();

	void generateStrategies(int n);

private:
	UserInterface* ui;
	Interpreter* interpreter;
};

