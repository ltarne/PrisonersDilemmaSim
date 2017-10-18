#include "Prisoner.h"




Prisoner::Prisoner(map<string, vector<string>> strategy) {
	this->strategy = strategy;

	LASTOUTCOME = 0;
	ALLOUTCOMES_W = 0;
	ALLOUTCOMES_X = 0;
	ALLOUTCOMES_Y = 0;
	ALLOUTCOMES_Z = 0;
	ITERATIONS = 0;
	MYSCORE = 0;
}

Prisoner::~Prisoner() {
}

outcome Prisoner::iteratePrisoner() {

	return outcome();
}
