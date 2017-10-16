#pragma once
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <istream>
#include <sstream>

#include "Prisoner.h"

using namespace std;

class Interpreter
{
public:
	Interpreter();
	~Interpreter();

	Prisoner interpretFile(string fileName);

protected:
	const string KEY_WORDS[5] = { "IF", "GOTO", "BETRAY", "SILENCE", "RANDOM" };
	const string VARIABLES[7] = { "LASTOUTCOME", "ALLOUTCOMES_W", "ALLOUTCOMES_X", "ALLOUTCOMES_Y", "ALLOUTCOMES_Z", "ITERATIONS", "MYSCORE" };
	const char OPERATORS[5] = { '+', '-', '>', '<', '=' };



};

