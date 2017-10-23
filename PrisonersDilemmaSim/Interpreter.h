#pragma once
#include <fstream>
#include <istream>
#include <sstream>
#include <iterator>
#include <ctype.h>
#include <time.h>

#include "Prisoner.h"
#include "UserInterface.h"

using namespace std;

enum outcome {
	SILENCE,
	BETRAY,
	NONE
};

class Interpreter
{
public:
	Interpreter(UserInterface* ui);
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


	void operationIF(map<string, vector<string>>::const_iterator* programPosition, vector<string> line, Prisoner* prisoner);
	

	void operationGOTO(map<string, vector<string>>::const_iterator* programPosition, vector<string> line, const map<string, vector<string>> &strategy);

protected:
	const string KEY_WORDS[5] = { "IF", "GOTO", "BETRAY", "SILENCE", "RANDOM" };
	const string VARIABLES[7] = { "LASTOUTCOME", "ALLOUTCOMES_W", "ALLOUTCOMES_X", "ALLOUTCOMES_Y", "ALLOUTCOMES_Z", "ITERATIONS", "MYSCORE" };
	const string OPERATORS[5] = { "+", "-", ">", "<", "=" };

	UserInterface* ui;

};

