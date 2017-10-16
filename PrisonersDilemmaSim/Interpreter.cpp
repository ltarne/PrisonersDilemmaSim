#include "Interpreter.h"



Interpreter::Interpreter() {
}


Interpreter::~Interpreter() {
}

Prisoner Interpreter::interpretFile(string fileName) {
	map<string, string> instructions;
	

	ifstream file(fileName);
	

	string line = "";

	while (getline(file, line)) {
		
		istringstream iss(line);
		vector<string> splitLine();
		
	}





	return Prisoner();
}
