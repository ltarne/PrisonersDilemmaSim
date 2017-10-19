#include "Interpreter.h"



Interpreter::Interpreter() {
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


		//Check it is the correct length and has line numbers and a keyword
		if (!isCorrectLength(splitLine) ||
			!isInteger(splitLine[0]) ||
			find(begin(KEY_WORDS), end(KEY_WORDS), splitLine[1]) == end(KEY_WORDS)) {
			cerr << "Invalid syntax: Line does not fit base criteria!\n";
			return NULL;
		}


		

		//Check that lines of 7 long are in the form of a valid IF
		if (splitLine.size() == 7 && 
			(splitLine[1] != "IF" ||
			(!VARIABLES->find(splitLine[2]) && !isInteger(splitLine[2])) ||
			!OPERATORS->find(splitLine[3]) ||
			(!VARIABLES->find(splitLine[4]) && !isInteger(splitLine[4])) ||
			splitLine[5] != "GOTO" ||
			!isInteger(splitLine[6]))) {
			cerr << "Invalid syntax: Line does not fit IF criteria\n";
			return NULL;
		}
		//Add GOTO line number to a vector of referenced line numbers
		else if(splitLine.size() == 7) {
			referencedLines.push_back(splitLine[6]);
		}




		//Seperate the line number
		string lineNum = splitLine[0];
		splitLine.erase(splitLine.begin());

		instructions.insert(pair<string, vector<string>>(lineNum, splitLine));
	}

	//Check that all line numbers listed in GOTO statements are valid
	for (int i = 0; i < referencedLines.size(); ++i) {
		if (instructions.find(referencedLines[i]) == instructions.end()) {
			cerr << "Invalid syntax: Line " + referencedLines[i] + " doesn't exist!\n";
			return NULL;
		}
	}
	

	return new Prisoner(instructions);
}

outcome Interpreter::interpretStrategy(Prisoner* prisoner) {
	map<string, vector<string>> strategy = prisoner->getStrategy();

	bool isFinished = false;
	string programPosition = strategy.begin()->first;

	while (!isFinished) {
		vector<string> line = strategy.find(programPosition)->second;
		
		if (line[0] == "BETRAY") {
			return BETRAY;
		}
		else if (line[0] == "SILENCE") {
			return SILENCE;
		}
		else if (line[0] == "RANDOM") {

		}
		else if (line[0] == "IF") {
			operationIF(&programPosition, line, prisoner);
		}
		else if (line[0] == "GOTO") {

		}
		else {
			isFinished = true;
		}
		
		
	}
	return BETRAY;
}

bool Interpreter::isInteger(string testString) {
	for (int i = 0; i < testString.length(); ++i) {
		if (!isdigit(testString[i])) {
			return false;
		}
	}
	return true;
}

bool Interpreter::isCorrectLength(vector<string> splitLine) {
	//Check for correct size
	const int numLengths = 4;
	int allowedSizes[numLengths] = { 2, 3, 5, 7 };

	for (int i = 0; i < numLengths; ++i) {
		if (splitLine.size() == allowedSizes[i]) {
			return true;
		}
	}
	return false;
}

void Interpreter::operationIF(const string* programPosition, vector<string> line, Prisoner* prisoner) {

}

void Interpreter::operationGOTO(string& programPosition, vector<string> line) {

}
