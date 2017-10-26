#include "Prisoner.h"




Prisoner::Prisoner() {
	strategy = map<string, vector<string>>();
	fileName = "";

	resetVariables();
}

Prisoner::Prisoner(map<string, vector<string>> strategy, string fileName) {
	this->strategy = strategy;
	this->fileName = fileName;

	resetVariables();
}

Prisoner::~Prisoner() {
}

unsigned int Prisoner::getVariable(const string word) {
	if (word == "LASTOUTCOME") {
		return LASTOUTCOME;
	}
	else if (word == "ALLOUTCOMES_W") {
		return ALLOUTCOMES_W;
	}
	else if (word == "ALLOUTCOMES_X") {
		return ALLOUTCOMES_X;
	}
	else if (word == "ALLOUTCOMES_Y") {
		return ALLOUTCOMES_Y;
	}
	else if (word == "ALLOUTCOMES_Z") {
		return ALLOUTCOMES_Z;
	}
	else if (word == "ALLOUTCOMES_A") {
		return ALLOUTCOMES_A;
	}
	else if (word == "ALLOUTCOMES_B") {
		return ALLOUTCOMES_B;
	}
	else if (word == "ALLOUTCOMES_C") {
		return ALLOUTCOMES_C;
	}
	else if (word == "ITERATIONS") {
		return ITERATIONS;
	}
	else if (word == "MYSCORE") {
		return MYSCORE;
	}

	return NULL;
}

void Prisoner::resetVariables() {
	LASTOUTCOME = N;
	ALLOUTCOMES_W = 0;
	ALLOUTCOMES_X = 0;
	ALLOUTCOMES_Y = 0;
	ALLOUTCOMES_Z = 0;
	ALLOUTCOMES_A = 0;
	ALLOUTCOMES_B = 0;
	ALLOUTCOMES_C = 0;
	ITERATIONS = 0;
	MYSCORE = 0;
}

