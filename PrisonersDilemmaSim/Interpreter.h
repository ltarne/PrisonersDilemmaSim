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

/* Outcome of one strategy run */
enum outcome {
	NONE,
	SILENCE,
	BETRAY
	
};

class Interpreter
{
public:
	Interpreter(UserInterface* ui);
	~Interpreter();

	inline const string* getVariables() {
		return VARIABLES;
	}

	inline const string* getKeywords() {
		return KEY_WORDS;
	}

	inline const string* getOperators() {
		return OPERATORS;
	}

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



	void operationIF(map<string, vector<string>>::const_iterator* programPosition, vector<string> line, Prisoner* prisoner);
	

	void operationGOTO(map<string, vector<string>>::const_iterator* programPosition, vector<string> line, const map<string, vector<string>> &strategy);

	vector<string> generateFileVector(string baseName, int n);

protected:
	const string KEY_WORDS[5] = { "IF", "GOTO", "BETRAY", "SILENCE", "RANDOM" };
	const string VARIABLES[7] = { "LASTOUTCOME", "ALLOUTCOMES_W", "ALLOUTCOMES_X", "ALLOUTCOMES_Y", "ALLOUTCOMES_Z", "ITERATIONS", "MYSCORE" };
	const string OPERATORS[5] = { "+", "-", ">", "<", "=" };
	const map<string, overallOutcome> LITERALS = { {"W", W},{"X", X},{"Y", Y}, {"Z",Z } };

	UserInterface* ui;

};

