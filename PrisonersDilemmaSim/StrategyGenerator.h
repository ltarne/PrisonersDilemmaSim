#pragma once
#include <fstream>
#include "UserInterface.h"

class StrategyGenerator
{
public:
	StrategyGenerator(UserInterface* ui);
	~StrategyGenerator();

	void writeManualStrategy();

	void generateStrategies(int n);

private:
	UserInterface* ui;
};

