#include "Interpreter.h"



Interpreter::Interpreter(UserInterface* ui) {
	this->ui = ui;
}


Interpreter::~Interpreter() {
}

string Interpreter::getRandomComparisonOperator() {
	set<string>::const_iterator iterator = COMPARISON_OPERATORS.begin();
	advance(iterator, rand() % 3);
	return *iterator;
}

string Interpreter::getRandomVariable() {
	set<string>::const_iterator iterator = VARIABLES.begin();
	advance(iterator, rand() % 6+1);
	return *iterator;
}

int Interpreter::getVariable(string word, Prisoner* prisoner) {
	if (isInteger(word)) {
		return stoi(word);
	}
	else {
		return prisoner->getVariable(word);
	}
}

Prisoner* Interpreter::interpretFile(string fileName) {
	map<string, vector<string>> instructions;
	

	ifstream file(fileName);

	if (!file.is_open()) {
		ui->display("Could not open file!");
		return NULL;
	}
	

	string line = "";
	vector<string> referencedLines;

	while (getline(file, line)) {
		istringstream iss(line);
		
		vector<string> splitLine((istream_iterator<string>(iss)), istream_iterator<string>());

		//TODO: Check lines are in order
		//TODO: If not ask user if they want an auto sort

		//Check it is the correct length and has line numbers and a keyword
		if (splitLine.size() < 2 || 
			!isInteger(splitLine[0]) ||
			find(begin(KEY_WORDS), end(KEY_WORDS), splitLine[1]) == end(KEY_WORDS)) {
			ui->display("Invalid syntax: Line does not fit base criteria!");
			return NULL;
		}

		if (splitLine[1] == "GOTO") {
			//Check that lines of 3 long use valid GOTO syntax
			if (splitLine.size() != 3 ||
				!isInteger(splitLine[2])) {
				ui->display("Invalid syntax: Lines does not fit GOTO criteria!");
				return NULL;
			}
			//Add GOTO line number to a vector of referenced line numbers
			else {
				referencedLines.push_back(splitLine[2]);
			}
		}



		if (splitLine[1] == "IF") {

			//Check that lines of 7 long are in the form of a valid IF

			if (splitLine.size() < 7 ||
				!isBooleanExpressions(vector<string>(splitLine.begin()+2,splitLine.end()-2)) ||
				splitLine[splitLine.size()-2] != "GOTO" ||
				!isInteger(splitLine.back())) {
				ui->display("Invalid syntax: Line does not fit IF criteria!");
				return NULL;
			}
			//Add GOTO line number to a vector of referenced line numbers
			else {
				referencedLines.push_back(splitLine.back());
			}
		}



		//Seperate the line number
		string lineNum = splitLine[0];
		splitLine.erase(splitLine.begin());

		instructions.insert(pair<string, vector<string>>(lineNum, splitLine));
	}

	//Check that all line numbers listed in GOTO statements are valid
	for (int i = 0; i < referencedLines.size(); ++i) {
		if (instructions.find(referencedLines[i]) == instructions.end()) {
			ui->display("Invalid syntax: Line " + referencedLines[i] + " doesn't exist!");
			return NULL;
		}
	}


	return new Prisoner(instructions, fileName);
}

outcome Interpreter::interpretStrategy(Prisoner* prisoner) {
	const map<string, vector<string>> &strategy = prisoner->getStrategy();

	map<string, vector<string>>::const_iterator mapPosition = strategy.begin();
	vector<string> line;



	while (mapPosition != strategy.end()) {
		line = mapPosition->second;

		if (line[0][0] == 'B') {
			return BETRAY;
		}
		else if (line[0][0] == 'S') {
			return SILENCE;
		}
		else if (line[0][0] == 'R') {

			if (rand() % 2) {
				return BETRAY;
			}
			else {
				return SILENCE;
			}
		}
		else if (line[0][0] == 'I') {
			operationIF(&mapPosition, line, prisoner, strategy);
		}
		else if (line[0][0] == 'G') {
			operationGOTO(&mapPosition, line, strategy);
		}

	}

	return NONE;
}

