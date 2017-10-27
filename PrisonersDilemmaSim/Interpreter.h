/* Interprets files into a readable format and executes strategies
* Author: Luke Burton 140274882
* Date: 27/10/2017
*/
#pragma once
#include <fstream>
#include <istream>
#include <sstream>
#include <iterator>
#include <ctype.h>
#include <time.h>
#include <set>

#include "Gang.h"
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

	/*Return a random compariosn operator*/
	string getRandomComparisonOperator();

	/*Return a random variable*/
	string getRandomVariable();

	/*Return address of the variable referenced
	* word: Word to be checked 
	* prisoner: Variable source
	*/
	int getVariable(string word, Prisoner* prisoner);

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

	/*Return if boolean expression i.e. x < y*/
	bool isBooleanExpressions(vector<string> expression);

	/*Return answer to boolean expression*/
	bool evaluateBooleanExpression(vector<string> expression, Prisoner* prisoner);

	/*Execute IF statement*/
	void operationIF(map<string, vector<string>>::const_iterator* programPosition, vector<string> line, Prisoner* prisoner, const map<string, vector<string>> &strategy);

	/*Execute GOTO statement*/
	void operationGOTO(map<string, vector<string>>::const_iterator* programPosition, vector<string> line, const map<string, vector<string>> &strategy);

	/*Generate filename form a base name and range*/
	vector<string> generateFileVector(string baseName, int n);

protected:
	const set<string> KEY_WORDS = { "IF", "GOTO", "BETRAY", "SILENCE", "RANDOM" };
	const set<string> VARIABLES = { "LASTOUTCOME", "ALLOUTCOMES_W", "ALLOUTCOMES_X", "ALLOUTCOMES_Y", "ALLOUTCOMES_Z", "ALLOUTCOMES_A", "ALLOUTCOMES_B", "ALLOUTCOMES_C", "ITERATIONS", "MYSCORE" };
	const set<string> COMPARISON_OPERATORS =  { ">", "<", "=" };
	const set<string> ARITHMETIC_OPERATORS = { "+", "-", };
	const map<string, overallOutcome> LITERALS = { {"W", W},{"X", X},{"Y", Y}, {"Z",Z }, {"A", A}, {"B", B}, {"C", C} };

	UserInterface* ui;

};

