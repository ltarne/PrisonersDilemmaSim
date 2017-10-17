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

	while (getline(file, line)) {
		istringstream iss(line);
		
		vector<string> splitLine((istream_iterator<string>(iss)), istream_iterator<string>());
		
		//Check it has line numbers
		for (int i = 0; i < splitLine[0].length(); ++i) {
			if (!isdigit(splitLine[0][i])) {
				cerr << "Incorrect syntax\n";
				return NULL;
			}
		}

		string lineNum = splitLine[0];
		splitLine.erase(splitLine.begin());

		instructions.insert(pair<string, vector<string>>(lineNum, splitLine));
	}
	

	return new Prisoner(instructions);
}

void Interpreter::interpretStrategy(Prisoner* prisoner) {

}
