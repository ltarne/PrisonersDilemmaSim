#pragma once
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <ctype.h>

#include "Prisoner.h"

using namespace std;

class Interpreter
{
public:
	Interpreter();
	~Interpreter();

	/* Generate a strategy map from a file and create a prisoner.
	* fileName: File path of strategy file
	*/
	Prisoner* interpretFile(string fileName);

	/* Interpret the strategy map of a prisoner.
	* prisoner: The prisoner containing the strategy map to be interpreted
	*/
	void interpretStrategy(Prisoner* prisoner);

protected:
	const string KEY_WORDS[5] = { "IF", "GOTO", "BETRAY", "SILENCE", "RANDOM" };
	const string VARIABLES[7] = { "LASTOUTCOME", "ALLOUTCOMES_W", "ALLOUTCOMES_X", "ALLOUTCOMES_Y", "ALLOUTCOMES_Z", "ITERATIONS", "MYSCORE" };
	const char OPERATORS[5] = { '+', '-', '>', '<', '=' };



};