bool Interpreter::isInteger(string testString) {
	for (int i = 0; i < testString.length(); ++i) {
		if (!isdigit(testString[i])) {
			return false;
		}
	}
	return true;
}

bool Interpreter::isBooleanExpressions(vector<string> expression) {
	bool isStatementComplete = false;
	bool isCompared = false;

	if (expression.size() < 3) {
		return false;
	}

	if (expression[0] == "LASTOUTCOME") {
		if (expression.size() != 3 || expression[1] != "=" || !LITERALS.count(expression[2]) ) {
			return false;
		}
		else {
			return true;
		}
	}

	for (int i = 0; i < expression.size(); ++i) {
		if (COMPARISON_OPERATORS.count(expression[i])) {
			if (isCompared) {
				return false;
			}
			isCompared = true;
			isStatementComplete = false;
		}
		else if ((isInteger(expression[i]) ||
			VARIABLES.count(expression[i]))) {
			if(isStatementComplete) {
				return false;
			}
			isStatementComplete = true;	
		}
		else if (ARITHMETIC_OPERATORS.count(expression[i])) {
			if (!isStatementComplete) {
				return false;
			}
			isStatementComplete = false;
		}
		
	}

	return true;
}

bool Interpreter::evaluateBooleanExpression(vector<string> expression, Prisoner* prisoner) {
	bool result;
	if (expression[0] == "LASTOUTCOME") {
		return prisoner->getLASTOUTCOME() == LITERALS.find(expression[2])->second;
	}
	else if (expression[2] == "LASTOUTCOME") {
		return prisoner->getLASTOUTCOME() == LITERALS.find(expression[0])->second;
	}

	int lhs = getVariable(expression[0], prisoner);

	int i = 1;
	string comparison;
	while (!COMPARISON_OPERATORS.count(expression[i])) {
		if (expression[i] == "+") {
			lhs += getVariable(expression[i], prisoner);
			i += 2;
		}
		else if (expression[i] == "-") {
			lhs -= getVariable(expression[i], prisoner);
			i += 2;
		}

	}
	comparison = expression[i];
	i++;
	int rhs = getVariable(expression[i], prisoner);
	for (int j = i+1; j < expression.size(); ++j) {
		if (expression[j] == "+") {
			lhs += getVariable(expression[j], prisoner);
			j++;
		}
		else if (expression[j] == "-") {
			lhs -= getVariable(expression[j], prisoner);
			j++;
		}
	}

	if (comparison[0] == '>') {
		return lhs > rhs;
	}
	else if (comparison[0] == '<') {
		return lhs < rhs;
	}
	else if (comparison[0] == '=') {
		return lhs == rhs;
	}


	return false;
}


void Interpreter::operationIF(map<string, vector<string>>::const_iterator* programPosition, vector<string> line, Prisoner* prisoner, const map<string, vector<string>> &strategy) {
	//TODO: Add support for + and -
	//TODO: Add support for X, Y, Z, W
	/*unsigned int lhs = prisoner->getVariable(line[1]);
	unsigned int rhs = prisoner->getVariable(line[3]);*/
	bool result = false;


	result = evaluateBooleanExpression(vector<string>{&line[1], &line[line.size() - 2]}, prisoner);

	if (result) {
		operationGOTO(programPosition, vector<string>{line[line.size() - 2], line[line.size() - 1]}, strategy);
	}
	else {
		(*programPosition)++;
	}
}

void Interpreter::operationGOTO(map<string, vector<string>>::const_iterator* programPosition, vector<string> line, const map<string, vector<string>> &strategy) {
	*programPosition = strategy.find(line[1]);
}

vector<string> Interpreter::generateFileVector(string baseName, int n) {
	vector<string> filePaths;
	for (int i = 0; i < n; ++i) {
		filePaths.push_back(baseName + to_string(i) + ".txt");
	}
	return filePaths;
}
