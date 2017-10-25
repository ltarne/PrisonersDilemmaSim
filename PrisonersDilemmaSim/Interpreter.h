#pragma once
#include <fstream>
#include <istream>
#include <sstream>
#include <iterator>
#include <ctype.h>
#include <time.h>
#include <set>

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

	inline const set<string> getVariables() {
		return VARIABLES;
	}

	inline const set<string> getKeywords() {
		return KEY_WORDS;
	}

	inline const set<string> getComparisonOperators() {
		return COMPARISON_OPERATORS;
	}

	inline const set<string> getArithmeticOperators() {
		return ARITHMETIC_OPERATORS;
	}

	string getRandomComparisonOperator();

	string getRandomVariable();

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

	bool isBooleanExpressions(vector<string> expression);

	void operationIF(map<string, vector<string>>::const_iterator* programPosition, vector<string> line, Prisoner* prisoner);

	void operationGOTO(map<string, vector<string>>::const_iterator* programPosition, vector<string> line, const map<string, vector<string>> &strategy);

	vector<string> generateFileVector(string baseName, int n);

protected:
	const set<string> KEY_WORDS = { "IF", "GOTO", "BETRAY", "SILENCE", "RANDOM" };
	const set<string> VARIABLES = { "LASTOUTCOME", "ALLOUTCOMES_W", "ALLOUTCOMES_X", "ALLOUTCOMES_Y", "ALLOUTCOMES_Z", "ITERATIONS", "MYSCORE" };
	const set<string> COMPARISON_OPERATORS =  { ">", "<", "=" };
	const set<string> ARITHMETIC_OPERATORS = { "+", "-", };
	const map<string, overallOutcome> LITERALS = { {"W", W},{"X", X},{"Y", Y}, {"Z",Z } };

	UserInterface* ui;

};

