/* Creates manual or automatic strategy files
* Author: Luke Burton 140274882
* Date: 27/10/2017
*/
#pragma once
#include <fstream>
#include "UserInterface.h"
#include "Interpreter.h"

class StrategyGenerator
{
public:
	StrategyGenerator(UserInterface* ui, Interpreter* interpreter);
	~StrategyGenerator();

	/*Write a manual strategy line by line*/
	void writeManualStrategy();

	/*Automatically generate n strategies*/
	void generateStrategies(int n);

private:
	UserInterface* ui;
	Interpreter* interpreter;
};

