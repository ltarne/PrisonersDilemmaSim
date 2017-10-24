#include "Interpreter.h"



Interpreter::Interpreter(UserInterface* ui) {
	this->ui = ui;
}


Interpreter::~Interpreter() {
}

Prisoner* Interpreter::interpretFile(string fileName) {
	map<string, vector<string>> instructions;
	

	ifstream file(fileName);

	if (!file.is_open()) {
		cerr << "Could not open file!\n";
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
				(!VARIABLES->find(splitLine[2]) && !isInteger(splitLine[2])) ||
				!OPERATORS->find(splitLine[3]) ||
				(!VARIABLES->find(splitLine[4]) && !isInteger(splitLine[4])) ||
				splitLine[5] != "GOTO" ||
				!isInteger(splitLine[6])) {
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
		
		if (line[0] == "BETRAY") {
			return BETRAY;
		}
		else if (line[0] == "SILENCE") {
			return SILENCE;
		}
		else if (line[0] == "RANDOM") {
			
			if (rand() % 2) {
				return BETRAY;
			}
			else {
				return SILENCE;
			}
		}
		else if (line[0] == "IF") {
			operationIF(&mapPosition, line, prisoner);
		}
		else if (line[0] == "GOTO") {
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


void Interpreter::operationIF(map<string, vector<string>>::const_iterator* programPosition, vector<string> line, Prisoner* prisoner) {
	//TODO: Add support for + and -
	//TODO: Add support for X, Y, Z, W
	unsigned int lhs = prisoner->getVariable(line[1]);
	unsigned int rhs = prisoner->getVariable(line[3]);
	bool result = false;

	if (line[2] == ">") {
		result = lhs > rhs;
	}
	else if (line[2] == "<") {
		result = lhs < rhs;
	}
	else if (line[2] == "=") {
		result = lhs == rhs;
	}

	if (result) {
		operationGOTO(programPosition, vector<string>{line[4], line[5]}, prisoner->getStrategy());
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
