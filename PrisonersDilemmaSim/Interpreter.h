#pragma once
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <ctype.h>
#include <set>

#include "Prisoner.h"

using namespace std;

enum outcome {
	SILENCE,
	BETRAY
};

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
	outcome interpretStrategy(Prisoner* prisoner);

	/* Is a given string an integer
	* testString: The string to be tested
	*/
	bool isInteger(string testString);

	/* Check that the statement given fits a valid size 
	* splitLine: Statement line split up by spaces
	*/
	bool isCorrectLength(vector<string> splitLine);


	void operationIF(const string* programPosition, vector<string> line, Prisoner* prisoner);
	

	void operationGOTO(string& programPosition, vector<string> line);

protected:
	const string KEY_WORDS[5] = { "IF", "GOTO", "BETRAY", "SILENCE", "RANDOM" };
	const string VARIABLES[7] = { "LASTOUTCOME", "ALLOUTCOMES_W", "ALLOUTCOMES_X", "ALLOUTCOMES_Y", "ALLOUTCOMES_Z", "ITERATIONS", "MYSCORE" };
	const string OPERATORS[5] = { "+", "-", ">", "<", "=" };



};

